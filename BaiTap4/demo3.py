import xml.etree.ElementTree as ET


def get_G_clef(number):
    clef = ET.Element("clef", {"number": f"{number}"})
    sign = ET.SubElement(clef, "sign")
    sign.text = "G"
    line = ET.SubElement(clef, "line")
    line.text = "2"
    clef_octave = ET.SubElement(clef, "clef-octave-change")
    clef_octave.text = "-1"
    return clef


def get_F_clef():
    clef = ET.Element("clef", {"number": "2"})
    sign = ET.SubElement(clef, "sign")
    sign.text = "F"
    line = ET.SubElement(clef, "line")
    line.text = "4"
    return clef


tree = ET.parse('testkey.musicxml')
measure = tree.findall('.//measure')[0]
# get divisions
attributes_elements = measure.find('attributes')
divisions_element = measure.find('attributes').find('divisions')
divisions_value = measure.find('attributes').find('divisions').text

new_divisions = ET.Element('divisions')
new_divisions.text = '2'

staves_element = ET.Element('staves')
staves_element.text = '2'

# replace
attributes_elements.insert(3, staves_element)
# attributes_elements.insert(0, new_divisions)
# attributes_elements.remove(divisions_element)

old_G_clef = attributes_elements.find('clef')
attributes_elements.remove(old_G_clef)

new_G_clef_1 = get_G_clef(1)
new_G_clef_2 = get_G_clef(2)
# new_F_clef = get_F_clef()

attributes_elements.insert(4, new_G_clef_1)
attributes_elements.insert(5, new_G_clef_2)
# attributes_elements.append(new_F_clef)

tree.write('testkey.musicxml')
