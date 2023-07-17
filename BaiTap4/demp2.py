import xml.etree.ElementTree as ET


tree = ET.parse("Conchimnon_1.musicxml")
chords = tree.findall(".//measure")


def get_chord(chord_symbol):
    tree = ET.parse("chords_3_4.xml")
    root = tree.getroot()
    chords = root.findall("chord")
    for chord in chords:
        if chord.get('name') == chord_symbol:
            return chord
    return 'Not found chord in data!'


for i, chord in enumerate(chords):
    if i == 1:
        chord_temp = get_chord('F')
        for data in chord_temp:
            chord.append(data)
        tree.write('Conchimnon_1.musicxml')
