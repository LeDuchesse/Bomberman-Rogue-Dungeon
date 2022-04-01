#include "../inc/objet.h"

int duration_popo(Effect effect){
	switch(effect){
		case HEAL:
			return 1;
			break;
		case MANA:
			return 1;
			break;
		case REGEN:
			return 30;
			break;
		case PRECISION:
			return 30;
			break;
		case LEARN:
			return 30;
			break;
		case TORCHE:
			return 15;
		default:
			return 1;
			break;

	}
	return 1;
}

Objets crea_potion(void){
	Potion popo;
	Objets obj;
	popo.effect =  rand()%6;
	popo.duration = duration_popo(popo.effect);
	obj.type_objet = CONSO;
	obj.Element.popo = popo;
	return obj;
}

Objets crea_equip(int tour){
	Objets obj;
	Equipment equip;
	equip.cathegorie = rand()%3;
	equip.quality = rand()%tour;
	equip.quality += 1;
	obj.type_objet = PERM;
	obj.Element.equip = equip;
	return obj;
}




