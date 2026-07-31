#include <stdio.h>

// ============================================================================
// PARTIE 1 : LES FONDATIONS (Structures = Données + Comportements)
// ============================================================================

/*
 * LA STRUCTURE HERO (L'équivalent d'un "Objet")
 * Au lieu d'avoir des variables éparpillées (pv, or, arme), on regroupe tout.
 * La magie ici, c'est le pointeur de fonction : il permet à notre Héros
 * de posséder sa propre action. On sépare la "donnée" du "comportement".
 */
typedef struct Hero {
    int pv;
    int or;
    char *arme;
    void (*attack)(char *target); // Pointeur vers une fonction d'attaque
} Hero;

/*
 * LA STRUCTURE DE ROUTAGE (Le dictionnaire d'actions)
 * Exactement comme 'op_t' dans le projet 3-calc !
 * Elle associe une "Clé" (le caractère tapé par le joueur) 
 * à une "Valeur" (la fonction à exécuter).
 */
typedef struct ActionMenu {
    char touche;                  // Exemple : 'S' pour Soigner
    void (*action_func)(Hero *h); // La fonction correspondante
} ActionMenu;


// ============================================================================
// PARTIE 2 : LES COMPORTEMENTS POSSIBLES (Les "Méthodes")
// ============================================================================

// --- 2A. Les types d'attaques (pour la variable mon_hero.attack) ---

void warrior_attack(char *target){
    printf("-> [COMPETENCE] GRAAAAAA Je vais découper %s en deux !!! (-50pv)\n", target);
}

void mage_attack(char *target){
    printf("-> [COMPETENCE] Alakazam ! Boule de feu sur %s !!! (-80pv)\n", target);
}

// --- 2B. Les actions du menu (pour notre dictionnaire d'actions) ---

void se_soigner(Hero *h) {
    h->pv += 50;
    printf("-> [ACTION] Le Héros boit une potion magique ! (+50 PV)\n");
}

void fuir(Hero *h) {
    printf("-> [ACTION] Le Héros fuit lâchement le combat...\n");
}


// ============================================================================
// PARTIE 3 : LE DISPATCHER (Le Cerveau du système d'événements)
// ============================================================================

/*
 * get_action_func : Le "Routeur"
 * Signature effrayante mais logique implacable :
 * Elle prend un 'char' en entrée, et RETOURNE un pointeur de fonction 
 * (qui lui-même prend un 'Hero *' et renvoie 'void').
 */
void (*get_action_func(char input))(Hero *) {
    
    // 1. Notre tableau de correspondances (Le dictionnaire)
    ActionMenu menu[] = {
        {'S', se_soigner},
        {'F', fuir},
        {'\0', NULL} // Sécurité : la case vide qui marque la fin du tableau
    };

    int i = 0;

    // 2. On parcourt le tableau. 
    // On s'arrête si on trouve la bonne touche, OU si on arrive à la fin ('\0').
    while (menu[i].touche != '\0' && menu[i].touche != input) {
        i++;
    }

    // 3. On retourne l'adresse de la fonction trouvée (ou NULL si la touche n'existe pas)
    return menu[i].action_func;
}


// ============================================================================
// PARTIE 4 : LE MOTEUR DU JEU (Manipulation de la structure Hero)
// ============================================================================

/*
 * INITIALISATION : On passe l'adresse du héros (Hero *h) pour pouvoir 
 * modifier son contenu original, et non une copie.
 */
void initialiser_hero(Hero *h, char **catalogue) {
    h->pv = 100;
    h->or = 15;
    h->arme = catalogue[0]; // On pointe vers "Dague rouillée"
    
    printf("\n=== DEBUT DE L'AVENTURE ===\n");
    printf("=> Le Héros entre dans le donjon.\n");
}

void afficher_status(Hero *h) {
    printf("\n[ STATUS : %d PV | %d or | Arme: %s ]\n", h->pv, h->or, h->arme);
    printf("------------------------------------------------\n");
}

void declencher_piege_acide(Hero *h, char **catalogue) {
    printf("\n*CLIC* Un piège à acide se déclenche !\n");
    h->pv -= 30;
    h->arme = catalogue[3]; // On redirige le pointeur vers "Mains nues"
    printf("=> Vous perdez 30 PV et votre arme fond !\n");
}

/*
 * MISE A JOUR : 'ramasser_loot' a été mise à jour pour utiliser 'Hero *h'
 * au lieu de l'ancien double pointeur 'char **arme_joueur'.
 */
void ramasser_loot(Hero *h, char **catalogue, int index_loot) {
    printf("\nVous trouvez un coffre mystérieux...\n");
    h->arme = catalogue[index_loot]; 
    printf("=> Vous vous équipez de : %s\n", h->arme);
}


// ============================================================================
// PARTIE 5 : LE MAIN (L'exécution de l'histoire)
// ============================================================================
int main() {
    // 1. LA BASE DE DONNÉES (Assets statiques)
    char *inventaire[4] = {
        "Dague rouillée", // Index 0
        "Epee longue",    // Index 1
        "Hache de feu",   // Index 2
        "Mains nues"      // Index 3
    };

    // 2. CRÉATION DU HÉROS
    Hero mon_hero;

    // 3. LE GAMEPLAY
    initialiser_hero(&mon_hero, inventaire);
    
    // On lui assigne un comportement par défaut (Guerrier)
    mon_hero.attack = &warrior_attack;
    afficher_status(&mon_hero);
    
    // Événement : Le Piège
    declencher_piege_acide(&mon_hero, inventaire);
    afficher_status(&mon_hero);
    
    // Événement : Le Combat (Utilisation du pointeur de fonction embarqué)
    printf("\nUn gobelin sauvage apparait !\n");
    mon_hero.attack("le gobelin sauvage"); // Appelle warrior_attack()

    // Événement : Changement de classe dynamique
    printf("\nLe heros lit un grimoire interdit et devient Mage !\n");
    mon_hero.attack = &mage_attack; // On écrase le pointeur par la nouvelle fonction

    printf("\nUn troll de glace apparait !\n");
    mon_hero.attack("le troll de glace"); // Appelle mage_attack() sans changer le code de l'appel !

    afficher_status(&mon_hero);

    // Événement : Action du joueur via le Dispatcher (Le Routeur)
    printf("\n=== TOUR DU JOUEUR ===\n");
    char touche_joueur = 'S'; // Le joueur simule l'appui sur la touche 'S'
    printf("Le joueur appuie sur la touche '%c'\n", touche_joueur);
    
    // On interroge notre routeur : "Quelle fonction correspond à 'S' ?"
    void (*mon_action)(Hero *) = get_action_func(touche_joueur);

    // On vérifie que la touche existe bien dans le dictionnaire
    if (mon_action != NULL) {
        mon_action(&mon_hero); // On exécute l'action trouvée en lui passant notre héros
    } else {
        printf("Touche invalide !\n");
    }

    afficher_status(&mon_hero);

    printf("=== FIN DE L'AVENTURE ===\n");

    return 0; 
}