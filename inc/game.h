#ifndef __GAME__H__
#define __GAME__H__

#include <MLV/MLV_all.h>
#include "../inc/player.h"
#include "../inc/graphique.h"


/*Reçois la touche de déplacement que le joueur a pressé et prépare le personnage à se déplacer*/
int action_player(MLV_Keyboard_button touche, Player * p, Donjon plateau);


/*Change l'arme du joueur en main*/
void click_player(int x, int y, Player * p);


/*Ouvre le coffre en face du joueur*/
void fouille_coffre(Donjon plateau, Player * p, Images images);


/*Renvoie l'emplacement x de l'inventaire en fonction du clique du joueur*/
int case_inventaire(int clic_x, int clic_y);


/*Prépare l'action de prendre l'objet d'un coffre en fonction du clique du joueur*/
void get_coffre(Donjon plateau, Player * p, int clic_x, int clic_y, int x_coffre, int y_coffre);


/*Permet de se balader dans l'inventaire et d'utiliser les potions*/
void dans_linventaire(Player * p, Images images);


/*Prépare les 4 actions possibles en fonction de ou se trouve le joueur
 *attaquer le monstre
 *fouiller le coffre
 *prendre les escaliers*/


Donjon action_env(Player * p, Donjon plateau, Images images);


/*Prend un escalier montant (revient en arrière)*/
Donjon escalierUP(Donjon plateau, Player * p);


/*Prend un escalier descendant et prépare la création d'un nouvel étage*/
Donjon escalierDOWN(Donjon plateau, Player * p);


/*Fait monter de niveau le joueur*/
Player* upLv(Player* p, Images im);


/*Suite direct de upLv, propose au joueur ou veut-il placer ses améliorations*/
void choix_amelioration(Player * p, Images im);

void fin(Donjon donjon, Player * p, Images images);

void exit_total(Donjon plateau, Player * p, Images images);




#endif