import json
import os
import re
import tkinter as tk
from tkinter import filedialog, messagebox
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import address_map_parser as amp

def get_address_key(transaction_type):
    if transaction_type.startswith("AXI_AR"):
        return "ARADDR"
    elif transaction_type.startswith("AXI_AW"):
        return "AWADDR"
    elif transaction_type.startswith("AHB"):
        return "HADDR"
    elif transaction_type.startswith("APB"):
        return "PADDR"
    else:
        return None

def calculate_delay(source, source_type, destination, destination_type, destination_base_addr, source_log_name, destination_log_name):
    base_addr = int(destination_base_addr, 16)
    source_addr_key = get_address_key(source_type)
    destination_addr_key = get_address_key(destination_type)
    
    if not source_addr_key or not destination_addr_key:
        print("src_type:" + source_type)
        print("dest_type:" + destination_type)
        raise ValueError("Invalid source or destination type")
    
    
    result_entry = {
        "ia_log": source_log_name,
        "ta_log": destination_log_name,
        "data":[]
    }

    for src_index, src_trans in enumerate(source):
        if src_trans['type'] == source_type:
            src_addr = int(src_trans[source_addr_key], 16)
            
            for dest_index, dest_trans in enumerate(destination):
                if dest_trans['type'] == destination_type:
                    dest_addr = int(dest_trans[destination_addr_key], 16) + base_addr
                    
                    if src_addr == dest_addr:
                        src_time = float(src_trans['time'].split()[0])
                        dest_time = float(dest_trans['time'].split()[0])
                        delay = dest_time - src_time
                        
                        data_entry = {
                            "time": src_time,
                            "latency": delay,
                            "ia_index": src_index,
                            "ta_index": dest_index
                        }
                        result_entry["data"].append(data_entry)
                        break

    return result_entry

