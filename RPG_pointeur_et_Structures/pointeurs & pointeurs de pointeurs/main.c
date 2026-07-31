#include <stdio.h>

// ==========================================
// OUTILS D'AFFICHAGE
// ==========================================
// Ici, on lit juste les valeurs. On n'a pas besoin de les modifier.
// Le passage normal (par valeur) suffit amplement.
void afficher_status(int pv, int or, char *arme) {
    printf("Status : %d PV | %d or | Arme: %s\n", pv, or, arme);
    printf("-------------------------\n");
}

// ==========================================
// FONCTIONS DE GAMEPLAY (Les Pointeurs en action)
// ==========================================

/* * INITIALISATION :
 * On doit configurer 3 variables en même temps. Un 'return' est donc inutile.
 * - int *pv, int *or : On prend l'adresse des nombres pour les modifier.
 * - char **arme_joueur : L'arme est DEJA un pointeur (char *). Pour modifier vers
 * quoi ce pointeur pointe, il nous faut son adresse (donc un char **).
 * - char **catalogue : Un tableau de strings passé en paramètre devient un pointeur sur pointeurs.
 */
void initialiser_hero(int *pv, int *or, char **arme_joueur, char **catalogue) {
    *pv = 100; // Va à l'adresse des PV et écris 100
    *or = 15;  // Va à l'adresse de l'or et écris 15
    
    // Va à l'adresse de la "flèche" de l'arme du joueur, et fais-la pointer
    // vers la case 0 du catalogue (la Dague). AUCUN texte n'est copié en mémoire !
    *arme_joueur = catalogue[0]; 
    
    printf("=> Le Héros entre dans le donjon.\n");
}

/*
 * ÉVÉNEMENT MULTIPLE : LE PIÈGE
 * Modifie la vie ET l'équipement simultanément.
 */
void declencher_piege_acide(int *pv, char **arme_joueur, char **catalogue) {
    printf("Un piège à acide se déclenche!\n");
    
    // Modification n°1 : On soustrait 30 directement dans la variable du main
    *pv -= 30;
    
    // Modification n°2 : On redirige le pointeur vers "Mains nues" (index 3).
    // Imaginez que c'est un asset 3D de 50 Mo, l'échange ici prend 0 seconde !
    *arme_joueur = catalogue[3];
    
    printf("=> Vous perdez 30 PV et votre arme fond !\n");
}

/*
 * LE LOOT (Récompense)
 */
void ramasser_loot(char **arme_joueur, char **catalogue, int index_loot) {
    printf("Vous trouvez un coffre\n");
    *arme_joueur = catalogue[index_loot]; // On redirige vers la nouvelle arme
    printf("=> Vous équipez une nouvelle arme\n");
}

// ==========================================
// LE CŒUR DU JEU
// ==========================================
int main() {
    // 1. NOTRE BASE DE DONNÉES (Le catalogue d'assets)
    // C'est un tableau de pointeurs statiques. Ces textes ne bougeront jamais.
    char *inventaire[4] = {
        "Dague rouillée", // Index 0
        "Epee longue",    // Index 1
        "Hache de feu",   // Index 2
        "Mains nues"      // Index 3
    };

    // 2. LES VARIABLES DU HÉROS (Vides au départ)
    int hero_pv;
    int hero_or;
    char *hero_arme; // Une "étiquette" qui ne pointe vers rien pour l'instant

    // 3. LE GAMEPLAY
    // Attention : On doit utiliser '&' pour envoyer la CLÉ (l'adresse) de nos variables, 
    // sinon les fonctions recevront juste une copie vide et le main ne sera jamais mis à jour.
    
    // ACTE 1 : Entrée dans le donjon
    initialiser_hero(&hero_pv, &hero_or, &hero_arme, inventaire);
    afficher_status(hero_pv, hero_or, hero_arme);
    
    // ACTE 2 : Le drame
    declencher_piege_acide(&hero_pv, &hero_arme, inventaire);
    afficher_status(hero_pv, hero_or, hero_arme);
    
    // ACTE 3 : La récompense (On demande l'index 2 : Hache de feu)
    ramasser_loot(&hero_arme, inventaire, 2);
    afficher_status(hero_pv, hero_or, hero_arme);

    return 0; // Fin de la partie
}