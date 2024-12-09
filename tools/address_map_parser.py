import argparse
import re
import json

def parse_address_map(config):
    address_map = {}
    current_region = None

    for line in config.splitlines():
        line = line.strip()
        if line.startswith('address_map'):
            address_map['name'] = re.findall(r'address_map\s+(\w+)', line)[0]
            address_map['addr_width'] = None
            address_map['regions'] = []
        elif line.startswith('addr_width'):
            address_map['addr_width'] = int(re.findall(r'addr_width\s+(\d+)', line)[0])
        elif line.startswith('region'):
            if current_region:
                address_map['regions'].append(current_region)
            region_info = re.findall(r'region\s+(\w+)\s+target\s+(\w+)', line)
            if region_info:
                region_name, target = region_info[0]
                current_region = {'name': region_name, 'target': target}
        elif line.startswith('base'):
            base = int(re.findall(r'base\s+(0x[0-9a-fA-F]+)', line)[0], 16)
            current_region['base'] = base
        elif line.startswith('size'):
            size = int(re.findall(r'size\s+(0x[0-9a-fA-F]+)', line)[0], 16)
            current_region['size'] = size

    if current_region:  # Add the last region if exists
        address_map['regions'].append(current_region)

    return address_map

def format_address_map(address_map):
    for region in address_map.get('regions', []):
        if 'base' in region:
            region['base'] = f"0x{region['base']:X}"
        if 'size' in region:
            region['size'] = f"0x{region['size']:X}"
    return address_map

def main():
    parser = argparse.ArgumentParser(description='Parse address map configuration file.')
    parser.add_argument('input_file', type=str, help='Path to the input configuration file')
    parser.add_argument('output_file', type=str, help='Path to the output JSON file')

    args = parser.parse_args()
    input_file_path = args.input_file
    output_file_path = args.output_file

    try:
        with open(input_file_path, 'r') as file:
            config = file.read()
            address_map = parse_address_map(config)
            formatted_address_map = format_address_map(address_map)
            
            with open(output_file_path, 'w') as output_file:
                json.dump(formatted_address_map, output_file, indent=4)
            
            print(f"Parsed data has been written to '{output_file_path}'")
    except FileNotFoundError:
        print(f"Error: The file '{input_file_path}' was not found.")
    except Exception as e:
        print(f"An error occurred: {e}")

if __name__ == '__main__':
    main()

