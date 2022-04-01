#include "../inc/terrain.h"
#include <time.h>




Donjon init_donjon(){
	return NULL;
}

Donjon init_plateau(Donjon plateau){
	
	int i, j;
	Etage * et;
	et = malloc(sizeof(*et));
	if(et == NULL){
		fprintf(stderr, "Erreur alloc \n");
        exit(1);
	}

	et->floor = 1;
	
	et->precedant = NULL;
	et->suivant = NULL;
	for(i = 0; i < X; i++){
		for(j = 0; j < Y; j++){
			et->etage[i][j].type = WALL;
			et->etage[i][j].visited = 0;
		}
	}
	liste toexpand = crea_token();
	toexpand = escalier_up(et, toexpand);
	generation(toexpand, et);
	free_toexpand(toexpand);
	free(toexpand);
	return et;
	
}


Donjon descentEtage(Donjon plateau){
	if(plateau->suivant != NULL)return plateau->suivant;
	int i, j;
	Etage * et;
	et = malloc(sizeof(*et));
	if(et == NULL){
		fprintf(stderr, "Erreur alloc \n");
        exit(1);
	}
	et->floor = plateau->floor+1;
	et->precedant = plateau;
	et->suivant = NULL;
	for(i = 0; i < X; i++){
			for(j = 0; j < Y; j++){
				et->etage[i][j].type = WALL;
				et->etage[i][j].visited = 0;
			}
		}
	liste toexpand = crea_token();
	toexpand = escalier_up(et, toexpand);
	generation(toexpand, et);
	plateau->suivant = et;
	plateau = plateau->suivant;
	return et;
}

Donjon monteEtage(Donjon plateau){

	if(plateau->precedant == NULL){
		return plateau;
	}
	plateau = plateau->precedant;
	return plateau;
}

Bool admissible(int x, int y, Donjon plateau){
	int cpt_1 = 0, cpt_2 = 0;
	if(x+1 >= X || y+1 >= Y || x-1 < 0 || y-1 < 0){
		return false;
	}

	if(plateau->etage[x+1][y].type != WALL)
		cpt_1++;
	if(plateau->etage[x-1][y].type != WALL)
		cpt_1++;
	if(plateau->etage[x][y+1].type != WALL)
		cpt_1++;
	if(plateau->etage[x][y-1].type != WALL)
		cpt_1++;

	if(plateau->etage[x][y+2].type != WALL)
		cpt_2++;
	if(plateau->etage[x][y-2].type != WALL)
		cpt_2++;
	if(plateau->etage[x+2][y].type != WALL)
		cpt_2++;
	if(plateau->etage[x-2][y].type != WALL)
		cpt_2++;
	if(plateau->etage[x+1][y+1].type != WALL)
		cpt_2++;
	if(plateau->etage[x+1][y-1].type != WALL)
		cpt_2++;
	if(plateau->etage[x-1][y-1].type != WALL)
		cpt_2++;
	if(plateau->etage[x-1][y+1].type != WALL)
		cpt_2++;

	if(cpt_1 == 1 && cpt_2 < 3){
		return true;
	}
	return false;

	
}

void admissible_adja(int x, int y, Donjon plateau, Cases * plat){
	
	if(admissible(x+1,y, plateau)){
		if(check_fine(plat, x+1, y)){
			ajout_droite(plat, x+1, y);
		}
		
	}
	if(admissible(x-1, y, plateau)){
		if(check_fine(plat, x-1, y)){
			ajout_droite(plat, x-1, y);
		}
	}
	
	if(admissible(x, y+1, plateau)){
		if(check_fine(plat, x, y+1)){
			ajout_droite(plat, x, y+1);
		}
	}
	
	if(admissible(x, y-1, plateau)){
		if(check_fine(plat, x, y-1)){
			ajout_droite(plat, x, y-1);
		}
	}

}

void generation(Cases * plat, Donjon plateau){
	int x, y, i;
	srand(time(NULL));
	int alea;
	do{		
		alea = rand() % liste_taille(plat)+1;
		supprime_n(plat, alea, &x, &y);
		if(admissible(x, y, plateau)){
			plateau->etage[x][y].type = ROOM;
			admissible_adja(x, y, plateau, plat);

		}
	}
	while(liste_taille(plat) != 0);
	plateau->etage[32][22].type = STAIR_UP;

	treasure_first_level(plateau);
	for(i = 0; i < 100; i++)
		treasure_generation(plateau);
	escalier_down(plateau);
	free_toexpand(plat);



}

liste escalier_up(Donjon plateau, liste toexpand){
	plateau->etage[32][22].type = STAIR_UP;
	toexpand = ajout_droite(toexpand, 32, 23);
	toexpand = ajout_droite(toexpand, 32, 21);
	toexpand = ajout_droite(toexpand, 33, 22);
	toexpand = ajout_droite(toexpand, 31, 22);
	return toexpand;
}

