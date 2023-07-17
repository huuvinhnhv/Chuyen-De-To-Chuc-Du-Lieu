import os
import tkinter as tk
from tkinter import StringVar, filedialog
from music21 import *
import threading
import xml.etree.ElementTree as ET
from tkinter import *
from tkinter.ttk import *


class MusicXMLReader:
    def __init__(self, file_path):
        self.file_path = file_path
        self.tree = ET.parse(file_path)
        self.root = self.tree.getroot()
        self.TONG_MAPPING = {
            -7: 'Cb',
            -6: 'Gb',
            -5: 'Db',
            -4: 'Ab',
            -3: 'Eb',
            -2: 'Bb',
            -1: 'F',
            0: 'C',
            1: 'G',
            2: 'D',
            3: 'A',
            4: 'E',
            5: 'B',
            6: 'F#',
            7: 'C#'
        }

    def get_staves_count(self):
        measure = self.tree.findall('.//measure')[0]
        attributes_elements = measure.find('attributes')
        if attributes_elements.find('staves') == None:
            return "1"
        return attributes_elements.find('staves').text

    def get_key_signature(self):
        key_element = self.root.find('.//key')
        if key_element is not None:
            fifths = key_element.findtext('fifths')
            if fifths is not None:
                fifths = int(fifths)
                if fifths in self.TONG_MAPPING:
                    return self.TONG_MAPPING[fifths]
        return "Not Found"

    def transpose(self, value):
        score = converter.parse(self.file_path)
        new_score = score.transpose(value)
        for part in new_score.parts:
            for measure in part.getElementsByClass('Measure'):
                key_sig = measure.keySignature
                if key_sig is not None:
                    new_key_sig = key_sig.transpose(value)
                    measure.replace(key_sig, new_key_sig)

        new_score.write('musicxml', (self.file_path))

    def get_tempo(self):
        # Tìm và lấy element chứa thông tin về tempo
        sound_element = self.root.find('.//sound')
        if sound_element is not None:
            tempo = sound_element.get('tempo')
            if tempo is not None:
                return int(tempo)
        return None

    def update_tempo(self, tempo2):
        # Tăng giá trị tempo lên một hằng số nhất định
        sound_element = self.root.find('.//sound')
        per_minute = self.root.find('.//per-minute')
        print(per_minute)
        if sound_element is not None and per_minute is not None:
            tempo = sound_element.get('tempo')
            if tempo is not None:
                sound_element.set('tempo', str(tempo2))
                per_minute.text = str(tempo2)

    def save_to_file(self):
        # Ghi đè file MusicXML
        self.tree.write(self.file_path)

    def get_time_signature(self):
        # Tìm và lấy element chứa thông tin về nhịp
        time_element = self.root.find('.//time')
        if time_element is not None:
            beats = int(time_element.find('beats').text)
            beat_type = int(time_element.find('beat-type').text)
            return f"{beats}/{beat_type}"
        return "Not Found"

    def get_tempo(self):
        # Tìm và lấy element chứa thông tin về tempo
        sound_element = self.root.find('.//sound')
        if sound_element is not None:
            tempo = sound_element.get('tempo')
            if tempo is not None:
                return int(tempo)
        return None

    def update_tempo(self, tempo2):
        # Tăng giá trị tempo lên một hằng số nhất định
        metronome_element = self.root.find('.//metronome')
        if metronome_element is not None:
            per_minute_element = metronome_element.find('.//per-minute')
            if per_minute_element is not None:
                per_minute_element.text = str(tempo2)
                sound_element = self.root.find('.//sound')
                if sound_element is not None:
                    sound_element.set('tempo', str(tempo2))
                self.tree.write(self.file_path)

    def save_to_file(self):
        # Ghi đè file MusicXML
        self.tree.write(self.file_path)

    def get_time_signature(self):
        # Tìm và lấy element chứa thông tin về nhịp
        time_element = self.root.find('.//time')
        if time_element is not None:
            beats = int(time_element.find('beats').text)
            beat_type = int(time_element.find('beat-type').text)
            return f"{beats}/{beat_type}"
        return "Not Found"

    def search_dynamic(self, measure_index, note_index):
        if note_index <= -1 or measure_index <= -1:
            return f"Index < 0!"
        tree = ET.parse(self.file_path)
        measure = tree.findall('.//measure')[measure_index]
        count = -1
        for i, data in enumerate(measure):
            if data.tag == 'note':
                count += 1
                if count == note_index:
                    if i-1 >= 0 and measure[i-1].tag == 'direction' and measure[i-1].findall('.//dynamics') != None:
                        temp = measure[i-1].find('.//dynamics')
                        if temp is None:
                            return "None"
                        for data in temp:
                            return data.tag
                    return "None"
        if count + 1 <= note_index:
            return f"Only {count+1} Note"


