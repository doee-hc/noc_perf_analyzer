import queue
import random
import time 

MAX_TRANS_NUM = 10000

class Task:
    def __init__(self, task_id, priority):
        """Initialize a Task with an ID and priority."""
        self.task_id = task_id
        self.priority = priority

    def __repr__(self):
        """String representation of the Task."""
        return f"Task(id={self.task_id}, priority={self.priority})"

class PriorityRoundRobinEncoder:
    def __init__(self):
        """Initialize the encoder with a dictionary for priority queues and a round-robin index."""
        self.priority_queues = {}  # Dictionary to store task queues for each priority
        self.current_priority_index = 0  # Index to track the current priority in the round-robin

    def add_task(self, task):
        """Add a task to the appropriate priority queue."""
        if task.priority not in self.priority_queues:
            # Create a new queue for this priority if it doesn't exist
            self.priority_queues[task.priority] = queue.Queue()
        self.priority_queues[task.priority].put(task)

    def get_task(self):
        """Retrieve a task using priority-based round-robin scheduling and clear all remaining tasks."""
        if not self.priority_queues:
            #raise Exception("No tasks available")
            return 0

        # Get all priorities sorted in descending order (higher priority first)
        priorities = sorted(self.priority_queues.keys(), reverse=True)

        # Iterate through the priorities in a round-robin manner
        for _ in range(len(priorities)):
            # Get the current priority based on the round-robin index
            priority = priorities[self.current_priority_index]

            # Check if the queue for this priority has any tasks
            if not self.priority_queues[priority].empty():
                # Get the next task from the queue
                task = self.priority_queues[priority].get()

                # Update the round-robin index to the next priority
                self.current_priority_index = (self.current_priority_index + 1) % len(priorities)

                # Clear all remaining tasks after retrieving one
                self.clear_all_tasks()
                return task

            # If the current priority's queue is empty, move to the next priority
            self.current_priority_index = (self.current_priority_index + 1) % len(priorities)

        # If no tasks are available in any queue
        return 0
        #raise Exception("No tasks available")

    def clear_all_tasks(self):
        """Clear all tasks from all priority queues."""
        self.priority_queues.clear()
        self.current_priority_index = 0  # Reset the round-robin index

class FIFO:
    def __init__(self, depth, name="FIFO"):
        self.depth = depth
        self.queue = queue.Queue(maxsize=depth)
        self.name = name  

    def write(self, data):
        if not self.queue.full():
            self.queue.put(data)
            print(f"{self.name} put: {data}")  
            return True  # Write successful
        #print(f"{self.name} is full, cannot write: {data}")  
        return False  # FIFO full

    def read(self):
        if not self.queue.empty():
            data = self.queue.get()
            print(f"{self.name} get: {data}")   
            return data  # Read successful
        #print(f"{self.name} is empty, cannot read")  
        return None  # FIFO empty

    def valid(self):
        return not self.queue.empty()

    def ready(self):
        return not self.queue.full()


