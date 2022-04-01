#include <stdio.h>
#include "../inc/liste.h"
#include "../inc/terrain.h"
#include "../inc/graphique.h"
#include "../inc/player.h"
#include "../inc/game.h"
#include "../inc/monster.h"
#include <MLV/MLV_all.h>

int main(void){

	Images images;
	MLV_Keyboard_button touche;
	Player* p;
	Donjon plateau;
	int cpt_walk = 0, clic_x = 0, clic_y = 0, jeu = 0;
	MLV_create_window("Donjon", "donjon", 1300, 1000);
	images = charge_image();
	jeu = screenChoix(images);

	if(jeu == 1){
		p = allocPlayer();
		p = initPlayer(p);
	   	plateau = init_donjon();
	    plateau = init_plateau(plateau);
		visiting_cell(plateau, p);
	}

	if(jeu == 2){
	   	plateau = init_donjon();
	    plateau = init_plateau(plateau);
	    p = read_player(p);
		visiting_cell(plateau, p);

	}
	draw_everything(plateau, p, images, cpt_walk);
	while(1){
		draw_everything(plateau, p, images, cpt_walk);

		MLV_wait_keyboard_or_mouse(&touche, NULL, NULL, &clic_x, &clic_y);
		if(touche == MLV_KEYBOARD_f){
			plateau = action_env(p,  plateau,  images);
			visiting_cell(plateau, p);
		}
		if(touche == MLV_KEYBOARD_z || touche == MLV_KEYBOARD_q || touche == MLV_KEYBOARD_s || touche == MLV_KEYBOARD_d){
			action_player(touche, p, plateau);
			visiting_cell(plateau, p);
			cpt_walk++;
		}

		if(touche == MLV_KEYBOARD_e){
			dans_linventaire(p, images);
		}

		if(touche == MLV_KEYBOARD_p){

			exit_total(plateau, p, images);
			printf("exit terminated\n");
			exit(1);
		}

		if(p->HP <= 0){
			fin(plateau, p, images);
			exit(1);
		}
		else{
			click_player(clic_x, clic_y, p);
		}

		touche = MLV_KEYBOARD_l;
		clic_x = -1;
		clic_y = -1;
  
	}
	return 0;
}