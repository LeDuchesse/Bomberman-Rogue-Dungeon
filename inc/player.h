/*player.h*/
 

#ifndef __PLAYER__
#define __PLAYER__


	/* Modules */


	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
	#include "../inc/terrain.h"
	#include "../inc/monster.h"
	/*#include "../inc/treasure.h"*/
	#include "time.h"



	/* Macros */


	/* Structures */

	typedef enum{
		NORD, SUD, EST, OUEST
	}Facing;

	/**
	 * @brief Struct player (player infos)
	 * Contains seven int's that represents
	 * the player status.
	 */
	typedef struct {
		int HP;
		int MP;
		int Atk;
		int Int;
		int Def;
		int Exp;
		int Lv;
		int pos_x;
		int pos_y;
		Facing face;
		Objets inventory [12];
		int arme; 
		int arme_cac;
		int arme_magic;
		int armure;
		Effect actual_effect[4]; /*Effet de potion actuel sur le joueur*/
		int vision;
		int monstre_tue;
	} Player;

	



	/* Fonctions */


	/**
	 * @brief Initiates the default player
	 * with the fields Atk, Int and Def set
	 * to 10, HP to 100 and MP to 50.
	 * Exp and Lv are set to 0.
	 * @param p the player
	 * @return Player*
	 */
	Player* initPlayer(Player* p);


	/**
	 * @brief Calculates the player's HP
	 * from his Def.
	 * @param Def defense of the player
	 * @return int
	 */
	int setHP(int Def);


	/**
	 * @brief Calculates the player's MP
	 * from his Int.
	 * @param Int intelligence of the player
	 * @return int
	 */
	int setMP(int Int);


	/**
	 * @brief Allocates a new Player.
	 * @return Player*
	 */
	Player* allocPlayer();


	/**
	 * @brief Frees the player.
	 * @param p the player
	 */
	void freePlayer(Player* p);


	/**
	 * @brief Increases player level
	 * by one if he can level up.
	 * @param p the player
	 * @return Player*
	 */


	/**
	 * @brief Allows to attribute 3 new
	 * skill points between player's Atk,
	 * Int and Def.
	 * @param p the player
	 * @return Player*
	 */
	Player* attributesAttribution(Player* p);


    /**
     * @brief Prints every stats of
     * the player.
     * @param p the player
     */
    void printPlayerInfos(Player* p);

    int attackPlayer(Player* p);

    /*Convert keyboard entry to coor*/
    void direction_to_int(int * x, int * y, int direction, Player * p);

    /*Move the player*/
    int moving(Player * p, int direction, Donjon plateau);

    /*Attaque le joueur si il se trouve sur une case adjascente*/
	int is_monster_around(Player* p, Donjon plateau);

	/*Attaque de monstre infligeant des dégats au joueur*/
	int monster_attack(Player * p, Donjon plateau, Monster * m);

	/*Vérifie si le joueur n'est pas mort*/
	int playerIsDead(Player* p);

	/*Renvoie la coordonnée en face du joueur selon sa direction*/
	void faceDirection(Player * p, int * x, int * y);


	/*Vérifie si le joueur est en face d'un monstre*/
	int facingMonster(Player * p, Donjon plateau);

	/*Vérifie si le joueur est en face d'un trésore*/
	int facingTreasure(Player * p, Donjon plateau);

	/*Action du combat*/
	int combat(Player * p, Donjon plateau);

	/*Renvoie les dégats qui vont être infligés multiplié par 3 ou 1 en fonction de si le coup est critique ou non*/
	int aleaCritiqueAttack(Player* p);

	/*Redonne dela vie au joueur en fonction de sa défense*/
	void potion_healing(Player * p);

	/*Redonne du mana au joueur en fonction de son intelligence*/
	void potion_magic(Player * p);

	/*Redonne du mana et de la vie au joueur tout les 3 tours*/
	void potion_regeneration(Player * p);
	
	/*Simule l'action de l'usure de la potion en fonction du tour*/
	void tour_potion(Player * p);

	/*Prend l'objet d'un coffre pour le mettre dans son inventaire.
	 *Les equipements ayant une meilleur qualité remplace automatiquement plus faible
	 *Ne fait rien si le joueur a un inventaire plein
	 */

	int get_objet(Player * p, Objets obj);

	/*utilise une potion sélectionné*/
	void using_popo(Player * p, Effect eff);

	/*Donne de l'xp au joueur lorse qu'il tue un monstre*/
	int xp_earn(Player * p);


	/*Rend les cases visible au joueur en fonction de sa vision*/
	int visiting_cell(Donjon plateau, Player * p);


	/*Donne le bonus de def, atk, int en fonction de l'équipement*/
	int effet_equip(Objets obj, Player * p);

	void sauve_player(Player * p);

	void effet_monstre(Monster * m, Player * p, Donjon plateau);

	Player * read_player(Player * p);

#endif
