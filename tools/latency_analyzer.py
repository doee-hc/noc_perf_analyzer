import json
import sys

def calculate_delay(source, source_type, destination, destination_type, destination_base_addr):
    # Convert base address to integer
    base_addr = int(destination_base_addr, 16)
    
    # Result list
    result = []
    
    # Iterate over transactions in source
    for src_trans in source:
        if src_trans['type'] == source_type:
            # Get source address
            src_addr = int(src_trans['ARADDR'], 16)
            
            # Iterate over transactions in destination
            for dest_trans in destination:
                if dest_trans['type'] == destination_type:
                    # Calculate actual address in destination
                    dest_addr = int(dest_trans['HADDR'], 16) + base_addr
                    
                    # If addresses match
                    if src_addr == dest_addr:
                        # Calculate delay
                        src_time = float(src_trans['time'].split()[0])
                        dest_time = float(dest_trans['time'].split()[0])
                        delay = dest_time - src_time
                        
                        # Add source transaction with delay information to result
                        src_trans_with_delay = src_trans.copy()
                        src_trans_with_delay['delay'] = delay
                        result.append(src_trans_with_delay)
                        break  # Break inner loop after match

    return result

#def main():
#    if len(sys.argv) != 4:
#        print("Usage: python script.py <source_json_file> <destination_json_file> <output_json_file>")
#        return
#
#    source_file = sys.argv[1]
#    destination_file = sys.argv[2]
#    output_file = sys.argv[3]
#
#    # Read input files
#    with open(source_file, 'r') as f:
#        source = json.load(f)
#
#    with open(destination_file, 'r') as f:
#        destination = json.load(f)
#
#    # Example call
#    source_type = "AXI_AR"  # Modify as needed
#    destination_type = "AHB_RD"  # Modify as needed
#    destination_base_addr = "44000000"  # Modify as needed
#
#    result = calculate_delay(source, source_type, destination, destination_type, destination_base_addr)
#
#    # Write to output file
#    with open(output_file, 'w') as f:
#        json.dump(result, f, indent=4)
#
#if __name__ == "__main__":
#    main()

