/* player */
 

#include "../inc/player.h"


Player* initPlayer(Player* p){
    int i;
    p->Exp = 0;
    p->Lv = 0;
    p->Atk = 10;
    p->Int = 10;
    p->Def = 10;
    p->HP = setHP(p->Def);
    p->MP = setMP(p->Int);
    p->pos_x = 32;
    p->pos_y = 22;
    p->face = SUD;
    p->arme = 0;
    p->arme_cac = 0;
    p->arme_magic = 0;
    p->armure = 0;
    for(i = 0; i < 12; i++)p->inventory[i].type_objet = VIDE;
    for(i = 0; i < 4; i++)p->actual_effect[i] = 0;
    p->vision = 1;
	p->monstre_tue = 0;
    
    return p;
}


int setHP(int Def){
    return Def * 10;
}


int setMP(int Int){
    return (Int * 10) - 50;
}


Player* allocPlayer(){
    Player* p;
    
    p = (Player*) malloc(sizeof(Player));
    if (p == NULL){
        fprintf(stderr, "Not enough memory !\n");
        exit(1);
    }
    initPlayer(p);

    return p;
}






void direction_to_int(int * x, int * y, int direction, Player * p){
	if(direction == 5){
        p->face = NORD;
		*y-=1;
    }

	if(direction == 2){
        p->face = SUD;
		*y+=1;
    }

	if(direction == 3){
        p->face = EST;
		*x+=1;
    }

	if(direction == 1){
        p->face = OUEST;
		*x-=1;
    }
}

int moving(Player * p, int direction, Donjon plateau){
	int x = 0, y = 0, mort = 0;
	direction_to_int(&x, &y, direction, p);
	if(plateau->etage[p->pos_x+x][p->pos_y+y].type == ROOM || plateau->etage[p->pos_x+x][p->pos_y+y].type == STAIR_UP || plateau->etage[p->pos_x+x][p->pos_y+y].type == STAIR_DOWN){
		p->pos_x += x;
		p->pos_y +=y;
        tour_potion(p);
		mort = is_monster_around(p, plateau);
    }
    return mort;
	

}

int attackPlayer(Player* p){

    if (p->arme == 0){
        float aleaAtk = 80;
        aleaAtk += rand() % 40;
        aleaAtk = aleaAtk/100;
        return (aleaAtk*p->Atk)*aleaCritiqueAttack(p);

        }

    else if (p->arme == 1 && p->MP>=20){
        p->MP -= 20;
        if(p->MP < 0)p->MP = 0;
        return 2*p->Int*aleaCritiqueAttack(p);
        
    }

return 0;
}

int aleaCritiqueAttack(Player* p){
    srand(time(NULL));
    int aleaCritique = 0, calculator = 20;
    if(p->actual_effect[PRECISION] == 1)calculator = 7;
    aleaCritique = rand() % calculator;

    if (aleaCritique == 5)
        return 3;  
    return 1;
}




void printPlayerInfos(Player* p){
    printf("Player stats :\n");
    printf("    HP : %d\n", p->HP);
    printf("    MP : %d\n", p->MP);
    printf("    Atk : %d\n", p->Atk);
    printf("    Int : %d\n", p->Int);
    printf("    Def : %d\n", p->Def);
    printf("    Exp : %d\n", p->Exp);
    printf("    Lv : %d\n", p->Lv);
}

int is_monster_around(Player* p, Donjon plateau){
    int mort = 0;
    if(p->pos_x+1 < 63 && p->pos_y+1 < 43 && p->pos_x-1 > 0 && p->pos_y-1 > 0){
        if (plateau->etage[p->pos_x+1][p->pos_y].type == MONSTER){
        mort = monster_attack(p, plateau, plateau->etage[p->pos_x+1][p->pos_y].Inter.monster);
        }
        if(plateau->etage[p->pos_x-1][p->pos_y].type == MONSTER){
            mort = monster_attack(p, plateau, plateau->etage[p->pos_x-1][p->pos_y].Inter.monster);
        }

        if(plateau->etage[p->pos_x][p->pos_y+1].type == MONSTER){
            mort = monster_attack(p, plateau, plateau->etage[p->pos_x][p->pos_y+1].Inter.monster);
        }

        if(plateau->etage[p->pos_x][p->pos_y-1].type == MONSTER){
            mort = monster_attack(p, plateau, plateau->etage[p->pos_x][p->pos_y-1].Inter.monster);
        }
    }
    
    return mort;
}

int playerIsDead(Player* p){
    /*vérifie si le joueur est mort*/
    if (p->HP <= 0) 
    {
        return 1;
    }
    return 0;
}

int monster_attack(Player * p, Donjon plateau, Monster * m){
    int mort = 0;
	p->HP-= attackMonster(m);
    effet_monstre(m, p, plateau);
	mort = playerIsDead(p);
	return mort;
}

void faceDirection(Player * p, int * x, int * y){
    switch(p->face){
        case NORD:
            *y = *y-1;
            break;
        case SUD:
            *y = *y+1;
            break;
        case EST:
            *x = *x+1;
            break;
        case OUEST:
            *x = *x-1;
            break;
        default:
            break;


    }
}


