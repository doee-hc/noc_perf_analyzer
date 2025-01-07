import queue
import random
import time 
from functools import reduce
from math import gcd

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
            #print(f"{self.name} put: {data}")  
            return True  # Write successful
        #print(f"{self.name} is full, cannot write: {data}")  
        return False  # FIFO full

    def read(self):
        if not self.queue.empty():
            data = self.queue.get()
            #print(f"{self.name} get: {data}")   
            return data  # Read successful
        #print(f"{self.name} is empty, cannot read")  
        return None  # FIFO empty

    def peek(self):
        """Peek at the first element without removing it."""
        if not self.queue.empty():
            # Access the internal deque structure
            data = self.queue.queue[0]
            #print(f"{self.name} peek: {data}")
            return data
        #print(f"{self.name} is empty, cannot peek")
        return None

    def valid(self):
        return not self.queue.empty()

    def ready(self):
        return not self.queue.full()

    def unused(self):
        """Get the remaining space in the FIFO."""
        unused = self.depth - self.queue.qsize()
        return unused

    def used(self):
        """Get the remaining space in the FIFO."""
        used = self.queue.qsize()
        return used 

class Monitor:
    def __init__(self):
        # A dictionary to store the status of tasks.
        # The key is the task ID, and the value is a boolean indicating whether the task is finished.
        self.tasks = {}
        self.instances = {}
        self.tick = 0
        self.max_freq = 0
        self.multiplier = 0

    def register_task(self, task_id):
        """
        Register a new task ID and mark it as not finished.
        If the task ID is already registered, it will not be added again.
        """
        if task_id not in self.tasks:
            self.tasks[task_id] = False  # Mark as not finished
        else:
            print(f"Task ID {task_id} is already registered.")



    def finish(self, task_id):
        """
        Mark the specified task ID as finished.
        If the task ID is not registered, print a warning message.
        """
        if task_id in self.tasks:
            self.tasks[task_id] = True  # Mark as finished
        else:
            print(f"Task ID {task_id} is not registered.")

    def simloop(self):
        """
        Check if all tasks are finished.
        Returns 1 if all tasks are finished, otherwise returns 0.
        """
        self.tick += 1
        # Use the all() function to check if all task statuses are True
        return 0 if all(self.tasks.values()) else 1

    def _lcm(self, a, b):
        """Calculate the least common multiple of two numbers"""
        return abs(a * b) // gcd(a, b)

    def _lcm_multiple(self, numbers):
        """Calculate the least common multiple of multiple numbers"""
        return reduce(self._lcm, numbers)

    def _get_fraction_denominator(self, fractional):
        """将小数部分转化为分数，并返回分母"""
        # 将小数转化为分数
        from fractions import Fraction
        fraction = Fraction(fractional).limit_denominator()
        return fraction.denominator

    def register_instance(self, instance_id, freq):
        """
        Register a new instance ID, marking it as enabled.
        If the instance ID is already registered, it will not be added again.
        """
        if instance_id not in self.instances:
            # 添加新实例
            self.instances[instance_id] = {"freq":freq}
            self.instances[instance_id]["cycles"] = 0
            # 获取当前所有实例的频率
            current_freqs = [instance["freq"] for instance in self.instances.values()]
            if current_freqs:
                # 找到最大频率
                self.max_freq = max(current_freqs)

                # 计算初始 interval（可能是小数）
                for inst_id, inst in self.instances.items():
                    inst["interval"] = self.max_freq / inst["freq"]

                # 找到所有 interval 的分母
                intervals = [inst["interval"] for inst in self.instances.values()]
                denominators = []

                for interval in intervals:
                    # 分离小数部分，转化为分数
                    fractional_part = interval - int(interval)
                    if fractional_part > 0:  # 只有小数部分不为0时才处理
                        # 将小数转化为分数，找到分母
                        denominator = self._get_fraction_denominator(fractional_part)
                        denominators.append(denominator)

                # 如果有小数部分，计算最小公倍数进行放大
                if denominators:
                    self.multiplier = self._lcm_multiple(denominators)
                else:
                    self.multiplier = 1  # 如果全是整数，不需要放大

                # 更新所有 interval 为整数
                for inst_id, inst in self.instances.items():
                    inst["interval"] = int(inst["interval"] * self.multiplier)
            else:
                # 如果是第一个实例，直接设置 interval 为 1
                self.instances[instance_id]["interval"] = 1
        else:
            print(f"Instance ID {instance_id} is already registered.")

    def get_time(self):
        # ns
        return self.tick * 1e9 / (self.max_freq * self.multiplier)

    def get_instance_cycle(self, instance_id):
        return self.instances[instance_id]["cycles"]

    def check_active(self, instance_id):
        """
        Check if the instance with the given ID is active based on the current tick.
        Returns 1 if the instance is active, otherwise returns 0.
        """
        if instance_id in self.instances:
            interval = self.instances[instance_id]["interval"]
            # Check if the current tick modulo the interval equals 0
            if self.tick % interval == 0:
                self.instances[instance_id]["cycles"] += 1
                return 1
            else:
                return 0
        else:
            print(f"Instance ID {instance_id} is not registered.")
            return 0