class Player:
    def __init__(self):
        self.playing = False
        self.file_path = None
        self.stream = None


class Controller:
    def __init__(self, player):
        self.player = player

    def remove_dynamics(self, measure_index, note_index):
        if note_index <= -1 or measure_index <= -1:
            return f"Index < 0!"
        tree = ET.parse(self.player.file_path)
        measure = tree.findall('.//measure')[measure_index]
        count = -1
        for i, data in enumerate(measure):
            if data.tag == 'note':
                count += 1
                if count == note_index:
                    if i-1 >= 0 and measure[i-1].tag == 'direction' and measure[i-1].findall('.//dynamics') != None:
                        temp = measure[i-1]
                        measure.remove(temp)
                        tree.write(self.player.file_path)
                        return "Done"

    def get_dynamics_tag(self, dynamics_symbol):
        dynamics_to_volume = {
            "ppp": 17.78,
            "pp": 36.67,
            "p": 54.44,
            "mp": 71.11,
            "mf": 88.89,
            "f": 106.67,
            "ff": 124.44,
            "fff": 140.00
        }
        direction = ET.Element("direction", {'placement': 'below'})
        direction_type = ET.SubElement(direction, 'direction-type')
        dynamics = ET.SubElement(direction_type, 'dynamics')
        ET.SubElement(dynamics, f'{dynamics_symbol}')
        volume = dynamics_to_volume.get(dynamics_symbol, 0)
        ET.SubElement(direction, 'sound', {
                      'dynamics': f'{volume}'})
        return direction

    def dynamic_change(self, measure_index, note_index, dynamics_symbol):
        if note_index <= -1 or measure_index <= -1:
            return f"Index < 0!"
        tree = ET.parse(self.player.file_path)
        measure = tree.findall('.//measure')[measure_index]
        count = -1
        for i, data in enumerate(measure):
            if data.tag == 'note':
                count += 1
                if count == note_index:
                    if i-1 >= 0 and measure[i-1].tag == 'direction' and measure[i-1].findall('.//dynamics') != None:
                        temp = measure[i-1]
                        temp2 = self.get_dynamics_tag(f'{dynamics_symbol}')
                        measure.insert(i, temp2)
                        measure.remove(temp)
                        break
                    else:
                        temp2 = self.get_dynamics_tag(f'{dynamics_symbol}')
                        measure.insert(i, temp2)
                        break
        tree.write(self.player.file_path)

    def open_file(self):
        file_path = filedialog.askopenfilename(
            defaultextension=".xml", filetypes=[("MUSICXML Files", "*.musicxml"), ("XML Files", "*.xml")])
        if file_path:
            self.player.tree = ET.parse(file_path)
            self.player.file_path = file_path

    def play_music(self):
        if not self.player.playing:
            score = converter.parse(self.player.file_path)
            sp = midi.realtime.StreamPlayer(score)

            def play_thread():
                self.player.stream = sp
                sp.play()
                self.player.playing = False

            self.player.playing = True
            threading.Thread(target=play_thread).start()

    def stop_music(self):
        self.player.playing = False
        self.player.stream.stop()

    def update_tempo(self, tempo):
        try:
            new_tempo = int(tempo)
            musicXMLReader = MusicXMLReader(
                self.player.file_path)
            musicXMLReader.update_tempo(new_tempo)
            musicXMLReader.save_to_file()
        except ValueError:
            print("Invalid tempo value. Please enter an integer.")
            return

    def get_time_signature(self):
        try:
            return MusicXMLReader(self.player.file_path).get_time_signature()
        except ValueError:
            print("Time signature not found!")
            return

    def get_key(self):
        try:
            return MusicXMLReader(self.player.file_path).get_key_signature()
        except ValueError:
            print("Key not found!")
            return

    def key_signature_up(self):
        try:
            MusicXMLReader(self.player.file_path).increase_key_signature()
        except ValueError:
            print("Key not found!")
            return

    def key_signature_down(self):
        try:
            MusicXMLReader(self.player.file_path).decrease_key_signature()
        except ValueError:
            print("Key not found!")
            return

    def get_tempo(self):
        try:
            return MusicXMLReader(self.player.file_path).get_tempo()
        except ValueError:
            print("Cann't read tempo value")
            return

    def get_G_clef(self, number):
        clef = ET.Element("clef", {"number": f"{number}"})
        sign = ET.SubElement(clef, "sign")
        sign.text = "G"
        line = ET.SubElement(clef, "line")
        line.text = "2"
        clef_octave = ET.SubElement(clef, "clef-octave-change")
        clef_octave.text = "-1"
        return clef

    def add_staves(self):
        if int(MusicXMLReader(self.player.file_path).get_staves_count()) >= 2:
            return
        tree = ET.parse(self.player.file_path)
        measure = tree.findall('.//measure')[0]
        attributes_elements = measure.find('attributes')
        staves_element = ET.Element('staves')
        staves_element.text = '2'
        if attributes_elements.find('staves') == None:
            attributes_elements.insert(3, staves_element)
        else:
            old_stave = attributes_elements.find('staves')
            attributes_elements.insert(3, staves_element)
            attributes_elements.remove(old_stave)
        old_G_clef = attributes_elements.find('clef')
        attributes_elements.remove(old_G_clef)
        attributes_elements.insert(4, self.get_G_clef(1))
        attributes_elements.insert(5, self.get_G_clef(2))
        tree.write(self.player.file_path)

    def get_chord(self, chord_symbol):
        tree = ET.parse("chords_3_4.xml")
        root = tree.getroot()
        chords = root.findall("chord")
        for chord in chords:
            if chord.get('name') == chord_symbol:
                return chord
        return 'Not found chord in data!'

    def add_chord_to_measure(self, measure_index, chord_symbol):
        chord = self.get_chord(chord_symbol)
        tree = ET.parse(self.player.file_path)
        measures = tree.findall(".//measure")
        for measure in measures:
            if measure.get('number') == measure_index:
                for data in chord:
                    print(data)
                    measure.append(data)
                tree.write(self.player.file_path)
                return


