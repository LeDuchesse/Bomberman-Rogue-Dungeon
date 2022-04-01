#include "../inc/game.h"



int action_player(MLV_Keyboard_button touche, Player * p, Donjon plateau){
	int dep, mort = 0;
	switch (touche) {
        case MLV_KEYBOARD_z:
            dep = 5;
            break;
        case MLV_KEYBOARD_s:
            dep = 2;
            break;
        case MLV_KEYBOARD_q:
            dep = 1;
            break;
        case MLV_KEYBOARD_d:
            dep = 3;
            break;
        default:
            break;
            }
    mort = moving(p, dep, plateau);
    return mort;
}

void click_player(int x, int y, Player * p){
    if((x > 1100 && x < 1160) && (y > 920 && y < 980)){
        p->arme = 0;
    }
    if((x > 1200 && x < 1260) && (y > 920 && y < 980)){
        p->arme = 1;
    }

}

Donjon action_env(Player * p, Donjon plateau, Images images){
	/**/
    int mort;
    if(facingTreasure(p, plateau) == 1){
        fouille_coffre(plateau, p, images);
        return plateau;
    }

    if(facingMonster(p, plateau) == 1){
        mort = combat(p, plateau);
        if(mort == 2)upLv(p, images);
        return plateau;
    }
    if(plateau->etage[p->pos_x][p->pos_y].type == STAIR_DOWN)
        return  escalierDOWN(plateau, p);
    if(plateau->etage[p->pos_x][p->pos_y].type == STAIR_UP)
        return escalierUP(plateau, p); 

    return plateau;
}

Donjon escalierUP(Donjon plateau, Player * p){
    if(plateau->floor != 1){
    	p->pos_x = plateau->precedant->pos_x_escalier;
        p->pos_y = plateau->precedant->pos_y_escalier;
    	plateau = monteEtage(plateau);
        
	}
    return plateau;
}

Donjon escalierDOWN(Donjon plateau, Player * p){
    p->pos_x = 32;
    p->pos_y = 22;
    plateau  = descentEtage(plateau); 
    return plateau;
}

int case_inventaire(int clic_x, int clic_y){
    if(clic_y < 0)return -1;
    int case_inv = -1;
    if(clic_x >290 && clic_x < 290+112)case_inv = 0;
    if(clic_x >491 && clic_x < 491+112)case_inv = 1;
    if(clic_x >692 && clic_x < 692+112)case_inv = 2;
    if(clic_x >893 && clic_x < 893+112)case_inv = 3;
    if(clic_y > 96 && clic_y < 96+146)case_inv+= 0;
    if(clic_y > 420 && clic_y < 420+146)case_inv+= 4;
    if(clic_y > 744 && clic_y < 744+146)case_inv+= 8;
    return case_inv;
}


void dans_linventaire(Player * p, Images images){
    int x, y, c;
    dessine_inventaire(p, images);
    MLV_actualise_window();
    MLV_wait_mouse(&x, &y);
    c = case_inventaire(x, y);
    if(c == -1)return;
    if(p->inventory[c].type_objet == CONSO){
        using_popo(p, p->inventory[c].Element.popo.effect);
        p->inventory[c].type_objet = VIDE;
    }

}

void fouille_coffre(Donjon plateau, Player * p, Images images){
	
    tour_potion(p);
    int x, y, clic_x, clic_y;
    x = p->pos_x;
    y = p->pos_y;
    faceDirection(p, &x, &y);
    dessine_treasure(plateau->etage[x][y].Inter.treasure, images);
    MLV_actualise_window();
    MLV_wait_mouse(&clic_x, &clic_y);
    get_coffre(plateau, p, clic_x, clic_y, x, y);

}

void get_coffre(Donjon plateau, Player * p, int clic_x, int clic_y, int x_coffre, int y_coffre){
    int v;
    if((clic_x >354 && clic_x < 449) && (clic_y > 387 && clic_y < 515)){
        v = get_objet(p, plateau->etage[x_coffre][y_coffre].Inter.treasure.popo);
        if(v == 1){
            plateau->etage[x_coffre][y_coffre].Inter.treasure.popo.type_objet = 2;
        }
    }
    if((clic_x >852 && clic_x < 956) && (clic_y > 387 && clic_y < 515)){
        v = get_objet(p, plateau->etage[x_coffre][y_coffre].Inter.treasure.equip);
        if(v == 1){
            plateau->etage[x_coffre][y_coffre].Inter.treasure.equip.type_objet = 2;
        }
    }
    
}



Player* upLv(Player* p, Images im){
    
    int neededExp;

    neededExp = 350 + (50 * p->Lv);

    if (p->Exp > neededExp){
        p->Exp = p->Exp - neededExp;
        p->Lv += 1;
        MLV_actualise_window();
        choix_amelioration(p, im);
        p->HP = setHP(p->Def);
        p->MP = setMP(p->Int);
        if(p->Lv%5==0)p->vision++;
        if(p->vision > 6)p->vision = 6;
    
    }


    return p;
}


void choix_amelioration(Player * p, Images im){
    int x, y, i, valide = 0;
    MLV_draw_image(im.images[76], 0, 0);
    MLV_actualise_window();
    for(i = 0; i < 3; i++){
        do{
            MLV_wait_mouse(&x, &y);
            if(y>430 && y < 573){
                if(x > 167 && x < 270){
                    p->Atk+= 1;
                    valide = 1;
                }
                if(x > 600 && x < 705){
                    p->Def+= 1;
                    valide = 1;
                }
                if(x > 1032 && x < 1134){
                    p->Int+= 1;
                    valide = 1;
                }

            }

        }while(valide != 1);
        
        valide = 0;
    }
}

void fin(Donjon plateau, Player * p, Images images){
    game_over(plateau, p);
    free_image(images);
    free(p);
    free_donjon(plateau);
    MLV_free_window();
}

void exit_total(Donjon plateau, Player * p, Images images){
    sauve_donjon(plateau);
    sauve_player(p);
    fin(plateau, p, images);
}   