class AXIMaster:
    def __init__(self, master_id, data_width, burst_length, frequency, monitor):
        monitor.register_instance(master_id,frequency)
        self.data_width = data_width
        self.burst_length = burst_length
        self.frequency = frequency

        # FIFOs for communication
        self.aw_fifo = None
        self.w_fifo = None
        self.b_fifo = None
        self.ar_fifo = None
        self.r_fifo = None

        self.monitor = monitor

        # Transaction tracking
        self.base_awid = 0  # Counter for AW transaction IDs
        self.base_arid = 0  # Counter for AR transaction IDs
        self.outstanding_writes = 0  # Count of outstanding write transactions
        self.outstanding_reads = 0   # Count of outstanding read transactions
        self.block_queue = []
        self.delay_counter = 0
        self.outstanding_read_queue = []
        self.outstanding_write_queue = []
        self.w_counter = 0
        self.r_counter = 0
        self.completed = 0
        self.master_id = master_id
        self.block_id = {}

        self.read_encoder = PriorityRoundRobinEncoder()
        self.write_encoder = PriorityRoundRobinEncoder()

    def connect_fifos(self, aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo):
        self.aw_fifo = aw_fifo
        self.w_fifo = w_fifo
        self.b_fifo = b_fifo
        self.ar_fifo = ar_fifo
        self.r_fifo = r_fifo

    def axi_write(self, slave_id, data_len, ost_len, burst_len, condition=None, priority=0):
        block_id_key = f"{self.master_id}->{slave_id} wr"
        if block_id_key in self.block_id:
            self.block_id[block_id_key] += 1
        else:
            self.block_id[block_id_key] = 0
        block_id = f"{block_id_key} {self.block_id[block_id_key]}"
        self.monitor.register_task(block_id)
        block = {
            "block_id": block_id,
            "type": "write",
            "data_length": data_len,
            "burst_length": burst_len,
            "condition": condition,
            "priority": priority,
            "transaction_queue": [],
            "max_outstanding": ost_len,
            "outstanding_writes": 0,
            "completed": 0,
            "awid_counter": self.base_awid
        }
        while(data_len> 0):
            awid = block["awid_counter"]
            block["awid_counter"] += 1
            burst = min(burst_len, data_len)
            data_len -= burst
            transaction = {
                "awid": awid,
                "slave_id": slave_id,
                "burst_length": burst,
                "state": "pending"
            }
            block["transaction_queue"].append(transaction)

        self.block_queue.append(block)
        print(f"Added write block: {block}")
        self.base_awid += MAX_TRANS_NUM
    
    def axi_read(self, slave_id, data_len,ost_len,burst_len, condition=None, priority=0):
        block_id_key = f"{self.master_id}->{slave_id} rd"
        if block_id_key in self.block_id:
            self.block_id[block_id_key] += 1
        else:
            self.block_id[block_id_key] = 0
        block_id = f"{block_id_key} {self.block_id[block_id_key]}"
        self.monitor.register_task(block_id)
        block = {
            "block_id": block_id,
            "type": "read",
            "data_length": data_len,
            "burst_length": burst_len,
            "condition": condition,
            "priority": priority,
            "transaction_queue": [],
            "max_outstanding": ost_len,
            "outstanding_reads": 0,
            "completed": 0,
            "arid_counter": self.base_arid
        }
        while(data_len> 0):
            arid = block["arid_counter"]
            block["arid_counter"] += 1
            burst = min(self.burst_length, data_len)
            data_len -= burst
            transaction = {
                "arid": arid,
                "slave_id": slave_id,
                "burst_length": burst,
                "state": "pending"
            }
            block["transaction_queue"].append(transaction)


        self.block_queue.append(block)
        print(f"Added read block: {block}")
        self.base_arid += MAX_TRANS_NUM

    def condition_check(self,block):
        condition = block["condition"]
        check_pass = 1
        if condition:
            if(check_pass and "delay" in condition):
                if 'delay_counter' not in condition:
                    condition["delay_counter"] = 0

                if(condition["delay_counter"] < condition["delay"]):
                    condition["delay_counter"] += 1
                    check_pass = 0
                else:
                    check_pass = 1
            if(check_pass and "ext_data" in condition):
                ext_data_fifo = condition["ext_data"]
                if block["type"] == "write":
                    if ext_data_fifo.used() >= block["burst_length"]:
                        check_pass = 1
                    else:
                        check_pass = 0
                if block["type"] == "read":
                    if ext_data_fifo.unused() >= block["burst_length"]:
                        check_pass = 1
                    else:
                        check_pass = 0
        return check_pass
                

    def process(self):

        if not self.monitor.check_active(self.master_id):
            return

        # W/B channel
        if self.outstanding_write_queue:
            wid = self.outstanding_write_queue[0]["awid"]
            burst = self.outstanding_write_queue[0]["burst"]
            blkIndex =  self.outstanding_write_queue[0]["blkIndex"]
            tranIndex =  self.outstanding_write_queue[0]["tranIndex"]

            # w channel
            if self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] == "in_progress":
                if self.w_counter < burst:
                    if self.w_fifo.ready():
                        if self.block_queue[blkIndex]["condition"] and "ext_data" in self.block_queue[blkIndex]["condition"]:
                            ext_data_fifo = self.block_queue[blkIndex]["condition"]["ext_data"]
                            wdata = ext_data_fifo.read()
                        else:
                            wdata = random.randint(0, 2**self.data_width - 1)
                        self.w_fifo.write({
                            "wid": wid,
                            "data": random.randint(0, 2**self.data_width - 1)
                        })
                        print(f"{self.master_id} write transfer WID={wid}")
                        self.w_counter += 1
                else:
                    self.w_counter = 0
                    self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "waiting_b"
                    print(f"{self.master_id} write transaction waiting for B response: AWID={wid}")

            # b channel
            if self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] == "waiting_b":
                if self.b_fifo.ready():
                    response = self.b_fifo.read()
                    if response:
                        if response["bid"] == wid:
                            self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "completed"
                            print(f"{self.master_id} write transaction completed: AWID={wid}")
                            self.outstanding_write_queue.pop(0)
                            self.block_queue[blkIndex]["outstanding_writes"] -= 1
                            self.block_queue[blkIndex]["completed"] += 1
                            if self.block_queue[blkIndex]["completed"] == len(self.block_queue[blkIndex]["transaction_queue"]):
                                self.monitor.finish(self.block_queue[blkIndex]["block_id"])
                        else:
                            raise ValueError(f"BID mismatch, act: {wid}, exp: {response['bid']}")
        # AW/AR channel
        for blkIndex,block in enumerate(self.block_queue):
            if self.condition_check(block):
                for tranIndex,transaction in enumerate(block["transaction_queue"]):
                    if transaction["state"] == "pending":
                        if block["type"] == "write":
                            # write transaction
                            if self.aw_fifo.ready() and block["outstanding_writes"] < block["max_outstanding"]:
                                self.write_encoder.add_task(Task(task_id={"blkIndex":blkIndex,"tranIndex":tranIndex}, priority=block["priority"]))

                        elif block["type"] == "read":
                            # read transaction
                            if self.ar_fifo.ready() and block["outstanding_reads"] < block["max_outstanding"]:
                                self.read_encoder.add_task(Task(task_id={"blkIndex":blkIndex,"tranIndex":tranIndex}, priority=block["priority"]))
                        break

        write_task = self.write_encoder.get_task()
        if write_task != 0:
            blkIndex = write_task.task_id["blkIndex"]
            tranIndex = write_task.task_id["tranIndex"]
            awid = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["awid"]
            burst = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["burst_length"]
            slave_id = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["slave_id"]
            if self.aw_fifo.ready():
                self.aw_fifo.write({"slave_id": slave_id, "awid": awid, "burst": burst})
                self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "in_progress"
                self.block_queue[blkIndex]["outstanding_writes"] += 1
                self.outstanding_write_queue.append({"blkIndex":blkIndex,"tranIndex":tranIndex,"awid":awid,"burst":burst})
                print(f"{self.master_id} write transaction started: AWID={awid}")


        read_task = self.read_encoder.get_task()
        if read_task != 0:
            blkIndex = read_task.task_id["blkIndex"]
            tranIndex = read_task.task_id["tranIndex"]
            arid = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["arid"]
            burst = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["burst_length"]
            slave_id = self.block_queue[blkIndex]["transaction_queue"][tranIndex]["slave_id"]
            if self.ar_fifo.ready():
                self.ar_fifo.write({"slave_id": slave_id, "arid": arid, "burst": burst})
                self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "waiting_r"
                self.block_queue[blkIndex]["outstanding_reads"] += 1
                self.outstanding_read_queue.append({"blkIndex":blkIndex,"tranIndex":tranIndex,"arid":arid,"burst":burst})
                print(f"{self.master_id} read transaction started: ARID={arid}")



        # r channel
        if self.outstanding_read_queue:
            rid = self.outstanding_read_queue[0]["arid"]
            burst = self.outstanding_read_queue[0]["burst"]
            blkIndex = self.outstanding_read_queue[0]["blkIndex"]
            tranIndex = self.outstanding_read_queue[0]["tranIndex"]

            if self.r_fifo.valid():
                response = self.r_fifo.read()
                if response["rid"] == rid:
                    self.r_counter += 1
                    if self.block_queue[blkIndex]["condition"] and "ext_data" in self.block_queue[blkIndex]["condition"]:
                        ext_data_fifo = self.block_queue[blkIndex]["condition"]["ext_data"]
                        ext_data_fifo.write(response)
                else:
                    raise ValueError(f"RID mismatch, act: {rid}, exp: {response['rid']}")

            if self.r_counter == burst:
                self.r_counter = 0
                self.block_queue[blkIndex]["transaction_queue"][tranIndex]["state"] = "completed"
                print(f"{self.master_id} read transaction completed: ARID={rid}")
                self.outstanding_read_queue.pop(0)
                self.block_queue[blkIndex]["outstanding_reads"] -= 1
                self.block_queue[blkIndex]["completed"] += 1
                if self.block_queue[blkIndex]["completed"] == len(self.block_queue[blkIndex]["transaction_queue"]):
                    self.monitor.finish(self.block_queue[blkIndex]["block_id"])