class View:
    def __init__(self, master, controller):
        self.master = master
        self.controller = controller

        self.open_button = tk.Button(
            master, text="Open", command=self.open_file,
            bg="orange", fg="white", font=("Arial", 12), width=10
        )
        self.label_for_file_name = tk.Label(
            master, text="File name:", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.lable_file_name = tk.Label(
            master, text="", bg="gray", fg="white", font=("Arial", 12), width=23, wraplength=300, justify="center")

        self.play_button = tk.Button(
            master, text="Play", command=self.controller.play_music,
            bg="green", fg="white", font=("Arial", 12), width=10
        )

        self.stop_button = tk.Button(
            master, text="Stop", command=self.controller.stop_music,
            bg="red", fg="white", font=("Arial", 12), width=10
        )

        self.lable_play_notice = tk.Label(
            master, text="", bg="gray", fg="red", font=("Arial", 12), width=10, wraplength=300, justify="center")

        self.label_tempo_old = tk.Label(
            master, text="Tempo:", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.label_tempo_value = tk.Label(
            master, text="", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")

        # key
        self.key_label = tk.Label(
            master, text="Key (tông): ", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.key_label_value = tk.Label(
            master, text="", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")

        # nhịp
        self.lable_time_signature = tk.Label(
            master, text="Nhịp: ", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.lable_time_signature_value = tk.Label(
            master, text="", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")

        # tăng tempo
        self.label_tempo = tk.Label(
            master, text="New tempo:", bg="violet", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.entry_tempo = tk.Entry(
            master, bg="white", fg="black", font=("Arial", 12), width=10)
        self.apply_button = tk.Button(
            master, text="Apply", command=self.apply_tempo_change,
            bg="gray", fg="white", font=("Arial", 12), width=10
        )
        # tăng giảm tông
        self.label_update_time_signature = tk.Label(
            master, text="Tông (+/-):", bg="blue", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.button_increase = tk.Button(
            master, text="Tăng", command=self.key_up,
            bg="gray", fg="white", font=("Arial", 12), width=10
        )
        self.button_decrease = tk.Button(
            master, text="Giảm", command=self.key_down,
            bg="gray", fg="white", font=("Arial", 12), width=10
        )
        # dynamic
        self.label_dynamic = tk.Label(
            master, text="Thay đổi dynamic:", bg="orange", fg="white", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.label_measure = tk.Label(
            master, text="Vị trí ô nhạc (1-based):", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.entry_measure = tk.Entry(
            master, bg="white", fg="black", font=("Arial", 12), width=10)
        self.label_note = tk.Label(
            master, text="Vị trí nốt trong ô nhạc (1-based):", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.entry_note = tk.Entry(
            master, bg="white", fg="black", font=("Arial", 12), width=10)

        self.button_dynamics_check = tk.Button(master, text="Check", command=self.check_dynamics,
                                               bg="gray", fg="white", font=("Arial", 12), width=10)
        self.label_dynamics_check = tk.Label(
            master, text="Check result:", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")
        self.label_dynamics_check_result = tk.Label(
            master, text="", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e")

        self.button_dynamics_remove = tk.Button(master, text="Remove", command=self.remove_dynamics,
                                                bg="gray", fg="white", font=("Arial", 12), width=10)
        self.label_dynamics = tk.Label(
            master, text="New dyamics:", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")

        self.dynamics = ['ppp', 'pp', 'p', 'mp', 'mf', 'f', 'ff', 'fff']
        self.dynamic_var = StringVar()
        self.dynamic_var.set(self.dynamics[0])
        self.dynamic_combo = Combobox(
            root, textvariable=self.dynamic_var, values=self.dynamics)
        self.apply_button_dynamic = tk.Button(
            master, text="Apply", command=self.add_chord,
            bg="gray", fg="white", font=("Arial", 12), width=10
        )
        # hop am
        self.label_key_add = tk.Label(
            master, text="Thêm hợp âm kèm giai điệu:", bg="gray", fg="yellow", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.label_staves_text = tk.Label(
            master, text="Số khuôn nhạc:", bg="gray", fg="yellow", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.label_staves_value = tk.Label(
            master, text="", bg="gray", fg="yellow", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.button_add_staves = tk.Button(master, text="Thêm khuôn", command=self.add_staves,
                                           bg="gray", fg="white", font=("Arial", 12), width=10)

        # apply chord
        self.label_measure_2 = tk.Label(
            master, text="Vị trí ô nhạc (1-based):", bg="gray", fg="white", font=("Arial", 12), width=10, anchor="e", wraplength=100, justify="center")
        self.entry_measure_2 = tk.Entry(
            master, bg="white", fg="black", font=("Arial", 12), width=10)

        self.chords = ['F', 'Dm', 'Gm', 'A#', 'Am', 'C', 'Em', 'D7', 'G']
        self.chords_var = StringVar()
        self.chords_var.set(self.chords[0])
        self.chords_combo = Combobox(
            root, textvariable=self.chords_var, values=self.chords)
        self.add_button_chord = tk.Button(
            master, text="Apply", command=self.add_chord,
            bg="gray", fg="white", font=("Arial", 12), width=10
        )

        # layout
        self.open_button.grid(row=0, column=0, padx=10, pady=10)
        self.play_button.grid(row=1, column=0, padx=10, pady=10)
        self.stop_button.grid(row=1, column=1, padx=10, pady=10)
        self.lable_play_notice.grid(row=1, column=2, padx=10, pady=10)
        self.label_for_file_name.grid(
            row=0, column=1, padx=10, pady=10)
        self.lable_file_name.grid(
            row=0, column=2, columnspan=2, padx=10, pady=10)
        self.label_tempo_old.grid(row=2, column=0, padx=10, pady=10)
        self.label_tempo_value.grid(row=2, column=1, padx=10, pady=10)
        self.key_label.grid(row=2, column=2, padx=10, pady=10)
        self.key_label_value.grid(row=2, column=3, padx=10, pady=10)
        self.lable_time_signature.grid(row=2, column=4, padx=10, pady=10)
        self.lable_time_signature_value.grid(row=2, column=5, padx=10, pady=10)
        self.label_tempo.grid(row=4, column=0, padx=10, pady=10)
        self.entry_tempo.grid(row=4, column=1, padx=10, pady=10)
        self.apply_button.grid(row=4, column=2, padx=10, pady=10, sticky="W")

        self.label_update_time_signature.grid(
            row=5, column=0, padx=10, pady=10)
        self.button_increase.grid(
            row=5, column=1, padx=10, pady=10)
        self.button_decrease.grid(
            row=5, column=2, padx=10, pady=10)
        # dynamic
        self.label_dynamic.grid(row=6, column=0, padx=10, pady=10)
        self.label_measure.grid(row=6, column=1, padx=10, pady=10)
        self.entry_measure.grid(row=6, column=2, padx=10, pady=10)
        self.label_note.grid(row=6, column=3, padx=10, pady=10)
        self.entry_note.grid(row=6, column=4, padx=10, pady=10)
        self.button_dynamics_check.grid(row=6, column=5, padx=10, pady=10)
        self.label_dynamics_check.grid(row=7, column=3, padx=10, pady=10)
        self.label_dynamics_check_result.grid(
            row=7, column=4, padx=10, pady=10)
        self.button_dynamics_remove.grid(row=7, column=5, padx=10, pady=10)
        self.label_dynamics.grid(row=7, column=0, padx=10, pady=10)
        self.dynamic_combo.grid(row=7, column=1, padx=10, pady=10)
        self.apply_button_dynamic.grid(row=7, column=2, padx=10, pady=10)

        self.label_key_add.grid(row=8, column=0, padx=10, pady=10)
        self.label_staves_text.grid(row=8, column=1, padx=10, pady=10)
        self.label_staves_value.grid(row=8, column=2, padx=10, pady=10)
        self.button_add_staves.grid(row=8, column=3, padx=10, pady=10)

        self.label_measure_2.grid(row=9, column=0, padx=10, pady=10)
        self.entry_measure_2.grid(row=9, column=1, padx=10, pady=10)
        self.chords_combo.grid(row=9, column=2, padx=10, pady=10)
        self.add_button_chord.grid(row=9, column=3, padx=10, pady=10)

    def add_chord(self):
        measure_index = self.entry_measure_2.get()
        chord_symbol = self.chords_combo.get()
        self.controller.add_chord_to_measure(measure_index, chord_symbol)

    def add_staves(self):
        self.controller.add_staves()
        self.get_staves()

    def get_staves(self):
        result = MusicXMLReader(
            self.controller.player.file_path).get_staves_count()
        self.label_staves_value.config(text=result)

    def get_reopen_notes(self):
        self.lable_play_notice.config(text="Re-open!")

    def remove_dynamics(self):
        measure_index = int(self.entry_measure.get()) - 1
        note_index = int(self.entry_note.get()) - 1
        dynamics_symbol = self.dynamic_combo.get()
        result = MusicXMLReader(self.controller.player.file_path).search_dynamic(
            measure_index, note_index)
        dynamics_to_volume = ["ppp", "pp", "p", "mp", "mf", "f", "ff", "fff"]
        if result not in dynamics_to_volume:
            self.label_dynamics_check_result.config(text=result)
            self.get_reopen_notes()
            return
        else:
            result1 = self.controller.remove_dynamics(
                measure_index, note_index)
            self.label_dynamics_check_result.config(text=result1)
            self.get_reopen_notes()

    def apply_dynamics_change(self):
        measure_index = int(self.entry_measure.get()) - 1
        note_index = int(self.entry_note.get()) - 1
        dynamics_symbol = self.dynamic_combo.get()
        result = MusicXMLReader(self.controller.player.file_path).search_dynamic(
            measure_index, note_index)
        self.controller.dynamic_change(
            measure_index, note_index, dynamics_symbol)
        self.check_dynamics()
        self.get_reopen_notes()

    def check_dynamics(self):
        measure_index = int(self.entry_measure.get()) - 1
        note_index = int(self.entry_note.get()) - 1
        result = MusicXMLReader(self.controller.player.file_path).search_dynamic(
            measure_index, note_index)
        self.label_dynamics_check_result.config(text=result)

    def get_dynamics(self):
        self.label_tempo_value.config(text=self.controller.get_tempo())

    def apply_tempo_change(self):
        tempo_value = self.entry_tempo.get()
        self.controller.update_tempo(tempo_value)
        self.get_tempo()

    def open_file(self):
        self.controller.open_file()
        file_path = self.controller.player.file_path
        if file_path:
            file_name = os.path.basename(file_path)
            self.lable_file_name.config(text=file_name)
            self.get_tempo()
            self.get_key()
            self.get_time_signature()
            self.lable_play_notice.config(text="")
            self.get_staves()

    def get_tempo(self):
        self.label_tempo_value.config(text=self.controller.get_tempo())

    def get_key(self):
        self.key_label_value.config(text=self.controller.get_key())

    def get_time_signature(self):
        self.lable_time_signature_value.config(
            text=self.controller.get_time_signature())

    def key_down(self):
        MusicXMLReader(self.controller.player.file_path).transpose(-1)
        self.get_key()

    def key_up(self):
        MusicXMLReader(self.controller.player.file_path).transpose(1)
        self.get_key()


class Application:
    def __init__(self, master):
        self.player = Player()
        self.controller = Controller(self.player)
        self.view = View(master, self.controller)


if __name__ == "__main__":
    root = tk.Tk()
    root.title("Music XML Basic Editor")
    root.geometry("800x600")
    app = Application(root)
    root.mainloop()
