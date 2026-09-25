#!/usr/bin/env python3
import xml.etree.ElementTree as ET

player_data = {
    "name": "Merlin",
    "role": "Mage",
    "level": 42,
    "mana": 150
}

print("Serialisation en xml")

root = ET.Element("character")
for key, value in player_data.items():
    child = ET.SubElement(root, key)
    child.text = str(value)

tree = ET.ElementTree(root)

tree.write("merlin.xml", encoding="utf-8", xml_declaration=True)
print("Fichier merlin.xml créé avec succès")

print("Deserialisation depuis le xml")
parsed_tree = ET.parse("merlin.xml")
parsed_root = parsed_tree.getroot()

print(f"Balise racine trouvée: <{parsed_root.tag}>")

rebuild_data= {}

for child in parsed_root:
    rebuild_data[child.tag] = child.text

print(f" Données reconstruites: {rebuild_data}")