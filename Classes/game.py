#!/usr/bin/env python3

class Player:
    """Classe définissant un joueur"""

    def __init__(self, name, health=100):
        self.name = name
        self.health = health

    @property
    def health(self):
        return self.__health

    @health.setter
    def health(self, value):
        if not isinstance(value, int):
            raise TypeError("La santé (health) doit être un entier")
        if value < 0:
            self.__health = 0
        else:
            self.__health = value

    def take_damage(self, amount):
        self.health -= amount

    
    def __str__(self):
        status= "Vivant" if self.health > 0 else "Mort"
        return f"Joueur: {self.name} | PV: {self.health} ({status})"


player1 = Player("Arthur", 100)
player2 = Player("Merlin", 80)

try: 
    player1.health = "invincible"
except Exception as e:
    print(f"Erreur bloquée: {e}")

player1.take_damage(150)
print(f"Santé de {player1.name} est de {player1.health}")

print(player1)

