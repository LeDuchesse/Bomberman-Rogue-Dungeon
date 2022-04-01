#ifndef __MONSTER__H__
#define __MONSTER__H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef enum{BN, YASMINE, CENDRILLON, SIRENE, RAIPONCE}Princesse;

typedef struct {
        int HP;
        int Atk;
        int pos_x;
        int pos_y;
        Princesse princesse;
    } Monster;

/*Initialise un monstre en fonction de son étage*/
Monster* initMonster(Monster* m, int x, int y, int etage);

/*donne un type aléatoire au monstre*/
void typeMonster(Monster* m);


Monster* allocMonsters();

void freeMonster(Monster* m);
/*Renvoie 1 si le monstre est mort après le coup d'un joueur*/
int isDead(Monster* m);

/*retourne le nombre de dégats que se prend un joueur lors d'une attaque de monstre*/
int attackMonster(Monster* m);


#endif