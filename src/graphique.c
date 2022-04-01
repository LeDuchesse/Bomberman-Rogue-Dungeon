#include "../inc/graphique.h"




int screenChoix(Images images){
   	int x, y, choix = 0;
   	MLV_draw_image(images.images[82], 0, 0);
   	MLV_actualise_window();
   	do{
   		MLV_wait_mouse(&x, &y);
   		if(x>491 && x<916 && y > 442 && y < 565){
   			choix = 1;
   		}
   		if(x > 175 && x < 1124 && y > 720 && y < 765){
   			choix = 2;
   		}
   	}while(choix == 0);
   	MLV_clear_window(MLV_COLOR_BLACK);
   	return choix;
}


void draw_everything(Donjon plateau, Player *p, Images images, int cpt_walk){
	MLV_clear_window(MLV_COLOR_BLACK);
	dessine_plateau(plateau, p, images);
	draw_hud(p, images, plateau);
	draw_player(plateau, p, images, cpt_walk);
	MLV_actualise_window();



}

void dessine_plateau(Donjon plateau, Player *p, Images images){
	int i, j, k, l, x, y;
	x = p->pos_x;
	y = p->pos_y;
	k = 0;
	l = 0;
	for(i = x - 6; i < x+6+1; i++){
		for(j = y - 4; j < y+4+1; j++){
			if(i>0 && i < 64 && j < 44 && j > 0){
				if(plateau->etage[i][j].visited == 1){
					if(plateau->etage[i][j].type == WALL){
				
				MLV_draw_image(images.images[50], k*100, l*100);
				
				}
				if(plateau->etage[i][j].type == ROOM){
					MLV_draw_image(images.images[51], k*100, l*100);
					draw_mur(plateau, i, j, images, k*100, l*100);

				}
				if(plateau->etage[i][j].type == TREASURE){
					MLV_draw_image(images.images[0], k*100, l*100);
				}
				if(plateau->etage[i][j].type == MONSTER){
					
					MLV_draw_image(images.images[51], k*100, l*100);
					draw_mur(plateau, i, j, images, k*100, l*100);
	    			draw_monster(plateau->etage[i][j].Inter.monster, images, k*100, l*100);
				}
				if(plateau->etage[i][j].type == STAIR_DOWN){

					MLV_draw_image(images.images[51], k*100, l*100);
					draw_mur(plateau, i, j, images, k*100, l*100);
					MLV_draw_image(images.images[84], k*100, l*100);
				}
				if(plateau->etage[i][j].type == STAIR_UP){
					MLV_draw_image(images.images[51], k*100, l*100);
					draw_mur(plateau, i, j, images, k*100, l*100);
					MLV_draw_image(images.images[83], k*100, l*100);
				}
				if(i>=63 || i < 0){
					MLV_draw_image(images.images[50], k*100, l*100);
				}
				if(j>=43 || j < 0){
					MLV_draw_image(images.images[50], k*100, l*100);
				}
				
			}
			else{
				MLV_draw_image(images.images[50], k*100, l*100);
				MLV_draw_image(images.images[75], k*100, l*100);
			}
				}
				
			
			l++;
		}
		l = 0;
		k++;
	}
	i = p->pos_x;
	j = p->pos_y;
}

void draw_monster(Monster * m, Images images, int x, int y){
	switch(m->princesse){
        case BN:
        	MLV_draw_image(images.images[70], x, y);
            break;

        case CENDRILLON:
            MLV_draw_image(images.images[71], x, y);
            break;

        case YASMINE:
            MLV_draw_image(images.images[74], x, y);
            break;

        case SIRENE:
        	MLV_draw_image(images.images[72], x, y);
            break;

        case RAIPONCE:
        	MLV_draw_image(images.images[73], x, y);
            break;

        default:
            break;

    }
}

void draw_mur(Donjon plateau, int i, int j, Images images, int k, int l){
	if(plateau->etage[i+1][j].type == WALL)MLV_draw_image(images.images[52], k, l);
	if(plateau->etage[i][j+1].type == WALL)MLV_draw_image(images.images[54], k, l);
	if(plateau->etage[i-1][j].type == WALL)MLV_draw_image(images.images[53], k, l);
	if(plateau->etage[i][j-1].type == WALL)MLV_draw_image(images.images[55], k, l);
	
}

