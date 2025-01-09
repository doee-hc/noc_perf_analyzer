import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk

class Fifo_canvas:
    def __init__(self, canvas, x, y, width=200, height=20):
        self.canvas = canvas
        self.x = x
        self.y = y
        self.width = width
        self.height = height
        self.data = 0
        self.max_data = 100  # FIFO 最大容量
        self.progress_bar = self.canvas.create_rectangle(x, y, x + width, y + height, fill='white', outline='black')
        self.blank_bar = 0
        self.canvas.bind("<Button1-Motion>", self.move)
        self.canvas.bind("<ButtonRelease-1>", self.release)

    def move(self, event):
        x, y = event.x, event.y
        self.x = x - self.width // 2  # 使得鼠标在进度条中心拖动
        self.y = y - self.height // 2
        self.canvas.coords(self.progress_bar, self.x, self.y, self.x + self.width, self.y + self.height)
        #self.update_display()

    def release(self, event):
        pass  # 可以在这里处理释放后的逻辑

    def update_data(self, new_data):
        self.data = new_data
        if self.data > self.max_data:
            self.data = self.max_data
        self.update_display()

    def update_display(self):
        filled_width = (self.data / self.max_data) * self.width
        self.canvas.delete(self.progress_bar)
        self.canvas.delete(self.blank_bar)
        self.progress_bar = self.canvas.create_rectangle(self.x, self.y, self.x + filled_width, self.y + self.height, fill='blue', outline='black')
        # 画出未填充部分
        self.blank_bar = self.canvas.create_rectangle(self.x + filled_width, self.y, self.x + self.width, self.y + self.height, fill='white', outline='black')

class FifoApp:
    def __init__(self, master):
        self.master = master
        self.master.title("FIFO 状态显示")

        # 加载默认架构图
        self.background_image = Image.open("noc_arch.png")
        self.background_photo = ImageTk.PhotoImage(self.background_image)

        # 根据图像大小调整窗口
        self.master.geometry(f"{self.background_image.width}x{self.background_image.height}")

        self.canvas = tk.Canvas(master, bg='white', width=self.background_image.width, height=self.background_image.height)
        self.canvas.pack(fill=tk.BOTH, expand=True)
        self.canvas.create_image(0, 0, image=self.background_photo, anchor=tk.NW)

        self.fifos = []

        # 添加默认 FIFO
        self.add_fifo(100, 100)
        self.add_fifo(300, 150)

        # 示例：更新 FIFO 数据量
        self.update_fifo_data(0, 50)  # 更新第一个 FIFO 的数据量为 50
        self.update_fifo_data(1, 20)   # 更新第二个 FIFO 的数据量为 20

    def add_fifo(self, x, y):
        fifo = Fifo(self.canvas, x, y)
        self.fifos.append(fifo)

    def update_fifo_data(self, fifo_index, new_data):
        if 0 <= fifo_index < len(self.fifos):
            self.fifos[fifo_index].update_data(new_data)

if __name__ == "__main__":
    root = tk.Tk()
    app = FifoApp(root)
    root.mainloop()

