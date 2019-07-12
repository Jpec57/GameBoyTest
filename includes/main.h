//
// Created by Jean-Paul BELLA on 2019-07-09.
//

#ifndef FIRST_MAIN_H
#define FIRST_MAIN_H

#include "../includes/player.h"
#include "../includes/tileset.h"
#include "../includes/window_tilemap.h"
#include "../includes/window_tileset.h"

#include "../res/tiles/helloWorld.c"
#include "../res/tiles/alpha.c"
#include "../res/tiles/window_tileset.c"

#include "../res/sprites/player.c"
#include "../src/sprites/sprites_operations.c"
#include "../res/tiles/tileset.c"
#include "../res/map/blankScreen.c"
#include "../res/map/tilemap.c"
#include "../res/map/window_tilemap.c"

#define PLAYER_SPRITE_L_ID 0
#define PLAYER_SPRITE_R_ID 1

#define SCREEN_TILE_HEIGHT 20
#define SCREEN_TILE_WIDTH 18

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

void flip_sprite_horiz(UINT8 sprite_id);
void unflip_sprite_horiz(UINT8 sprite_id);
UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame);
#endif //FIRST_MAIN_H