void escalier_down(Donjon plateau){
	int x, y, cpt_1;
	srand(time(NULL));
	do{
		cpt_1 = 0;
		x = rand() % X;
		y = rand() % Y;
		
		if(plateau->etage[x+1][y].type == WALL)
			cpt_1++;
		if(plateau->etage[x-1][y].type == WALL)
			cpt_1++;
		if(plateau->etage[x][y+1].type == WALL)
			cpt_1++;
		if(plateau->etage[x][y-1].type == WALL)
			cpt_1++;

		if(plateau->etage[x][y].type != ROOM)
			cpt_1 = 0;
	}
	while(cpt_1 != 3);
	plateau->etage[x][y].type = STAIR_DOWN;
	plateau->pos_x_escalier = x;
	plateau -> pos_y_escalier = y;
}

void treasure_first_level(Donjon plateau){
	
	int x, y;
	x = 32;
	y = 22;
	if(plateau->etage[x][y-1].type == WALL){
		plateau->etage[x][y-1].type = TREASURE;
		plateau->etage[x][y-1].Inter.treasure = crea_treasure(plateau->floor, x, y-1);
		return;
	}
	if(plateau->etage[x][y+1].type == WALL){
		plateau->etage[x][y+1].type = TREASURE;
		plateau->etage[x][y+1].Inter.treasure = crea_treasure(plateau->floor, x, y+1);
		return;
	}
	if(plateau->etage[x+1][y].type == WALL){
		plateau->etage[x+1][y].type = TREASURE;
		plateau->etage[x+1][y].Inter.treasure = crea_treasure(plateau->floor, x+1, y);
		return;
	}
	if(plateau->etage[x-1][y].type == WALL){
		plateau->etage[x-1][y].type = TREASURE;
		plateau->etage[x-1][y].Inter.treasure = crea_treasure(plateau->floor, x-1, y);
		return;
	}

}

Bool impasse(Donjon plateau){
	
	int x, y, cpt_1;
	for(x = 1; x < X; x++){
		for(y = 1; y < Y; y++){
			cpt_1 = 0;
				if(plateau->etage[x+1][y].type == WALL)
					cpt_1++;
				if(plateau->etage[x-1][y].type == WALL)
					cpt_1++;
				if(plateau->etage[x][y+1].type == WALL)
					cpt_1++;
				if(plateau->etage[x][y-1].type == WALL)
					cpt_1++;
				if(plateau->etage[x][y].type != ROOM)
					cpt_1 = 0;
				if(cpt_1 == 3){
					return false;
			}
			
		}
	}
	return true;
}

void treasure_generation(Donjon plateau){
	int x, y, cpt_1;
	Monster *m = allocMonsters();

	srand(time(NULL));
	do{
		cpt_1 = 0;
		x = rand() % X;
		y = rand() % Y;
		
		if(plateau->etage[x+1][y].type == WALL)
			cpt_1++;
		if(plateau->etage[x-1][y].type == WALL)
			cpt_1++;
		if(plateau->etage[x][y+1].type == WALL)
			cpt_1++;
		if(plateau->etage[x][y-1].type == WALL)
			cpt_1++;

		if(plateau->etage[x][y].type != ROOM)
			cpt_1 = 0;
	}
	while(cpt_1 != 3);
	
	plateau->etage[x][y].type = TREASURE;
	plateau->etage[x][y].Inter.treasure = crea_treasure(plateau->floor, x, y);

	if(plateau->etage[x+1][y].type == ROOM){
		plateau->etage[x+1][y].type = MONSTER;
		initMonster(m, x+1, y, plateau->floor);
		plateau->etage[x+1][y].Inter.monster = m;
	}
		

	if(plateau->etage[x-1][y].type == ROOM){
		plateau->etage[x-1][y].type = MONSTER;
		initMonster(m, x-1, y, plateau->floor);
		plateau->etage[x-1][y].Inter.monster = m;
	}

	if(plateau->etage[x][y+1].type == ROOM){
		plateau->etage[x][y+1].type = MONSTER;
		initMonster(m, x, y+1, plateau->floor);
		plateau->etage[x][y+1].Inter.monster = m;
	}

	if(plateau->etage[x][y-1].type == ROOM){
		plateau->etage[x][y-1].type = MONSTER;
		initMonster(m, x, y-1, plateau->floor);
		plateau->etage[x][y-1].Inter.monster = m;
	}
}

void free_donjon(Donjon plateau){
	int i, j;
	for(i = 0; i < 63; i++){
		for(j = 0; j < 43; j++){
			if(plateau->etage[i][j].type == MONSTER){
				free(plateau->etage[i][j].Inter.monster);
			}
		}
	}
	if(plateau->floor == 1){
		free(plateau);
		return;
	}

	while(plateau->precedant != NULL){
		plateau = plateau->precedant;
	}

	while(plateau->suivant != NULL){
		plateau = plateau->suivant;
		free(plateau->precedant);
	}
	free(plateau);

}

void sauve_donjon(Donjon plateau){
	FILE * donjon;
	donjon = fopen("sauvegardes/donjon.bin", "w");
	fwrite(plateau, 1, sizeof(plateau), donjon);
	fclose(donjon);
}

