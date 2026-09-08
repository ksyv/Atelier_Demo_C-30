#!/usr/bin/env python3
"""
EXEMPLE DE GESTION COMPLÈTE DES EXCEPTIONS
Ce script illustre l'utilisation de try, except, else, finally et raise.
Objectif : Calculer un prix unitaire de manière sécurisée (programmation défensive).
"""

def get_unit_price(item_data, item_name="Inconnu"):
    # 1. LE BLOC TRY : "La zone de danger"
    # On y place uniquement le code susceptible de provoquer une erreur.
    try: 
        # Risque 1 : Que se passe-t-il si les clés n'existent pas dans le dictionnaire ?
        # -> Lèvera une exception KeyError.
        total_price = item_data['total_value']
        quantity = item_data['quantity']

        # Risque 2 : Les données sont techniquement valides pour Python, 
        # mais absurdes pour notre logique métier (un prix négatif).
        # On utilise 'raise' pour déclencher VOLONTAIREMENT une exception.
        if total_price < 0:
            raise ValueError("Le prix total ne peut être négatif !")

        # Risque 3 : Que se passe-t-il si la quantité est égale à 0 ?
        # -> Lèvera une exception ZeroDivisionError.
        unit_price = total_price / quantity

    # 2. LES BLOCS EXCEPT : "Les filets de sécurité"
    # On capture les erreurs SPÉCIFIQUES une par une. 
    # Règle d'or : On n'utilise jamais un "except:" tout seul.

    except ZeroDivisionError:
        # S'exécute si on a tenté de diviser par zéro (quantité = 0).
        print(f"[{item_name}] Erreur : Impossible de diviser par zéro. Le stock ici est vide.")
        unit_price = 0

    except KeyError as e:
        # S'exécute si on cherche une clé qui n'existe pas dans le dictionnaire.
        # L'alias "as e" permet de récupérer le nom de la clé manquante.
        print(f"[{item_name}] Erreur de donnée : Il manque la clé {e}")
        unit_price = None

    except ValueError as e:
        # S'exécute si on a déclenché le 'raise ValueError' plus haut.
        # "e" contiendra le message "Le prix total ne peut être négatif !".
        print(f"[{item_name}] Règle métier violée : {e}")
        unit_price = None

    # 3. LE BLOC ELSE : "La zone de succès pur"
    # Il s'exécute UNIQUEMENT si le bloc 'try' est arrivé à la fin SANS AUCUNE ERREUR.
    # C'est ici qu'on met la suite logique du traitement si tout s'est bien passé.
    else:
        print(f"[{item_name}] Calcul réussi !")

    # 4. LE BLOC FINALLY : "L'agent d'entretien"
    # Il s'exécute TOUJOURS, qu'il y ait eu un succès (else) ou une erreur (except).
    # Très utile pour fermer un fichier, clore une connexion base de données, ou faire des logs.
    finally:
        print(f"[{item_name}] ---- Fin du traitement ----\n")

    # On retourne la valeur finale (qui peut être un chiffre, 0, ou None selon ce qui s'est passé).
    return unit_price


# ==========================================
# ZONE DE TESTS (Simulations des différents scénarios)
# ==========================================

# Cas 1 : Le "Happy Path". Tout est correct. (Déclenche le 'else')
apples = {'total_value': 50, 'quantity': 10}

# Cas 2 : Test de la division par zéro. (Déclenche le 'except ZeroDivisionError')
bananas = {'total_value': 0, 'quantity': 0}

# Cas 3 : Test de la donnée manquante. (Déclenche le 'except KeyError')
oranges = {'total_value' : 30}

# Cas 4 : Test de la règle métier. (Déclenche le 'raise' puis le 'except ValueError')
mangos = {'total_value': -50, 'quantity': 10}


print("--- DÉMARRAGE DU SCRIPT ---\n")
print(f"--> Résultat final : {get_unit_price(apples, 'pommes')}\n")
print(f"--> Résultat final : {get_unit_price(bananas, 'bananes')}\n")
print(f"--> Résultat final : {get_unit_price(oranges, 'oranges')}\n")
print(f"--> Résultat final : {get_unit_price(mangos, 'mangues')}\n")

'''
Décryptage des flux d'exécution :
* 🍎 Cas des pommes : Le code passe dans le try jusqu'au bout -> puis dans le else (car aucune erreur) -> puis dans le finally.
* 🍌 Cas des bananes : Le code plante dans le try à l'étape de la division -> saute immédiatement dans le except ZeroDivisionError -> puis va dans le finally. Le else est ignoré.
* 🍊 Cas des oranges : Le code plante dans le try dès la première ligne (clé 'quantity' introuvable) -> saute immédiatement dans le except KeyError -> puis va dans le finally. L'opération mathématique n'est même pas tentée.
* 🥭 Cas des mangues : Le code détecte une donnée aberrante (-50) -> déclenche lui-même une erreur avec raise ValueError -> cette erreur est interceptée juste en dessous par le except ValueError -> puis on passe au finally.
* 💡 L'astuce à retenir : Dès qu'une erreur se produit (ou est levée avec raise) dans le bloc try, l'exécution de ce bloc s'arrête instantanément et Python cherche le bloc except correspondant.
'''