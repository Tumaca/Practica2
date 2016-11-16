#include "stdafx.h"
#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

static const int	ANCHOMUNDO = 50;
static const char	PLAYER = 'X';
static int			POS_PLAYER = ANCHOMUNDO / 2;
static const char	BACKGROUND = '-';
static const char	BULLET = 'o';
static int			POS_BULLET = -1;
//Bool que se pone en true si hay una bala en el mapa
static bool			BULLETEXIST = false;
static int			BULLET_DIRECTION;
//Bool que especifica si hay un enemigo en pantalla.
static bool			ENEMYEXIST = false;
static const char	ENEMY = 'E';
static int			POS_ENEMY = -5;
//Direccion del enemigo
static int			DIRECTION_ENEMY;

void pintaMundo() {
	
	for (int i = 0; i < ANCHOMUNDO; i++) {
		if (i == POS_PLAYER) { printf("%c", PLAYER); }
		else if (i == POS_BULLET) { printf("%c", BULLET); }
		else if (i == POS_ENEMY) { printf("%c", ENEMY); }
		else { printf("%c", BACKGROUND); }
	}
	cout << '\r';
}
int main()
{
	printf("\n");
	int key;

	pintaMundo();
	

	while (1) {
		
			if (_kbhit()) {
				key = _getch();
				if (key == 'a') {
					if (POS_PLAYER > 0) { --POS_PLAYER; }
				}
				else if (key == 'd') {
					if (POS_PLAYER < ANCHOMUNDO-1 ) { ++POS_PLAYER; }
				}

				if (!BULLETEXIST) {
					if (key == 'j') {
						if (POS_BULLET < ANCHOMUNDO - 1) {
							POS_BULLET = POS_PLAYER - 1;
							BULLET_DIRECTION = -1;
							BULLETEXIST = true;
						}
					} else if (key == 'k') {
						if (POS_BULLET < ANCHOMUNDO - 1) {
							POS_BULLET = POS_PLAYER + 1;
							BULLET_DIRECTION = 1;
							BULLETEXIST = true;
						}
					}
				}
				key = 0;
			}
		

		if (BULLETEXIST) {
			if (POS_BULLET < 0 || POS_BULLET>ANCHOMUNDO) {
				POS_BULLET = -1;
				BULLETEXIST = false;
				
			}
			else {
				if (BULLET_DIRECTION == 1) { ++POS_BULLET; }
				else { --POS_BULLET; }
			}
		}
		//spawn an enemy
		if (!ENEMYEXIST) {
			if ((rand() & 2) == 0) {
				POS_ENEMY = 0;
				DIRECTION_ENEMY = 1;
			} else {
				POS_ENEMY = ANCHOMUNDO-1;
				DIRECTION_ENEMY = -1;
			}
			ENEMYEXIST = true;
		} else {
			if (DIRECTION_ENEMY == -1) { --POS_ENEMY; }
			else { ++POS_ENEMY; }
		}

		//chequea la colision de la bala con el enemigo
		if (BULLETEXIST) {
			if (POS_ENEMY == POS_BULLET || POS_ENEMY - DIRECTION_ENEMY == POS_BULLET ) {
				POS_BULLET = -1;
				POS_ENEMY = -5;
				ENEMYEXIST = false;
			}
		}
		//chequea la colision del enemigo con el jugador
		if (POS_ENEMY == POS_PLAYER || POS_ENEMY - DIRECTION_ENEMY == POS_PLAYER) {
			POS_ENEMY = -5;
			ENEMYEXIST = false;
			POS_BULLET = -1;
			BULLETEXIST = false;
			printf("%s", "GAME OVER");
			if (!_kbhit()) {key = _getch();}
			POS_PLAYER = ANCHOMUNDO / 2;
		}
		
		pintaMundo();
		Sleep(50);
	}
	
	return 0;
}