void draw_player(Donjon plateau, Player * p, Images im, int cpt_walk){
	cpt_walk %= 2;
	int armure = p->armure;
	if(armure > 2)armure = 3;
	switch(p->face){
		case NORD:
			MLV_draw_image(im.images[7 + cpt_walk + 10*armure], 1300/2-50, 900/2-50);
			break;
		case SUD:
			MLV_draw_image(im.images[1 + cpt_walk + 10*armure], 1300/2-50, 900/2-50);
			break;
		case EST:
			MLV_draw_image(im.images[5 + cpt_walk + 10*armure], 1300/2-50, 900/2-50);
			break;
		case OUEST:
			MLV_draw_image(im.images[3 + cpt_walk + 10*armure], 1300/2-50, 900/2-50);
			break;
		default:
			MLV_draw_image(im.images[10+10*armure], 1300/2-50, 900/2-50);
			break;
	}
}



void draw_hud(Player * p, Images images, Donjon plateau){
	MLV_draw_image(images.images[41], 0, 900);

	if(p->arme == 0){
		MLV_draw_image(images.images[42], 1100, 920);
		MLV_draw_image(images.images[43], 1200, 920);
	}
	if(p->arme == 1){
		MLV_draw_image(images.images[43], 1100, 920);
		MLV_draw_image(images.images[42], 1200, 920);
	}
	

	MLV_draw_image(images.images[44], 1105, 925);
	MLV_draw_image(images.images[45], 1205, 925);
	MLV_draw_filled_rectangle(10, 925, 20*(p->HP/p->Def), 10, MLV_COLOR_RED);
	MLV_draw_filled_rectangle(10, 945, 20*((p->MP)/(p->Int -5)), 10, MLV_COLOR_BLUE);
	MLV_draw_filled_rectangle(10, 965,p->Exp*2/(3.5+p->Lv), 10, MLV_COLOR_PINK);

	MLV_draw_text(215, 923, "%d/%d", MLV_COLOR_RED, p->HP, p->Def*10);
	MLV_draw_text(215, 947, "%d/%d", MLV_COLOR_BLUE, p->MP, (p->Int*10)-50);
	MLV_draw_text(215 + 15, 963, "%d", MLV_COLOR_PINK, p->Lv);


	MLV_draw_image(images.images[77], 275, 905);
	MLV_draw_text(290, 970, "%d", MLV_COLOR_LIGHT_BLUE, p->actual_effect[REGEN]);
	MLV_draw_image(images.images[78], 315, 905);
	MLV_draw_text(330, 970, "%d", MLV_COLOR_DEEP_PINK, p->actual_effect[PRECISION]);
	MLV_draw_image(images.images[79], 350, 905);
	MLV_draw_text(365, 970, "%d", MLV_COLOR_ORANGE, p->actual_effect[LEARN]);

	MLV_draw_image(images.images[80], 385, 905);
	MLV_draw_text(395, 970, "%d", MLV_COLOR_BROWN, p->actual_effect[TORCHE]);
	MLV_draw_text(450, 910, "Etage : %d", MLV_COLOR_WHITE, plateau->floor);
	MLV_draw_text(450, 930, "Atk : %d", MLV_COLOR_WHITE, p->Atk);
	MLV_draw_text(450, 950, "Def : %d", MLV_COLOR_WHITE, p->Def);
	MLV_draw_text(450, 970, "Int : %d", MLV_COLOR_WHITE, p->Int);
	MLV_draw_text(550, 940, "Monstres tués : %d", MLV_COLOR_GREEN, p->monstre_tue);
	
}

