#!/usr/bin/env python3

class Character:
    """Classe Mère: définir la base de tout personnage."""

    def __init__(self, name, health):
        self.name = name
        self.health = health

    @property
    def health(self):
        return self.__health

    @health.setter
    def health(self, value):
        if value < 0:
            self.__health = 0
        else:
            self.__health = value

    def take_damage(self, amount):
        self.health -= amount
        print(f"{self.name} subit {amount} dégâts! PV restants: {self.health}")

    def attack(self, target):
        """Un personnage de base ne sait pas comment attaquer."""
        raise NotImplementedError("La methode attack() doit être définie par la classe enfant") 

class Warrior(Character):
    """Classe Fille 1 : Hérite de Character"""

    def __init__(self, name, health=120, strength=20):
        super().__init__(name, health)
        self.strength = strength

    def attack(self, target):
        print(f"{self.name} frappe violemment {target.name} avec son épée")
        target.take_damage(self.strength)

class Mage(Character):
    """Classe Fille 2 : Hérite de Character"""

    def __init__(self, name, health=80, mana=50):
            super().__init__(name, health)
            self.mana = mana
    
    def attack(self, target):
        if self.mana >= 10:
            print(f"{self.name} lance une boule de feu mineure sur {target.name}!")
            self.mana -= 10
            target.take_damage(40)
        else:
            print(f"{self.name} n'a plus de mana et donne un petit coup de baton")
            target.take_damage(2)

boss = Character("Seigneur Démon", 500)

arthur = Warrior("Arthur", strength=50)
merlin = Mage("Merlin", mana=20)

team = [arthur, merlin]

print("---Début du combat---")
for member in team:
    member.attack(boss)

print("---vérification des types---")
print(f"Merlin est un Mage? {isinstance(merlin, Mage)}")
print(f"Merlin est un Character ?{isinstance(merlin, Character)}")
print(f"Arthur est un Mage? {isinstance(arthur, Mage)}")
print(f"Arthur est un Character ?{isinstance(arthur, Character)}")

for member in team:
    member.attack(boss)

for member in team:
    member.attack(boss)

for member in team:
    member.attack(boss)

