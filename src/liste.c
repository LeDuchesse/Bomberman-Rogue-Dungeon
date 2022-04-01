#include "../inc/liste.h"

liste crea_token(void) {
    return NULL;
	}

Bool token_vide(liste tok) {
    if (tok == NULL) {
        return true;
    }
    return false;
}

int liste_taille(Cases * tok) { 
    int taille = 0;
    if (token_vide(tok))
        return 0;
    while (tok->suivant != NULL) {
        taille++;
        tok = tok->suivant;
        
    }
    return taille;
}

liste ajout_droite(Cases * tok, int x, int y) {
    Cases *token;

    token = malloc(sizeof(*token));

    if (token == NULL) {
        fprintf(stderr, "Erreur alloc \n");
        exit(1);
    }
    token->case_i = x;
    token->case_j = y;
    token->suivant = NULL;

    if (token_vide(tok)) {
        tok = token;
        return tok;
    }
    Cases *temp;
    temp = tok;

    while (temp->suivant != NULL){
        temp = temp->suivant;
    }
    temp->suivant = token;

    return tok;


}


Bool check_fine(Cases * toexp, int x, int y){
    /*vérifie que x et y ne sont pas déja des cases dans la liste to_expand*/
	Cases * temp;
	temp = toexp;
	while(temp != NULL){
		if(x == temp->case_i && y == temp->case_j){
			return false;
		}
		temp = temp->suivant;
	}
	return true;
}



void supprime_n(Cases * plat, int n, int * x, int * y){
    /*supprime de la liste un element au numéro n et renvoie ses attributs*/
	Cases * temp1;
	temp1 = plat;

	int i;
	if(plat == NULL){
		return;
	}
	for(i = 0; i < n-1; i++){
		temp1 = temp1->suivant;
	}
	Cases * temp2 = temp1->suivant;
	temp1->suivant = temp2->suivant;

	*x = temp2->case_i;
	*y = temp2->case_j;

	free(temp2);

}

void free_toexpand(liste l){
    int taille = 0, i = 0;
    taille = liste_taille(l);
    for(i = taille; i > 0; i--){
        supprime_n(l, i, 0, 0);
    }
}