class AXISlave:
    def __init__(self, slave_id, max_outstanding, frequency, monitor):
        monitor.register_instance(slave_id,frequency)
        self.max_outstanding = max_outstanding
        self.frequency = frequency

        # FIFOs for communication
        self.aw_fifo = None
        self.w_fifo = None
        self.b_fifo = None
        self.ar_fifo = None
        self.r_fifo = None

        self.monitor = monitor
        self.slave_id = slave_id

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

        if not self.monitor.check_active(self.slave_id):
            return

        # Process W/B channel
        if self.active_writes:
            awid = self.active_writes[0]["awid"]
            burst = self.active_writes[0]["burst"]
            # b channel
            if self.b_flag:
                self.b_flag = 0
                self.b_fifo.write({"bid":awid})
                print(f"{self.slave_id} receive w channel complete AWID={awid}")
                self.active_writes.pop(0)
            else:
                w = self.w_fifo.peek()
                if w :
                    wid = w["wid"]
                    if awid == wid:
                        self.w_fifo.read()
                        #raise ValueError(f"WID mismatch, act: {wid}, exp: {awid}")
                        self.w_counter += 1
                        print(f"{self.slave_id} receive W channel AWID={awid}")
                        if self.w_counter == burst:
                            self.w_counter = 0
                            self.b_flag = 1

        # Process AW channel
        if self.aw_fifo.valid() and len(self.active_writes) < self.max_outstanding:
            aw = self.aw_fifo.peek()
            if aw:
                if aw["slave_id"] == self.slave_id:
                    self.aw_fifo.read()
                    awid = aw["awid"]
                    burst = aw["burst"]
                    self.active_writes.append({"awid":awid,"burst":burst})
                    print(f"{self.slave_id} AW channel complete AWID={awid}")

        # Process R channel
        if self.active_reads:
            arid = self.active_reads[0]["arid"]
            burst = self.active_reads[0]["burst"]
            # r channel
            self.r_fifo.write({"rid":arid})
            self.r_counter += 1
            if self.r_counter == burst:
                self.r_counter = 0
                print(f"{self.slave_id} response r channel complete {arid}")
                self.active_reads.pop(0)

        # Process AR channel
        if self.ar_fifo.valid() and len(self.active_reads) < self.max_outstanding:
            ar = self.ar_fifo.peek()
            if ar:
                if ar["slave_id"] == self.slave_id:
                    self.ar_fifo.read()
                    arid = ar["arid"]
                    burst = ar["burst"]
                    self.active_reads.append({"arid":arid,"burst":burst})