class AXIMaster:
    def __init__(self, data_width, max_outstanding, burst_length, frequency):
        self.data_width = data_width
        self.max_outstanding = max_outstanding
        self.burst_length = burst_length
        self.frequency = frequency

        self.dma_fifo = None

        # FIFOs for communication
        self.aw_fifo = None
        self.w_fifo = None
        self.b_fifo = None
        self.ar_fifo = None
        self.r_fifo = None

        # Transaction tracking
        self.awid_counter = 0  # Counter for AW transaction IDs
        self.arid_counter = 0  # Counter for AR transaction IDs
        self.outstanding_writes = 0  # Count of outstanding write transactions
        self.outstanding_reads = 0   # Count of outstanding read transactions
        self.block_queue = []
        self.delay_counter = 0
        self.outstanding_read_queue = []
        self.outstanding_write_queue = []
        self.w_counter = 0
        self.r_counter = 0

        self.read_encoder = PriorityRoundRobinEncoder()
        self.write_encoder = PriorityRoundRobinEncoder()

    def connect_fifos(self, aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo, dma_fifo=None):
        self.aw_fifo = aw_fifo
        self.w_fifo = w_fifo
        self.b_fifo = b_fifo
        self.ar_fifo = ar_fifo
        self.r_fifo = r_fifo
        self.dma_fifo = dma_fifo

    def axi_write(self, slave_id, data_length, condition=None, priority=0):
        block = {
            "type": "write",
            "slave_id": slave_id,
            "data_length": data_length,
            "remaining_length": data_length,
            "condition": condition,
            "priority": priority,
            "transaction_queue": []
        }
        while(data_length > 0):
            awid = self.awid_counter
            self.awid_counter += 1
            burst = min(self.burst_length, data_length)
            data_length -= burst
            transaction = {
                "awid": awid,
                "burst_length": burst,
                "state": "pending"
            }
            block["transaction_queue"].append(transaction)

        self.block_queue.append(block)
        print(f"Added write block: {block}")
        self.awid_counter += MAX_TRANS_NUM
    
    def axi_read(self, slave_id, data_length, condition=None, priority=0):
        block = {
            "type": "read",
            "slave_id": slave_id,
            "data_length": data_length,
            "remaining_length": data_length,
            "condition": condition,
            "priority": priority,
            "transaction_queue": []
        }
        while(data_length > 0):
            arid = self.arid_counter
            self.arid_counter += 1
            burst = min(self.burst_length, data_length)
            data_length -= burst
            transaction = {
                "arid": arid,
                "burst_length": burst,
                "state": "pending"
            }
            block["transaction_queue"].append(transaction)


        self.block_queue.append(block)
        print(f"Added read block: {block}")
        self.arid_counter += MAX_TRANS_NUM

    def condition_check(self,condition):
        if condition:
            if(condition["type"] == "delay"):
                if 'delay_counter' not in condition:
                    condition["delay_counter"] = 0

                if(condition["delay_counter"] >= condition["value"]):
                    return 1
                else:
                    condition["delay_counter"] += 1
                    return 0
        else:
            return 1
                

    def process(self):
        for blkIndex,block in enumerate(self.block_queue):
            if self.condition_check(block["condition"]):
                for tranIndex,transaction in enumerate(block["transaction_queue"]):
                    if transaction["state"] == "pending":
                        if block["type"] == "write":
                            # write transaction
                            if self.aw_fifo.ready() and self.outstanding_writes < self.max_outstanding:
                                self.write_encoder.add_task(Task(task_id={"blkIndex":blkIndex,"tranIndex":tranIndex}, priority=block["priority"]))

                        elif block["type"] == "read":
                            # read transaction
                            if self.ar_fifo.ready() and self.outstanding_reads < self.max_outstanding:
                                self.read_encoder.add_task(Task(task_id={"blkIndex":blkIndex,"tranIndex":tranIndex}, priority=block["priority"]))
                        break

        write_task = self.write_encoder.get_task()
        if write_task != 0:
            blkIndex = write_task.task_id["blkIndex"]
            tranIndex = write_task.task_id["tranIndex"]
            awid = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["awid"]
            burst = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["burst_length"]
            self.aw_fifo.write({"awid": awid, "burst": burst})
            self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "in_progress"
            self.outstanding_write_queue.append({"blkIndex":blkIndex,"tranIndex":tranIndex,"awid":awid,"burst":burst})
            print(f"Write transaction started: AWID={awid}")

        read_task = self.read_encoder.get_task()
        if read_task != 0:
            blkIndex = read_task.task_id["blkIndex"]
            tranIndex = read_task.task_id["tranIndex"]
            arid = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["arid"]
            burst = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["burst_length"]
            self.ar_fifo.write({"arid": arid, "burst": burst})
            self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "waiting_r"
            self.outstanding_read_queue.append({"blkIndex":blkIndex,"tranIndex":tranIndex,"arid":arid,"burst":burst})
            print(f"Read transaction started: ARID={arid}")

        # w/b channel
        if self.outstanding_write_queue:
            wid = self.outstanding_write_queue[0]["awid"]
            burst = self.outstanding_write_queue[0]["burst"]
            blkIndex =  self.outstanding_write_queue[0]["blkIndex"]
            tranIndex =  self.outstanding_write_queue[0]["tranIndex"]

            # w channel
            if self.block_queue[blkIndex]["transaction_queue"][tranIndex] == "in_progress":
                if self.w_counter < burst:
                    if self.w_fifo.ready():
                        self.w_fifo.write({
                            "wid": wid,
                            "data": random.randint(0, 2**self.data_width - 1)
                        })
                        self.w_counter += 1
                else:
                    self.w_counter = 0
                    self.block_queue[blkIndex]["transaction_queue"][tranIndex] = "waiting_b"
                    print(f"Write transaction waiting for B response: AWID={wid}")

            # b channel
            if self.block_queue[blkIndex]["transaction_queue"][tranIndex] == "waiting_b":
                if self.b_fifo.ready():
                    response = self.b_fifo.read()
                    if response:
                        if response["bid"] == wid:
                            self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "completed"
                            print(f"Write transaction completed: AWID={wid}")
                            self.outstanding_write_queue.pop(0)
                        else:
                            raise ValueError(f"BID mismatch, act: {wid}, exp: {response['bid']}")

        # r channel
        if self.outstanding_read_queue:
            rid = self.outstanding_read_queue[0]["arid"]
            burst = self.outstanding_read_queue[0]["burst"]
            blkIndex = self.outstanding_read_queue[0]["blkIndex"]
            tranIndex = self.outstanding_read_queue[0]["tranIndex"]
            if self.dma_fifo is not None:
                # dma mode: r data store into internal dma fifo
                if self.r_fifo.valid() and self.dma_fifo.ready():
                    response = self.r_fifo.read()
                    if response:
                        if response["rid"] == rid:
                            self.r_counter += 1
                            self.dma_fifo.write(response)
                        else:
                            raise ValueError(f"RID mismatch, act: {rid}, exp: {response['rid']}")
            else:
                # nomal mode: always rready
                if self.r_fifo.valid():
                    response = self.r_fifo.read()
                    if response:
                        if response["rid"] == rid:
                            self.r_counter += 1
                            # discard data
                        else:
                            raise ValueError(f"RID mismatch, act: {rid}, exp: {response['rid']}")
            if self.r_counter == burst:
                self.r_counter = 0
                self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "completed"
                print(f"Read transaction completed: ARID={rid}")
                self.outstanding_read_queue.pop(0)


