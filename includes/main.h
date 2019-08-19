//
// Created by Jean-Paul BELLA on 2019-07-09.
//

#ifndef FIRST_MAIN_H
#define FIRST_MAIN_H

#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1

#define MAX_SPRITE_NUM 3

#define SCREEN_TILE_HEIGHT 20
#define SCREEN_TILE_WIDTH 18

#define BACKGROUND_WIDTH 32
#define BACKGROUND_HEIGHT 32

#define WHITE  0
#define SILVER 1
#define GRAY   2
#define BLACK  3
#define PALETTE(c0, c1, c2, c3) c0 | c1 << 2 | c2 << 4 | c3 << 6

#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include <types.h>
#include "../includes/player.h"
#include "../includes/tileset.h"
#include "../includes/tilemap.h"
#include "../includes/window_tilemap.h"
#include "../includes/window_tileset.h"


#include "../res/tiles/helloWorld.c"
#include "../res/tiles/alpha.c"
#include "../res/tiles/window_tileset.c"
#include "../res/tiles/tileset.c"

#include "../res/sprites/player.c"
#include "../src/sprites/sprites_operations.c"
#include "../src/sprites/map_movements.c"

#include "../res/map/blankScreen.c"
#include "../res/map/blank_window.c"
#include "../res/map/tilemap.c"
#include "../res/map/window_tilemap.c"

#include "../src/utils/text.c"
#include "../src/utils/window_operations.c"

// Données de l'animation des sprites du joueur
UINT8 PLAYER_SPRITE_ANIM_L[] = {
// TAILLE | MIROIR |         ID DES TUILES   | DIRECTION
        4,       0,        0 , 4,  0,  8,   // Bas
        4,       0,       12, 16, 12, 20,   // Haut
        4,       0,       24, 28, 24, 32,   // Droite
        4,       1,       26, 30, 26, 34,   // Gauche
};
UINT8 PLAYER_SPRITE_ANIM_R[] = {
// TAILLE | MIROIR |         ID DES TUILES   | DIRECTION
        4,       0,        2,  6,  2, 10,   // Bas
        4,       0,       14, 18, 14, 22,   // Haut
        4,       0,       26, 30, 26, 34,   // Droite
        4,       1,       24, 28, 24, 32,   // Gauche
};

// Liste des sous-animation (les nombre représentent l'octet où la
// sous-animation commence dans les données globales de l'animation du
// joueur)
#define PLAYER_DIRECTION_DOWN  0
#define PLAYER_DIRECTION_UP    6
#define PLAYER_DIRECTION_RIGHT 12
#define PLAYER_DIRECTION_LEFT  18

#define WALKABLE_GROUND_SIZE 1
int WALKABLE_GROUND[WALKABLE_GROUND_SIZE] = {47};

void flip_sprite_horiz(UINT8 sprite_id);
void unflip_sprite_horiz(UINT8 sprite_id);
UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame);

int ft_strlen(char *str);
char *ft_itoa(int num);
void convert_text(char *text);

//void keep_sprites_static_while_moving(int bkg_dir_x, int bkg_dir_y);

//int write_on_screen(char *text);

void wait_frames(INT8 count);
#endif //FIRST_MAIN_H