void dessine_inventaire(Player * p, Images images){
	int i, x = 0 , y = 0;
	int equip;
	MLV_draw_image(images.images[48], 0, 0);

	for(i = 0; i < 12; i++){
			
		coor_inv(&y, &x, i);
		if(p->inventory[i].type_objet == CONSO){
			switch(p->inventory[i].Element.popo.effect){
				case HEAL:
					MLV_draw_image(images.images[56], x-70, y-70);
					break;
				case LEARN:
					MLV_draw_image(images.images[60], x-70, y-70);
					break;
				case REGEN:
					MLV_draw_image(images.images[57], x-70, y-70);
					break;
				case MANA:
					MLV_draw_image(images.images[59], x-70, y-70);
					break;
				case PRECISION:
					MLV_draw_image(images.images[58], x-70, y-70);
					break;
				case TORCHE:
					MLV_draw_image(images.images[81], x-30, y-70);
					break;
				default:
					break;
				}
		}

		if(p->inventory[i].type_objet == PERM){
			equip = dessine_equip(p->inventory[i], images);
			if(equip > 0) MLV_draw_image(images.images[equip], x-70, y-70);
		}
		
	}

		
}



void coor_inv(int * x, int * y, int i){
	if(i >= 0 && i <= 3) *x = 150;
	if(i >= 4 && i <= 7) *x = 465;
	if(i >= 8 && i <= 11) *x = 810;

	if(i % 4 == 0){
		*y = 350;
		return;
	}

	if(i == 1 || i == 5 || i == 9){
	 *y = 550;
	 return;
	}

	if(i % 2 == 0){
		*y = 750;
		return;
	}
	*y = 950;
	return;
}

void dessine_treasure(Treasure tre, Images images){
	MLV_draw_image(images.images[49], 0, 0);
	int equip;
	if(tre.popo.type_objet == CONSO){
		switch(tre.popo.Element.popo.effect){
		case HEAL:
			MLV_draw_image(images.images[56], 345, 330);
			break;
		case LEARN:
			MLV_draw_image(images.images[60], 330, 330);
			break;
		case REGEN:
			MLV_draw_image(images.images[57], 345, 330);
			break;
		case MANA:
			MLV_draw_image(images.images[59], 345, 330);
			break;
		case PRECISION:
			MLV_draw_image(images.images[58], 345, 330);
			break;
		case TORCHE:
			MLV_draw_image(images.images[81], 370, 330);
			break;
		default:
			break;
		}
	}
	if(tre.equip.type_objet == 1){
		equip = dessine_equip(tre.equip, images);
		if(equip > 0) MLV_draw_image(images.images[equip], 820, 350);
	}
	
}

int dessine_equip(Objets obj, Images images){
	int image = -1;
	switch(obj.Element.equip.cathegorie){
		case ARMOR:
			image = 67;
			break;
		case WEAPOND:
			image = 61;
			break;
		case WAND:
			image = 64;
			break;
		default:
			break;
	}
	switch(obj.Element.equip.quality){
		case 1:
			image +=0;
			break;
		case 2:
			image +=1;
			break;
		default:
			break;
	}
	if(obj.Element.equip.quality>2)image+=2;
	
	return image;
}

void animation_level_up(Player * p, Images images){
	MLV_draw_image(images.images[9 + 10*p->armure], 1300/2-50, 900/2-50);
	MLV_actualise_window();
	MLV_wait_milliseconds(500);
	MLV_draw_image(images.images[10 + 10*p->armure], 1300/2-50, 900/2-50);
	MLV_actualise_window();
	MLV_wait_milliseconds(500);
	
}

void free_image(Images im){
	int i;
	for(i = 0; i< 85; i++){
		MLV_free_image(im.images[i]);
	}
}

void game_over(Donjon plateau, Player * p){
	MLV_draw_filled_rectangle(0, 0, 1300, 1000, MLV_COLOR_BLACK);
	MLV_draw_text(650, 500, "Vous avez tué %d princesses", MLV_COLOR_GREEN, p->monstre_tue);
	MLV_draw_text(650, 600, "Vous avez atteint l'étage %d", MLV_COLOR_GREEN, plateau->floor);
	MLV_actualise_window();
	MLV_wait_mouse(NULL, NULL);
}


