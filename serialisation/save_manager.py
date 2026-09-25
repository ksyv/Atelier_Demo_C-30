#!/usr/bin/env python3
import json
import pickle

game_save = {
    "player_name": "Arthur",
    "level": 5,
    "inventory": ["Epee", "Potion de soin", "Bouclier"],
    "is-alive": True
}

print("1. Sauvegarde en JSON")

with open("save.json", mode="w", encoding="utf-8") as f:
    json.dump(game_save, f, indent=4)

print("Fichier save.json créé")

print("2. Chargement depuis le JSON")
with open("save.json", mode="r", encoding="utf-8") as f:
    loaded_data = json.load(f)

print(f"Données chargées: {loaded_data}")
print(f"Type de la variable: {type(loaded_data)}")

#--- les limites du json
class Warrior:
    def __init__(self, name, health):
        self.name = name
        self.health = health

    def attack(self):
        print(f"{self.name} attaque!")

arthur = Warrior("Arthur", 150)

print("3. Tentative de sauvegarde de la classe avec Json")
try: 
    with open("warrior.json", mode="w", encoding="utf-8") as f:
        json.dump(arthur, f)
except TypeError as e:
    print(f"Crash JSON: {e}")

print("4. Sauvegarde de la classe avec Pickle")

with open("warrior.pkl", mode="wb") as f:
    pickle.dump(arthur, f)

print("Fichier warrior.pkl créé!")

print("5. Chargement depuis Pickle")
with open("warrior.pkl", mode="rb") as f:
    loaded_warrior = pickle.load(f)
print(f"Objet chargé: {loaded_warrior.name} (PV: {loaded_warrior.health})")

loaded_warrior.attack()