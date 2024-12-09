import tkinter as tk
from tkinter import ttk
from tkinter import filedialog, Text, Scrollbar
import matplotlib.pyplot as plt
import os
import json
from scipy.spatial import KDTree
import address_map_parser as amp
import latency_analyzer as la

def main():
    root = tk.Tk()
    root.title("Bus Transaction Log")

    file_paths = []

    fig, ax = plt.subplots(figsize=(15, 4))

    transactions_list = []
    log_lines_list = []
    kdtrees = []

    def load_files():
        transactions_list.clear()
        log_lines_list.clear()
        kdtrees.clear()
        
        for file_path in file_paths:
            with open(file_path, 'r') as file:
                data = json.load(file)
                transactions = data
                transactions_list.append(transactions)

                file.seek(0)
                lines = file.readlines()
                if len(lines) > 2:
                    lines = lines[1:-1]
                elif len(lines) > 1:
                    lines = lines[1:]
                else:
                    lines = []
                log_lines_list.append(lines)

                times = [[float(trans['time'].replace(' ns', ''))] for trans in transactions]
                kdtree = KDTree(times)
                kdtrees.append(kdtree)

    colors = plt.cm.get_cmap('tab10', 10)

    scatter_plots = []
    global highlight_marker, second_marker, time_diff_text
    highlight_marker = None
    second_marker = None
    time_diff_text = None

    log_vars = []

    type_colors = {}
    type_list = ["AXI_AR", "AXI_R", "AXI_AW", "AXI_W", "AXI_B", "AHB_WR", "AHB_RD", "APB_WR", "APB_RD"]  
    for i, t in enumerate(type_list):
        type_colors[t] = colors(i % 10)

    def draw_scatter():
        ax.clear()
        scatter_plots.clear()
        visible_indices = [i for i, var in enumerate(log_vars) if var.get()]


        if not visible_indices:
            ax.text(0.5, 0.5, 'No logs selected', horizontalalignment='center', verticalalignment='center', transform=ax.transAxes)
            fig.canvas.draw()
            return

        handled_types = set()
        for j, i in enumerate(visible_indices):
            transactions = transactions_list[i]
            for trans in transactions:
                x = float(trans['time'].replace(' ns', ''))
                y = j
                trans_type = trans['type']
                color = type_colors.get(trans_type, 'black')
                if trans_type not in handled_types:
                    scatter = ax.scatter(x, y, label=trans_type, color=color, marker='s')
                    handled_types.add(trans_type)
                else:
                    scatter = ax.scatter(x, y, color=color, marker='s')
                scatter_plots.append(scatter)

        ax.set_xlabel('Time (ns)')
        if transactions_list:
            max_time = max(float(trans['time'].replace(' ns', '')) for transactions in transactions_list for trans in transactions)
            ax.set_xlim(0, max_time + 1000)
            ax.set_ylim(-1, len(visible_indices))
            ax.yaxis.set_ticks(range(len(visible_indices)))
            ax.yaxis.set_ticklabels([os.path.splitext(os.path.basename(file_paths[i]))[0] for i in visible_indices])
            ax.grid(True)
            ax.legend(loc='upper right',ncol=10)
        fig.canvas.draw()

    main_frame = tk.Frame(root)
    main_frame.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    left_frame = tk.Frame(main_frame)
    left_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

    notebook_left = ttk.Notebook(left_frame)
    notebook_left.pack(side=tk.TOP, fill=tk.BOTH, expand=True)
    notebook_right = ttk.Notebook(left_frame)
    notebook_right.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

    text_widgets_left = []
    text_widgets_right = []
    control_frame = tk.Frame(main_frame)
    control_frame.pack(side=tk.LEFT, fill=tk.Y)

    checkbuttons_frame = tk.Frame(control_frame)
    checkbuttons_frame.pack(side=tk.TOP, anchor='w')

    def reload_logs():
        load_files()
        for i, log_text in enumerate(text_widgets_left):
            log_text.config(state=tk.NORMAL)
            log_text.delete('1.0', tk.END)
            for line in log_lines_list[i]:
                log_text.insert('end', line)
            log_text.config(state=tk.DISABLED)
        for i, log_text in enumerate(text_widgets_right):
            log_text.config(state=tk.NORMAL)
            log_text.delete('1.0', tk.END)
            for line in log_lines_list[i]:
                log_text.insert('end', line)
            log_text.config(state=tk.DISABLED)
        draw_scatter()

    def browse_files():
        nonlocal file_paths
        new_file_paths = filedialog.askopenfilenames(initialdir="npa_db", title="Select log files", filetypes=(("JSON files", "*.json"), ("all files", "*.*")))
        if new_file_paths:
            file_paths = new_file_paths
            for widget in notebook_left.winfo_children():
                widget.destroy()
            for widget in notebook_right.winfo_children():
                widget.destroy()
            text_widgets_left.clear()
            text_widgets_right.clear()
            log_vars.clear()
            for widget in checkbuttons_frame.winfo_children():
                widget.destroy()
            load_files()
            for i, file_path in enumerate(file_paths):
                tab_left = ttk.Frame(notebook_left)
                notebook_left.add(tab_left, text=os.path.splitext(os.path.basename(file_path))[0])

                log_text_left = Text(tab_left, height=10, width=200)
                log_text_left.config(state=tk.NORMAL)
                log_text_left.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                scrollbar_left = Scrollbar(tab_left, command=log_text_left.yview)
                scrollbar_left.pack(side=tk.RIGHT, fill=tk.Y)
                log_text_left.config(yscrollcommand=scrollbar_left.set)
                for line in log_lines_list[i]:
                    log_text_left.insert('end', line)
                log_text_left.config(state=tk.DISABLED)

                text_widgets_left.append(log_text_left)

                tab_right = ttk.Frame(notebook_right)
                notebook_right.add(tab_right, text=os.path.splitext(os.path.basename(file_path))[0])

                log_text_right = Text(tab_right, height=10, width=200)
                log_text_right.config(state=tk.NORMAL)
                log_text_right.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
                scrollbar_right = Scrollbar(tab_right, command=log_text_right.yview)
                scrollbar_right.pack(side=tk.RIGHT, fill=tk.Y)
                log_text_right.config(yscrollcommand=scrollbar_right.set)
                for line in log_lines_list[i]:
                    log_text_right.insert('end', line)
                log_text_right.config(state=tk.DISABLED)

                text_widgets_right.append(log_text_right)

                log_var = tk.BooleanVar(value=True)
                log_vars.append(log_var)
                checkbutton = ttk.Checkbutton(checkbuttons_frame, text=os.path.splitext(os.path.basename(file_path))[0], variable=log_var, command=draw_scatter)
                checkbutton.pack(side=tk.TOP, anchor='w')

                log_text_left.bind("<Button-1>", lambda e, idx=i: on_log_click(e, idx, 'left'))
                log_text_right.bind("<Button-1>", lambda e, idx=i: on_log_click(e, idx, 'right'))

            fig.set_size_inches(15, max(4, len(file_paths)/2))
            draw_scatter()

    browse_button = tk.Button(control_frame, text="Browse Files", command=browse_files)
    browse_button.pack(side=tk.TOP, anchor='w')

    reload_button = tk.Button(control_frame, text="Reload", command=reload_logs)
    reload_button.pack(side=tk.TOP, anchor='w')

    def on_click(event):
        if event.xdata is None or event.ydata is None or event.key == 'control':
            return

        visible_indices = [i for i, var in enumerate(log_vars) if var.get()]
        y_index = int(round(event.ydata))
        if y_index < 0 or y_index >= len(visible_indices):
            return

        actual_index = visible_indices[y_index]
        transactions = transactions_list[actual_index]
        kdtree = kdtrees[actual_index]

        _, nearest_idx = kdtree.query([event.xdata])
        nearest_trans = transactions[nearest_idx]

        log_text_left = text_widgets_left[actual_index]
        log_text_right = text_widgets_right[actual_index]

        if event.button == 1:
            log_text_left.config(state=tk.NORMAL)
            log_text_left.tag_remove('highlight', '1.0', 'end')
            line_number = transactions.index(nearest_trans)
            log_text_left.see(f"{line_number + 1}.0")
            log_text_left.tag_add('highlight', f"{line_number + 1}.0", f"{line_number + 2}.0")
            log_text_left.tag_config('highlight', background='yellow')
            log_text_left.config(state=tk.DISABLED)
            notebook_left.select(actual_index)
            time_value = float(nearest_trans['time'].replace(' ns', ''))
            highlight_point(time_value, y_index)
        elif event.button == 2:
            log_text_right.config(state=tk.NORMAL)
            log_text_right.tag_remove('highlight', '1.0', 'end')
            line_number = transactions.index(nearest_trans)
            log_text_right.see(f"{line_number + 1}.0")
            log_text_right.tag_add('highlight', f"{line_number + 1}.0", f"{line_number + 2}.0")
            log_text_right.tag_config('highlight', background='yellow')
            log_text_right.config(state=tk.DISABLED)
            notebook_right.select(actual_index)
            time_value = float(nearest_trans['time'].replace(' ns', ''))
            highlight_second_point(time_value, y_index)

    def on_log_click(event, idx, notebook_side):
        if notebook_side == 'left':
            log_text = text_widgets_left[idx]
        else:
            log_text = text_widgets_right[idx]
        
        line_index = log_text.index("@%s,%s" % (event.x, event.y)).split('.')[0]
        line_number = int(line_index) - 1

        if 0 <= line_number < len(transactions_list[idx]):
            trans = transactions_list[idx][line_number]
            log_text.config(state=tk.NORMAL)
            log_text.tag_remove('highlight', '1.0', 'end')
            log_text.tag_add('highlight', f"{line_index}.0", f"{str(int(line_index) + 1)}.0")
            log_text.tag_config('highlight', background='yellow')
            log_text.config(state=tk.DISABLED)

            time_value = float(trans['time'].replace(' ns', ''))
            visible_indices = [i for i, var in enumerate(log_vars) if var.get()]
            y_index = visible_indices.index(idx)
            if notebook_side == 'left':
                highlight_point(time_value, y_index)
            else:
                highlight_second_point(time_value, y_index)

    def highlight_point(time_value, y_index):
        global highlight_marker
        if highlight_marker:
            try:
                highlight_marker.remove()
            except ValueError:
                pass

        x_min, x_max = ax.get_xlim()
        if time_value < x_min or time_value > x_max:
            delta_x_div2 = (x_max - x_min)/2
            ax.set_xlim(time_value - delta_x_div2, time_value + delta_x_div2)
        highlight_marker = ax.axvline(x=time_value, color='red', linestyle='--', linewidth=2)
        fig.canvas.draw()
        show_time_difference()

    def highlight_second_point(time_value, y_index):
        global second_marker
        if second_marker:
            try:
                second_marker.remove()
            except ValueError:
                pass

        x_min, x_max = ax.get_xlim()
        if time_value < x_min or time_value > x_max:
            delta_x_div2 = (x_max - x_min)/2
            ax.set_xlim(time_value - delta_x_div2, time_value + delta_x_div2)
        second_marker = ax.axvline(x=time_value, color='orange', linestyle='--', linewidth=2)
        fig.canvas.draw()
        show_time_difference()

    def show_time_difference():
        global time_diff_text
        if highlight_marker and second_marker:
            x1 = highlight_marker.get_xdata()[0]
            x2 = second_marker.get_xdata()[0]
            time_diff = abs(x2 - x1)
            if time_diff_text:
                try:
                    time_diff_text.remove()
                except ValueError:
                    pass
            time_diff_text = ax.text(0.05, 0.95, f'DT: {time_diff:.2f} ns', transform=ax.transAxes, horizontalalignment='left', verticalalignment='top', bbox=dict(facecolor='white', alpha=0.8))
            fig.canvas.draw()

    fig.canvas.mpl_connect('button_press_event', on_click)

    def limit_zoom(event):
        if event.name == 'scroll_event' and event.key == 'control':
            if event.step > 0:
                scale_factor = 0.9
            else:
                scale_factor = 1.1

            x_min, x_max = ax.get_xlim()
            x_center = event.xdata
            new_x_range = (x_max - x_min) * scale_factor
            new_x_min = x_center - (x_center - x_min) * scale_factor
            new_x_max = x_center + (x_max - x_center) * scale_factor

            ax.set_xlim(new_x_min, new_x_max)
            fig.canvas.draw()

    fig.canvas.mpl_connect('scroll_event', limit_zoom)

    pan_start = None

    def on_mouse_press(event):
        nonlocal pan_start
        if event.button == 1 and event.key == 'control':
            pan_start = event.xdata

    def on_mouse_release(event):
        nonlocal pan_start
        pan_start = None

    def on_mouse_move(event):
        if pan_start is not None and event.xdata is not None:
            x_min, x_max = ax.get_xlim()
            dx = pan_start - event.xdata
            ax.set_xlim(x_min + dx, x_max + dx)
            fig.canvas.draw()

    fig.canvas.mpl_connect('button_press_event', on_mouse_press)
    fig.canvas.mpl_connect('button_release_event', on_mouse_release)
    fig.canvas.mpl_connect('motion_notify_event', on_mouse_move)

    root.after(100, browse_files)

    plt.show()

    root.mainloop()

if __name__ == "__main__":
    main()