Images charge_image(){
	Images image;
	int i;

	image.images[0] = MLV_load_image("src/img/chest.png");

	image.images[1] = MLV_load_image("src/img/player/white/perso_moving_forward.png");
	image.images[2] = MLV_load_image("src/img/player/white/perso_moving_forward_2.png");
	image.images[3] = MLV_load_image("src/img/player/white/perso_moving_left_1.png");
	image.images[4] = MLV_load_image("src/img/player/white/perso_moving_left_2.png");
	image.images[5] = MLV_load_image("src/img/player/white/perso_moving_right_1.png");
	image.images[6] = MLV_load_image("src/img/player/white/perso_moving_right_2.png");
	image.images[7] = MLV_load_image("src/img/player/white/perso_moving_up_1.png");
	image.images[8] = MLV_load_image("src/img/player/white/perso_moving_up_2.png");
	image.images[9] = MLV_load_image("src/img/player/white/animation_level_up_1.png");
	image.images[10] = MLV_load_image("src/img/player/white/animation_level_up_2.png");
	image.images[11] = MLV_load_image("src/img/player/red/move_back_1.png");
	image.images[12] = MLV_load_image("src/img/player/red/move_back_2.png");
	image.images[13] = MLV_load_image("src/img/player/red/move_left_1.png");
	image.images[14] = MLV_load_image("src/img/player/red/move_left_2.png");
	image.images[15] = MLV_load_image("src/img/player/red/move_right_1.png");
	image.images[16] = MLV_load_image("src/img/player/red/move_right_2.png");
	image.images[17] = MLV_load_image("src/img/player/red/move_forward_1.png");
	image.images[18] = MLV_load_image("src/img/player/red/move_forward_2.png");
	image.images[19] = MLV_load_image("src/img/player/red/animation_level_up_1.png");
	image.images[20] = MLV_load_image("src/img/player/red/animation_level_up_2.png");

	image.images[21] = MLV_load_image("src/img/player/purple/moving_down_1.png");
	image.images[22] = MLV_load_image("src/img/player/purple/moving_down_2.png");
	image.images[23] = MLV_load_image("src/img/player/purple/moving_left_1.png");
	image.images[24] = MLV_load_image("src/img/player/purple/moving_left_2.png");
	image.images[25] = MLV_load_image("src/img/player/purple/moving_right_1.png");
	image.images[26] = MLV_load_image("src/img/player/purple/moving_right_2.png");
	image.images[27] = MLV_load_image("src/img/player/purple/moving_up_1.png");
	image.images[28] = MLV_load_image("src/img/player/purple/moving_up_2.png");
	image.images[29] = MLV_load_image("src/img/player/purple/animation_level_up_1.png");
	image.images[30] = MLV_load_image("src/img/player/purple/animation_level_up_2.png");

	image.images[31] = MLV_load_image("src/img/player/black/moving_down_1.png");
	image.images[32] = MLV_load_image("src/img/player/black/moving_down_2.png");
	image.images[33] = MLV_load_image("src/img/player/black/moving_left_1.png");
	image.images[34] = MLV_load_image("src/img/player/black/moving_left_2.png");
	image.images[35] = MLV_load_image("src/img/player/black/moving_right_1.png");
	image.images[36] = MLV_load_image("src/img/player/black/moving_right_2.png");
	image.images[37] = MLV_load_image("src/img/player/black/moving_up_1.png");
	image.images[38] = MLV_load_image("src/img/player/black/moving_up_2.png");
	image.images[39] = MLV_load_image("src/img/player/black/animation_level_up_1.png");
	image.images[40] = MLV_load_image("src/img/player/black/animation_level_up_2.png");

	image.images[41] = MLV_load_image("src/img/HUD/hud.png");
	image.images[42] = MLV_load_image("src/img/HUD/icon_selection_arme_2.png");
	image.images[43] = MLV_load_image("src/img/HUD/icon_deselection_arme_2.png");
	image.images[44] = MLV_load_image("src/img/HUD/epee_bois.png");
	image.images[45] = MLV_load_image("src/img/HUD/magic_blanc.png");
	image.images[46] = MLV_load_image("src/img/HUD/action_impossible.png");
	image.images[47] = MLV_load_image("src/img/HUD/action_possible.png");
	image.images[48] = MLV_load_image("src/img/HUD/backpack.png");
	image.images[49] = MLV_load_image("src/img/HUD/coffre_ouverture.png");

	image.images[50] = MLV_load_image("src/img/sol/mur_tapis.png");
	image.images[51] = MLV_load_image("src/img/sol/mur/mur_total.png");
	image.images[52] = MLV_load_image("src/img/sol/mur/mur_a_droite.png");
	image.images[53] = MLV_load_image("src/img/sol/mur/mur_a_gauche.png");
	image.images[54] = MLV_load_image("src/img/sol/mur/mur_en_bas.png");
	image.images[55] = MLV_load_image("src/img/sol/mur/mur_en_haut.png");

	image.images[56] = MLV_load_image("src/img/potions/heal.png");
	image.images[57] = MLV_load_image("src/img/potions/regen.png");
	image.images[58] = MLV_load_image("src/img/potions/pre.png");
	image.images[59] = MLV_load_image("src/img/potions/mana.png");
	image.images[60] = MLV_load_image("src/img/potions/exp.png");

	image.images[61] = MLV_load_image("src/img/armes/arme_cac/epee_rouge.png");
	image.images[62] = MLV_load_image("src/img/armes/arme_cac/dague_violette.png");
	image.images[63] = MLV_load_image("src/img/armes/arme_cac/epee_noir.png");

	image.images[64] = MLV_load_image("src/img/armes/arme_magique/magic_rouge.png");
	image.images[65] = MLV_load_image("src/img/armes/arme_magique/magic_violet.png");
	image.images[66] = MLV_load_image("src/img/armes/arme_magique/magic_noir.png");

	image.images[67] = MLV_load_image("src/img/cristaux/cristal_rouge.png");
	image.images[68] = MLV_load_image("src/img/cristaux/cristal_violet.png");
	image.images[69] = MLV_load_image("src/img/cristaux/crsital_noir.png");

	image.images[70] = MLV_load_image("src/img/monstre/BN.png");
	image.images[71] = MLV_load_image("src/img/monstre/cendrillon.png");
	image.images[72] = MLV_load_image("src/img/monstre/petite_sirene.png");
	image.images[73] = MLV_load_image("src/img/monstre/raiponce.png");
	image.images[74] = MLV_load_image("src/img/monstre/Yasmine.png");
	image.images[75] = MLV_load_image("src/img/sol/mur/filtre_opak.png");
	image.images[76] = MLV_load_image("src/img/HUD/level_up.png");

	image.images[77] = MLV_load_image("src/img/potions/regen.png");
	image.images[78] = MLV_load_image("src/img/potions/pre.png");
	image.images[79] = MLV_load_image("src/img/potions/exp.png");

	image.images[80] = MLV_load_image("src/img/potions/torche.png");
	image.images[81] = MLV_load_image("src/img/potions/torche.png");
	image.images[82] = MLV_load_image("src/img/menu.png");
	image.images[83] = MLV_load_image("src/img/sol/strair_up.png");
	image.images[84] = MLV_load_image("src/img/sol/stair_down.png");
	MLV_resize_image_with_proportions(image.images[0], 100, 100);
	MLV_resize_image(image.images[41], 1300, 100);
	MLV_resize_image(image.images[42], 60, 60);
	MLV_resize_image(image.images[43], 60, 60);

	for(i = 1; i < 41; i++){
		MLV_resize_image_with_proportions(image.images[i], 80, 80);
	}
	MLV_resize_image(image.images[49], 1300, 900);

	for(i = 56; i < 70; i++){
		MLV_resize_image_with_proportions(image.images[i], 175, 150);
	}
	for(i = 77; i < 81; i++){
		MLV_resize_image_with_proportions(image.images[i], 50, 50);
	}
	MLV_resize_image(image.images[70], 100, 100);
	MLV_resize_image_with_proportions(image.images[44], 50, 50);
	MLV_resize_image_with_proportions(image.images[45], 50, 50);

	return image;
}
