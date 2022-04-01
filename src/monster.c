/* monster */


#include "../inc/monster.h"



Monster* initMonster(Monster* m, int x, int y, int etage){
    m->Atk = 0 + 10*etage;
    m->HP = 40 + 10*etage;
    m->pos_x = x;
    m->pos_y = y;
    m->princesse = rand()%5;
    typeMonster(m);
    return m;
}



void typeMonster(Monster* m){
    switch(m->princesse){
        case BN:
            break;

        case CENDRILLON:
            m->Atk *= 0.8; 
            m->HP *= 1.3; 
            break;

        case YASMINE:
            m->Atk *= 1.3; 
            m->HP /= 3; 
            break;

        case SIRENE:
            break;

        case RAIPONCE:
            break;
        default:
            break;

    }
}



Monster* allocMonsters(){
    Monster* m;
    
    m = (Monster*) malloc(sizeof(Monster));
    if (m == NULL){
        fprintf(stderr, "Not enough memory !\n");
        exit(1);
    }
    initMonster(m, 0, 0, 1);

    return m;
}


void freeMonster(Monster* m){
    free(m);
}

int isDead(Monster* m){
    if (m->HP <= 0) 
    {
        freeMonster(m);
        return 1;
    }
    return 0;
}
    

int attackMonster(Monster* m){

    srand(time(NULL));
    float aleaAtk = 80;
    aleaAtk += rand() % 40;
    aleaAtk = aleaAtk/100;
    int aleaCritique = 0;
    aleaCritique = rand() % 100;
    if (aleaCritique == 10||aleaCritique == 20||aleaCritique == 30||aleaCritique == 40||aleaCritique == 50)
    {
        return (aleaAtk*m->Atk)*3;    
    }
    return aleaAtk*m->Atk;
}