# Simulation setup
def simulate():
    # Initialize master and slave

    monitor = Monitor()

    # 1.2G * 256bit
    dma_m0 = AXIMaster(master_id="DMA_M0", data_width=32, burst_length=4, frequency=1.2e9, monitor=monitor)
    dma_m1 = AXIMaster(master_id="DMA_M1", data_width=32, burst_length=4, frequency=1.2e9, monitor=monitor)
    axi_sram = AXISlave(slave_id="AXI_SRAM", max_outstanding=1000, frequency=1.2e9, monitor=monitor)

    # 400M * 64bit
    core00_dccm = AXISlave(slave_id="CORE00_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core01_dccm = AXISlave(slave_id="CORE01_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core02_dccm = AXISlave(slave_id="CORE02_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core03_dccm = AXISlave(slave_id="CORE03_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core10_dccm = AXISlave(slave_id="CORE10_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core11_dccm = AXISlave(slave_id="CORE11_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core12_dccm = AXISlave(slave_id="CORE12_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core13_dccm = AXISlave(slave_id="CORE13_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core20_dccm = AXISlave(slave_id="CORE20_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core21_dccm = AXISlave(slave_id="CORE21_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core22_dccm = AXISlave(slave_id="CORE22_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core23_dccm = AXISlave(slave_id="CORE23_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core30_dccm = AXISlave(slave_id="CORE30_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core31_dccm = AXISlave(slave_id="CORE31_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core32_dccm = AXISlave(slave_id="CORE32_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
    core33_dccm = AXISlave(slave_id="CORE33_DCCM", max_outstanding=1000, frequency=0.1e9, monitor=monitor)
     
    print(monitor.instances)

    # Connect FIFOs
    aw_fifo = FIFO(16, name="aw_fifo")
    w_fifo = FIFO(16, name="w_fifo")
    b_fifo = FIFO(16, name="b_fifo")
    ar_fifo = FIFO(16, name="ar_fifo")
    r_fifo = FIFO(16, name="r_fifo")

    dma_ch1_fifo = FIFO(16, name="dma_ch1_fifo")
    dma_ch2_fifo = FIFO(16, name="dma_ch2_fifo")
    dma_ch3_fifo = FIFO(16, name="dma_ch3_fifo")
    dma_ch4_fifo = FIFO(16, name="dma_ch4_fifo")
    dma_ch5_fifo = FIFO(16, name="dma_ch5_fifo")
    dma_ch6_fifo = FIFO(16, name="dma_ch6_fifo")
    dma_ch7_fifo = FIFO(16, name="dma_ch7_fifo")
    dma_ch8_fifo = FIFO(16, name="dma_ch8_fifo")

    dma_m0.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo )
    axi_sram.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)
    core00_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo) 
    core01_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo) 
    core02_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core03_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core10_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core11_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core12_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core13_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core20_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core21_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core22_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core23_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core30_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core31_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core32_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo)  
    core33_dccm.connect_fifos(aw_fifo, w_fifo, b_fifo, ar_fifo, r_fifo) 


    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch1_fifo})
    dma_m0.axi_write(slave_id="CORE00_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch1_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch2_fifo})
    dma_m0.axi_write(slave_id="CORE01_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch2_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch3_fifo})
    dma_m0.axi_write(slave_id="CORE02_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch3_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch4_fifo})
    dma_m0.axi_write(slave_id="CORE03_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch4_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch5_fifo})
    dma_m0.axi_write(slave_id="CORE10_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch5_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch6_fifo})
    dma_m0.axi_write(slave_id="CORE11_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch6_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch7_fifo})
    dma_m0.axi_write(slave_id="CORE12_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch7_fifo})
    dma_m0.axi_read(slave_id="AXI_SRAM",        data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch8_fifo})
    dma_m0.axi_write(slave_id="CORE13_DCCM",    data_len=16, ost_len=2, burst_len=4,condition={"delay":0,"ext_data":dma_ch8_fifo})


    # Simulate
    #for cycle in range(1000):  # Simulate 1000 clock cycles
    cycle = 0
    while monitor.simloop():
        print(f"time:{monitor.get_time():.2f}ns")

        if(monitor.get_time() > 1000):
            return
        # Issue write and read commands
        dma_m0.process()
        axi_sram.process()
        core00_dccm.process()
        core01_dccm.process()
        core02_dccm.process()
        core03_dccm.process()
        core10_dccm.process()
        core11_dccm.process()
        core12_dccm.process()
        core13_dccm.process()
        core20_dccm.process()
        core21_dccm.process()
        core22_dccm.process()
        core23_dccm.process()
        core30_dccm.process()
        core31_dccm.process()
        core32_dccm.process()
        core33_dccm.process()

        # Add any additional simulation logic here


if __name__ == "__main__":
    simulate()

