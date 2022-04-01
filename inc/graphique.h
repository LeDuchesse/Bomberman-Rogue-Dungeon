#ifndef __GRAPHIQUE__H__
#define __GRAPHIQUE__H__

#include "../inc/terrain.h"
#include "../inc/player.h"
#include <MLV/MLV_all.h>
#include <string.h>

typedef struct{
	MLV_Image * images[85];
}Images;


/*Dessine la fenêtre*/
void draw_everything(Donjon plateau, Player *p, Images images, int cpt_walk);

/*Affiche le joueur en fonction de sa direction, et de son nombre de pas*/
void draw_player(Donjon plateau, Player * p, Images im, int cpt_walk);


/*Dessine les monstres en fonction de leur type*/
void draw_monster(Monster * m, Images images, int x, int y);


/*Dessine le donjon*/
void dessine_plateau(Donjon plateau, Player *p, Images images);

/*Dessine le HUD du joueur*/
void draw_hud(Player * p, Images images, Donjon plateau);

/*Charge toutes les images dans un tableau d'image*/
Images charge_image();

/*Dessine le sol en fonction des murs adjascent*/
void draw_floor(Donjon plateau);

/*Dessine l'inventaire et les objets qui s'y trouve*/
void dessine_inventaire(Player * p, Images images);

/*Dessine un trésore et les objets qui s'y trouve*/
void dessine_treasure(Treasure tre, Images images);

/*Dessine les murs*/
void draw_mur(Donjon plateau, int x, int y, Images images, int k, int l);

/*Retourne la case de l'inventaire en fonction du clique*/
void coor_inv(int * x, int * y, int i);

/*Dessine un équipement en fonction de son type*/
int dessine_equip(Objets obj, Images images);

void animation_level_up(Player * p, Images images);

void free_image(Images im);

int screenChoix(Images images);

void game_over(Donjon plateau, Player * p);






#endif