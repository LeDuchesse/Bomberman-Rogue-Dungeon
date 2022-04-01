#include "../inc/treasure.h"

Treasure crea_treasure(int etage, int pos_x, int pos_y){
	Treasure tre;
	tre.popo = crea_potion();
	tre.equip = crea_equip(etage);
	tre.pos_x = pos_x;
	tre.pos_y = pos_y;
	return tre;
}