class AXISlave:
    def __init__(self, max_outstanding, frequency):
        self.max_outstanding = max_outstanding
        self.frequency = frequency

        # FIFOs for communication
        self.aw_fifo = None
        self.w_fifo = None
        self.b_fifo = None
        self.ar_fifo = None
        self.r_fifo = None

        # Internal state
        self.active_writes = []
        self.active_reads = []

        self.w_counter = 0
        self.r_counter = 0
        self.b_flag = 0
        self.r_flag = 0

    def connect_fifos(self, aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo):
        self.aw_fifo = aw_fifo
        self.w_fifo = w_fifo
        self.b_fifo = b_fifo
        self.ar_fifo = ar_fifo
        self.r_fifo = r_fifo

    def process(self):

        # Process W/B channel
        if self.active_writes:
            awid = self.active_writes[0]["awid"]
            burst = self.active_writes[0]["burst"]
            # b channel
            if self.b_flag:
                self.b_flag = 0
                self.b_fifo.write({"bid":awid})
                print(f"Slave receive w channel complete {awid}")
                self.active_writes.pop(0)
            else:
                w = self.w_fifo.read()
                if w :
                    wid = w["wid"]
                    if awid != wid:
                        raise ValueError(f"WID mismatch, act: {wid}, exp: {awid}")
                    # discard data
                    self.w_counter += 1
                    if self.w_counter == burst:
                        self.w_counter = 0
                        self.b_flag = 1

        # Process AW channel
        if self.aw_fifo.valid() and len(self.active_writes) < self.max_outstanding:
            aw = self.aw_fifo.read()
            if aw:
                awid = aw["awid"]
                burst = aw["burst"]
                self.active_writes.append({"awid":awid,"burst":burst})

        # Process R channel
        if self.active_reads:
            arid = self.active_reads[0]["arid"]
            burst = self.active_reads[0]["burst"]
            # r channel
            self.r_fifo.write({"rid":arid})
            self.r_counter += 1
            if self.r_counter == burst:
                self.r_counter = 0
                print(f"Slave response r channel complete {arid}")
                self.active_reads.pop(0)

        # Process AR channel
        if self.ar_fifo.valid() and len(self.active_reads) < self.max_outstanding:
            ar = self.ar_fifo.read()
            if ar:
                arid = ar["arid"]
                burst = ar["burst"]
                self.active_reads.append({"arid":arid,"burst":burst})



# Simulation setup
def simulate():
    # Initialize master and slave
    master = AXIMaster(data_width=32, max_outstanding=4, burst_length=4, frequency=100)
    slave = AXISlave(max_outstanding=4, frequency=100)

    # Connect FIFOs
    aw_fifo = FIFO(16, name="aw_fifo")
    w_fifo = FIFO(16, name="w_fifo")
    b_fifo = FIFO(16, name="b_fifo")
    ar_fifo = FIFO(16, name="ar_fifo")
    r_fifo = FIFO(16, name="r_fifo")
    dma_fifo = FIFO(16, name="dma_fifo")

    master.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo, dma_fifo)
    slave.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)

    master.axi_write(slave_id=0, data_length=16)
    master.axi_read(slave_id=0, data_length=16)
    # Simulate
    for cycle in range(1000):  # Simulate 1000 clock cycles
        # Issue write and read commands
        master.process()

        # Handle responses
        slave.process()

        # Add any additional simulation logic here


if __name__ == "__main__":
    simulate()

