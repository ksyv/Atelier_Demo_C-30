#!/usr/bin/env python3

prenom = "Alice"
print("Adresse initiale:", id(prenom))

prenom = prenom + "Dupond"
print("Nouvelle adresse:", id(prenom))


panier = ["Pomme", "Poire"]
print("Adresse initiale panier:", id(panier))

panier.append("Fraise")
print("Adresse panier après ajout:", id(panier))

bordeaux_gps = (44.837, -0.579)
latitude = bordeaux_gps[0]
print(f"Latitude: {latitude}")

gps_temporaire = list(bordeaux_gps)
gps_temporaire[0] = 45.000
nouveau_gps = tuple(gps_temporaire)
print(nouveau_gps)

taches_du_jour = ["Coder", "Manger", "Dormir"]
premiere_tache = taches_du_jour[0]
taches_du_jour[1] = "Boire du café"
print("Après modification :", taches_du_jour)
taches_du_jour.pop(0)
print("liste finale", taches_du_jour)

user_profil = {
    "username": "pseudo1",
    "role": "student",
    "score": 42
}

print("Le rôle de l'utilisateur est :", user_profil["role"])
 #print("L'age de l'utilisateur est :", user_profil["age"])
print("age sécurisé:", user_profil.get("age", "non renseigné"))

user_profil["score"] = 100
user_profil["active"] = True

print("Profil mis à jour:", user_profil)

tags_article = {"python", "dev", "novice"}
print("Est-ce que 'dev' est là ?", "dev" in tags_article)

tags_article.add("tutorial")
tags_article.add("python")

print("Mes tags:", tags_article)