def gen_latency_logs(log_files):

    current_dir = os.path.dirname(os.path.abspath(__file__))
    bus_config_dir = os.path.join(os.path.dirname(current_dir), 'bus_config')
    address_map_file = os.path.join(bus_config_dir, 'address_map.json')
    bus_map_file = os.path.join(bus_config_dir, 'bus_map.json')

    with open(address_map_file, 'r') as f:
        address_map = json.load(f)

    with open(bus_map_file, 'r') as f:
        bus_map = json.load(f)

    ia_logs = {}
    ta_logs = {}

    for ia in bus_map["ia"]:
        ia_logs[ia] = []
    for ta_key in bus_map:
        if ta_key != "ia":
            for ta in bus_map[ta_key]:
                ta_logs[ta] = []

    for log_file in log_files:
        log_file_name = os.path.basename(log_file)
        
        match_ia_axi = re.match(r'(axi)_ia_(.+?)_(ar|aw)', log_file_name)
        match_ta_axi = re.match(r'(axi)_ta_(.+?)_(ar|aw)', log_file_name)
        match_ia_ahb_apb = re.match(r'(ahb|apb)_ia_(.+)\.json', log_file_name)
        match_ta_ahb_apb = re.match(r'(ahb|apb)_ta_(.+)\.json', log_file_name)
        
        if match_ia_axi:
            log_type, ia_name, _ = match_ia_axi.groups()
            ia_logs[f"{log_type}_ia_{ia_name}"].append(log_file)
        elif match_ta_axi:
            log_type, ta_name, _ = match_ta_axi.groups()
            ta_logs[f"{log_type}_ta_{ta_name}"].append(log_file)
        elif match_ia_ahb_apb:
            log_type, ia_name = match_ia_ahb_apb.groups()
            ia_logs[f"{log_type}_ia_{ia_name}"].append(log_file)
        elif match_ta_ahb_apb:
            log_type, ta_name = match_ta_ahb_apb.groups()
            ta_logs[f"{log_type}_ta_{ta_name}"].append(log_file)

    for ia in bus_map["ia"]:
        for ia_log_file in ia_logs.get(ia, []):
            ia_log_name = os.path.splitext(os.path.basename(ia_log_file))[0]

            with open(ia_log_file, 'r') as f:
                ia_log_data = json.load(f)
            for region in address_map['regions']:
                target_ta = region['target']
                base_addr = region['base']
                if target_ta in bus_map:
                    for ta in bus_map[target_ta]:
                        for ta_log_file in ta_logs.get(ta, []):
                            ta_log_name = os.path.splitext(os.path.basename(ta_log_file))[0]

                            if (ia_log_name.startswith('axi') and ia_log_name.endswith('ar') and
                                ta_log_name.startswith('axi') and ta_log_name.endswith('ar')): 
                                    source_type = "AXI_AR"
                                    destination_type = "AXI_AR"
                            elif (ia_log_name.startswith('axi') and ia_log_name.endswith('aw') and
                                ta_log_name.startswith('axi') and ta_log_name.endswith('aw')): 
                                    source_type = "AXI_AW"
                                    destination_type = "AXI_AW"
                            elif (ia_log_name.startswith('axi') and ia_log_name.endswith('ar') and
                                ta_log_name.startswith('ahb') or ta_log_name.startswith('apb')): 
                                    source_type = "AXI_AR"
                                    destination_type = ta_log_name.split('_')[0].upper() + '_RD' 
                            elif (ia_log_name.startswith('axi') and ia_log_name.endswith('aw') and
                                ta_log_name.startswith('ahb') or ta_log_name.startswith('apb')): 
                                    source_type = "AXI_AW"
                                    destination_type = ta_log_name.split('_')[0].upper() + '_WR' 
                            elif (ia_log_name.startswith('ahb') or ia_log_name.startswith('apb') and
                                ta_log_name.startswith('ahb') or ta_log_name.startswith('apb')):
                                    for suffix in ['RD', 'WR']:
                                        source_type = ia_log_name.split('_')[0].upper() + '_' + suffix
                                        destination_type = ta_log_name.split('_')[0].upper() + '_' + suffix

                                        with open(ta_log_file, 'r') as f:
                                            ta_log_data = json.load(f)

                                        result = calculate_delay(ia_log_data, source_type, ta_log_data, destination_type, base_addr, ia_log_name, ta_log_name)

                                        if result["data"]:
                                            output_file_name = f"npa_db/latency_{ia_log_name}_{ta_log_name}_{suffix}.json"
                                            print(f"Write to {output_file_name}")
                                            with open(output_file_name, 'w') as f:
                                                json.dump(result, f, indent=4)
                                    continue
                            else:
                                continue

                            with open(ta_log_file, 'r') as f:
                                ta_log_data = json.load(f)

                            result = calculate_delay(ia_log_data, source_type, ta_log_data, destination_type, base_addr, ia_log_name, ta_log_name)

                            if result["data"]:
                                output_file_name = f"npa_db/latency_{ia_log_name}_{ta_log_name}.json"
                                print(f"Write to {output_file_name}")
                                with open(output_file_name, 'w') as f:
                                    json.dump(result, f, indent=4)

#def load_and_process():
#    log_files = filedialog.askopenfilenames(title="Select Log Files", filetypes=[("JSON files", "*.json")])
#    address_map_file = filedialog.askopenfilename(title="Select Address Map File", filetypes=[("JSON files", "*.json")])
#    bus_map_file = filedialog.askopenfilename(title="Select Bus Map File", filetypes=[("JSON files", "*.json")])
#    
#    if not log_files or not address_map_file or not bus_map_file:
#        messagebox.showwarning("Warning", "Please select all required files.")
#        return
#    
#    process_logs(log_files, address_map_file, bus_map_file)
#
#root = tk.Tk()
#root.title("Log Processor")
#
#frame = tk.Frame(root)
#frame.pack(pady=20)
#
#process_button = tk.Button(frame, text="Load and Process Logs", command=load_and_process)
#process_button.pack()
#
#root.mainloop()


