#ifndef __TERRAIN__H__
#define __TERRAIN__H__

#define X 63
#define Y 43
#include "../inc/liste.h"
#include "../inc/monster.h"
#include "../inc/treasure.h"


typedef enum{WALL, ROOM, MONSTER, TREASURE, STAIR_UP, STAIR_DOWN} Celltype;

typedef struct{

	Celltype type;
	int visited;
	union{
		Monster* monster;
		Treasure treasure;
	}Inter;


}Cell;

typedef struct donjon{
	Cell etage[X][Y];
	int floor;
	int pos_x_escalier;
	int pos_y_escalier;
	struct donjon * suivant;
	struct donjon * precedant;
}Etage, *Donjon;


Donjon init_donjon();

/*initialise le plateau en créant un étage avec des murs*/
Donjon init_plateau(Donjon plateau);


/*Creer un nouvel étage*/
Donjon descentEtage(Donjon plateau);


/*fait revenir le joueur a un étage plus haut*/
Donjon monteEtage(Donjon plateau);

/*verifie si x et y sont admissible dans le processus de création du labyrinthe*/
Bool admissible(int x, int y, Donjon plateau);


/*vérifie si les cases adjascentes à la case qui vient de devenir une case ROOM sont admissibles*/
void admissible_adja(int x, int y, Donjon plateau, Cases * plat);


/*Génère tout un labyrinthe*/
void generation(Cases * plat, Donjon plateau);


/*Place l'escalier montant, donc le point de départ de l'algorythme de génération du labyrinthe*/
liste escalier_up(Donjon plateau, liste toexpand);


/*Place l'escalier descandant dans une impasse*/
void escalier_down(Donjon plateau);

/*genere un tresore à coté de l'escalier montant*/
void treasure_first_level(Donjon plateau);

/*Génère tout les trésore dans une impasse et place un monstre à coté*/
void treasure_generation(Donjon plateau);

/*verifie si il y a des impasses sur le plateau*/
Bool impasse(Donjon plateau);

void free_donjon(Donjon plateau);

void sauve_donjon(Donjon plateau);




#endif