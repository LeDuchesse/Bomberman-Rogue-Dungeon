#ifndef __OBJET_H__
#define __OBJET__H__

#include <stdlib.h>
#include <stdio.h>
#include <time.h>


typedef enum{REGEN, PRECISION, LEARN, TORCHE, MANA, HEAL }Effect;

typedef enum{ARMOR, WEAPOND, WAND}Cathegorie;

typedef enum{CONSO, PERM, VIDE}Type_Objet;

typedef struct{
	Effect effect;
	int duration;
}Potion;

typedef struct{
	Cathegorie cathegorie;
	int quality;
} Equipment;

typedef struct{
	Type_Objet type_objet; /*Vide si l'objet doit disparaître*/
	union{
		Potion popo;    
		Equipment equip;
	}Element;
	
}Objets;


/*Affecte la durée d'une potion en fonction de son effet*/
int duration_popo(Effect effect);

/*créer une potion aléatoirement*/
Objets crea_potion(void);

/*créer un équipement aléatoire en fonction de l'étage*/
Objets crea_equip(int tour);




#endif