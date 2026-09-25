#!/usr/bin/env python3

def create_register(filename, guest_name):
    with open(filename, mode="w", encoding="utf-8") as f:
        f.write(f"---Registre de l'Auberge ---\n")
        f.write(f"Client : {guest_name}\n")
    print(f"{guest_name} a été inscrit avec succès.")

def add_guest(filename, guest_name):
    with open(filename, mode="a", encoding="utf-8") as f:
        f.write(f"Nouveau client : {guest_name}\n")
    print(f"{guest_name} a été ajouté au registre avec succès.")

def read_register(filename):
    print("\n ---Lecture du registre ---")
    try:
        with open(filename, mode="r", encoding="utf-8") as f:
            content = f.read()
            print(content)
    except FileNotFoundError:
        print("Erreur: Le registre n'existe pas encore !")

if __name__ == "__main__":
    file_name = "guestbook.txt"

    create_register(file_name, "Arthur le Guerrier")
    add_guest(file_name, "Merlin le Mage")
    add_guest(file_name, "Lancelot le Chevalier")
    read_register(file_name)