int facingMonster(Player * p, Donjon plateau){
    
    int x, y;
    x = p->pos_x;
    y = p->pos_y;
    faceDirection(p, &x, &y);
    if(plateau->etage[x][y].type == MONSTER){
        return 1;
    }
    return 0;
}

int facingTreasure(Player * p, Donjon plateau){
    int x, y;
    x = p->pos_x;
    y = p->pos_y;
    faceDirection(p, &x, &y);
    if(plateau->etage[x][y].type == TREASURE){
        return 1;
    }
    return 0;
}

int combat(Player * p, Donjon plateau){
    tour_potion(p);
    int x, y;
    x = p->pos_x;
    y = p->pos_y;
    faceDirection(p, &x, &y);
    plateau->etage[x][y].Inter.monster->HP -= attackPlayer(p);
    if(isDead(plateau->etage[x][y].Inter.monster) == 1){
        p->Exp += xp_earn(p);
        p->monstre_tue ++;
        plateau->etage[x][y].type = ROOM;
        return 2;
        }
    monster_attack(p, plateau, plateau->etage[x][y].Inter.monster);

    return 1;
}

void effet_monstre(Monster * m, Player * p, Donjon plateau){
    if(m->princesse == SIRENE){
        p->MP -= 2*plateau->floor;
        if(p->MP < 0)p->MP = 0;
    }
    if(m->princesse == RAIPONCE){
        p->Exp -= 5*p->Lv;
        if(p->Exp < 0)p->Exp = 0;
    }
}

int xp_earn(Player * p){
    if(p->actual_effect[2]>0){
        return (int)50*1.3;
    }
    return 100;
}


void potion_healing(Player * p){
    p->HP += setHP(p->Def) * 0.10;
    if(p->HP > setHP(p->Def))
        setHP(p->Def); 
}

void potion_magic(Player * p){
    p->MP += setMP(p->Int) * 0.10;
      if(p->HP > setMP(p->Int))
        setMP(p->Int); 
    }

void potion_regeneration(Player * p){
    p->actual_effect[REGEN] = 30;
}



void using_popo(Player * p, Effect eff){
    if(eff == HEAL){
        potion_healing(p);
        return;
    }
    if(eff == MANA){
        potion_magic(p);
        return;
    }
    p->actual_effect[eff] = 30;
    if(eff == TORCHE)p->actual_effect[eff] = 15;
    return;

}

void effet_potion_regen(Player * p){
    if(p->actual_effect[REGEN] > 0 && p->actual_effect[REGEN]%3 == 0){
        p->HP += 20;
         if(p->HP > setHP(p->Def))
            p->HP = setHP(p->Def);
        p->MP += 10;
        if(p->HP > setMP(p->Int))
            p->MP = setMP(p->Int);
    }
}

void tour_potion(Player * p){
    int i;
    for(i = 0; i < 4; i++){
        if(i == 0){
            effet_potion_regen(p);
        }
        if(p->actual_effect[i]>0){
            p->actual_effect[i]--;
        }


    }
}


int get_objet(Player * p, Objets obj){
    int i;
    for(i = 0; i < 12; i++){
        if(obj.type_objet == PERM && p->inventory[i].type_objet == PERM){
            if(obj.Element.equip.quality > p->inventory[i].Element.equip.quality && obj.Element.equip.cathegorie == p->inventory[i].Element.equip.cathegorie){
                p->inventory[i] = obj;
                effet_equip(p->inventory[i], p);
                return 1;
            }
            if(obj.Element.equip.cathegorie == p->inventory[i].Element.equip.cathegorie){
                return 0;
            }
        }
        if(p->inventory[i].type_objet == VIDE){
            p->inventory[i] = obj;
            effet_equip(p->inventory[i], p);
            return 1;
        }
    }
    return 0;
}



int visiting_cell(Donjon plateau, Player * p){
    int i, j, vision;
    vision = p->vision;
    if(p->actual_effect[3]>0)vision++;
    for(i = -vision; i < vision+1; i++){
        for(j = -vision; j < vision+1; j++){
            if((p->pos_x+i) < 63 && (p->pos_y+j) < 43 && (p->pos_x+i) > 0 && (p->pos_y+j) > 0){
                plateau->etage[p->pos_x+i][p->pos_y+j].visited = 1;
            }
        }
    }

    return 0;
}

int effet_equip(Objets obj, Player * p){
    if(obj.type_objet == PERM){
        if(obj.Element.equip.cathegorie == WAND){
        p->Int += 2*obj.Element.equip.quality;
        }
        if(obj.Element.equip.cathegorie == WEAPOND){
            p->Atk += 2*obj.Element.equip.quality;
        }
        if(obj.Element.equip.cathegorie == ARMOR){
            p->armure = obj.Element.equip.quality;
            p->Def += 2*obj.Element.equip.quality;
        }
    }
    return 1;

}

void sauve_player(Player * p){
    FILE * player;
    player = fopen("sauvegardes/player.bin", "w");
    fwrite(p, 1, sizeof(p), player);
    fclose(player);
}

Player * read_player(Player * p){
    FILE * player;
    player = fopen("sauvegardes/player.bin", "r");
    fread(p, 1, 1000000, player);
    fclose(player);
    return p;
}

