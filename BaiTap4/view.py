import tkinter as tk
from tkinter import filedialog
import xml.etree.ElementTree as ET


class View:
    def __init__(self, master):
        self.master = master
        self.open_button = tk.Button(
            master, text="Open", command=self.open_file)
        self.play_button = tk.Button(
            master, text="Play", command=self.controller.play_music)
        self.pause_button = tk.Button(
            master, text="Pause", command=self.controller.pause_music)
        self.stop_button = tk.Button(
            master, text="Stop", command=self.controller.stop_music)
        self.open_button.pack()
        self.play_button.pack()
        self.pause_button.pack()
        self.stop_button.pack()

    def set_controller(self, controller):
        self.controller = controller

    def open_file(self):
        file_path = filedialog.askopenfilename(
            defaultextension=".xml", filetypes=[("XML Files", "*.xml"), ("MUSICXML Files", "*.musicxml")])
        if file_path:
            self.model.tree = ET.parse(file_path)
            self.model.root = self.model.tree.getroot()
            self.update_music_info()

    def update_music_info(self):
        # TODO: update music information in the view
        pass
