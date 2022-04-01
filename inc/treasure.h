#ifndef __TREASURE_H__
#define __TREASURE__H__

#include "../inc/objet.h"
#include <stdlib.h>
#include <stdio.h>




typedef struct{
	Objets popo;
	Objets equip;
	int pos_x;
	int pos_y;
}Treasure;


/*créer un trésore*/
Treasure crea_treasure(int pos_x, int pos_y, int etage);


#endif