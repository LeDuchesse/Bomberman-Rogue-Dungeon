#ifndef __LISTE__H__
#define __LISTE__H__

#include <stdio.h>
#include <stdlib.h>
/* Définition d'un Booléen */
typedef enum {
    false,
    true
} Bool;

/* Définition d'un token */
typedef struct casent {
    int case_i;
    int case_j;
    struct casent *suivant;
    
} Cases, *liste;

liste crea_token(void);

liste ajout_droite(Cases * tok, int x, int y);

int liste_taille(Cases *tok);

Bool token_vide(liste tok) ;

void supprime_n(Cases * plat, int n, int * x, int * y);

Bool check_fine(Cases * toexp, int x, int y);

void free_toexpand(liste l);







#endif