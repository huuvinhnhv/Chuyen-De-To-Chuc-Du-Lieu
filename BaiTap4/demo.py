import xml.etree.ElementTree as ET


# def change_dynamics(measure_index, note_index, dynamics_value):
#     # Đọc file XML
#     tree = ET.parse('DemoDynamic.musicxml')

#     # Tìm thẻ "Measure" tại ô nhạc thứ measure_index
#     measure = tree.findall('.//measure')[measure_index]

#     # Tìm thẻ "Note" tại ô nhạc thứ note_index trong thẻ "Measure"
#     note = measure.findall('.//note')[note_index]

#     # Thay đổi giá trị của thuộc tính "dynamics"
#     note.set('dynamics', dynamics_value)

#     # Lưu lại file XML đã được chỉnh sửa
#     tree.write('DemoDynamic.musicxml')


# change_dynamics(0, 0, 'ff')
tree = ET.parse('DemoDynamic.musicxml')


direction = ET.Element("direction", {'placement': 'below'})
direction_type = ET.SubElement(direction, 'direction_type')
dynamics = ET.SubElement(direction_type, 'dynamics')
p = ET.SubElement(dynamics, 'p')
sound = ET.SubElement(direction, 'sound', {'dynamics': '54.44'})

# for i, data in enumerate(child):
#     if data.tag == 'direction' and child[i+1].tag == 'child':
#         data.get()
# child.insert(1, direction)


def get_dynamics_tag(dynamics_symbol):
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
    direction_type = ET.SubElement(direction, 'direction_type')
    dynamics = ET.SubElement(direction_type, 'dynamics')
    ET.SubElement(dynamics, f'{dynamics_symbol}')
    volume = dynamics_to_volume.get(dynamics_symbol, 0)
    ET.SubElement(direction, 'sound', {
                  'dynamics': f'{volume}'})
    return direction


def search_dynamic(measure_index, note_index):
    tree = ET.parse('DemoDynamic.musicxml')
    measure = tree.findall('.//measure')[measure_index]
    count = -1
    for i, data in enumerate(measure):
        if data.tag == 'note':
            count += 1
            if count == note_index:
                if measure[i-1].tag == 'direction' and measure[i-1].findall('.//dynamics') != None:
                    temp = measure[i-1].find('.//dynamics')
                    for data in temp:
                        return data.tag
                else:
                    return "None"
    # for i, data in enumerate(measure):
    #     print(f'{i}:{data}')
    tree.write('DemoDynamic.musicxml')


search_dynamic(1, 1)

# tree.write('DemoDynamic.musicxml')
# print(child)
# note = measure[0].findall('.//note')
# dynamics = measure[0].findall('.//dynamics')
# print(dynamics)

# note.find('direction')
