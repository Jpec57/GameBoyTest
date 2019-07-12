#include <gb/gb.h>
#include <stdio.h>
#include "../includes/main.h"

UINT8 player[2];
UINT8 player_direction;
UINT8 player_animation_frame;
UINT8 is_player_walking;

void checkIfIsColliding(UINT8 previous_coord[2]){
    if (!TILEMAP[(player[1] / 8) * 20 + (player[0] / 8)]
        && !TILEMAP[((player[1] - 1) / 8) * 20 + ((player[0] - 1) / 8)]){
        move_sprite(PLAYER_SPRITE_L_ID, player[0], player[1]);
        move_sprite(PLAYER_SPRITE_R_ID, player[0] + 8, player[1]);
    } else {
        player[0] = previous_coord[0];
        player[1] = previous_coord[1];
    }
}

void moveUser(){
    UINT8 keys;
    UINT8 prev_keys = 0;
    UINT8 frame_skip = 8;
    UINT8 previous_coord[2];

    while (1){
        wait_vbl_done();
        keys = joypad();
        previous_coord[0] = player[0];
        previous_coord[1] = player[1];
        is_player_walking = 1;
        if (keys & J_UP) {
            player_direction = PLAYER_DIRECTION_UP;
            player[1] -= 1;
        } else if (keys & J_DOWN) {
            player_direction = PLAYER_DIRECTION_DOWN;
            player[1] += 1;
        } else if (keys & J_LEFT) {
            player_direction = PLAYER_DIRECTION_LEFT;
            player[0] -= 1;
        } else if (keys & J_RIGHT) {
            player_direction = PLAYER_DIRECTION_RIGHT;
            player[0] += 1;
        } else {
            is_player_walking = 0;
            frame_skip = 1;
        }
        if (keys & J_START){
            move_bkg(0, 0);
        }

        if (is_player_walking) {
            checkIfIsColliding(previous_coord);
            frame_skip -= 1;
            if (!frame_skip) {
                frame_skip = 8;
            } else {
                continue;
            }
        } else {
            player_animation_frame = 0;
        }
        prev_keys = keys;
        // On met à jour les tuiles utilisées dans les sprites
        update_sprite_animation(
                PLAYER_SPRITE_L_ID,
                PLAYER_SPRITE_ANIM_L,
                player_direction,
                player_animation_frame);
        player_animation_frame = update_sprite_animation(
                PLAYER_SPRITE_R_ID,
                PLAYER_SPRITE_ANIM_R,
                player_direction,
                player_animation_frame);
    }

//    if (joypad() & J_LEFT) {
//        player[0]--;
//        scroll_bkg(-1, 0);
//    }
//    if (joypad() & J_RIGHT) {
//        player[0]++;
//        scroll_bkg(1, 0);
//    }
//    move_sprite(0, player[0], player[1]);
}

void updateSwitches() {
    SHOW_WIN;
    SHOW_SPRITES;
    SHOW_BKG;
}

void initUser(){
    player_direction = PLAYER_DIRECTION_DOWN;
    player_animation_frame = 0;
    is_player_walking = 0;
    player[0] = 80;
    player[1] = 72;

    // On utilise des sprites de 8×16 px
    SPRITES_8x16;
    // Charge les tuiles des sprites dans la mémoire vidéo
    set_sprite_data(0, PLAYER_SPRITES_TILE_COUNT, PLAYER_SPRITES);

    // On initialise les deux sprites qui représentent le joueur
    move_sprite(PLAYER_SPRITE_L_ID, player[0], player[1]);
    set_sprite_prop(PLAYER_SPRITE_L_ID, S_PALETTE);

    move_sprite(PLAYER_SPRITE_R_ID, player[0] + 8, player[1]);
    set_sprite_prop(PLAYER_SPRITE_R_ID, S_PALETTE);

    update_sprite_animation(PLAYER_SPRITE_L_ID, PLAYER_SPRITE_ANIM_L, PLAYER_DIRECTION_DOWN, 0);
    update_sprite_animation(PLAYER_SPRITE_R_ID, PLAYER_SPRITE_ANIM_R, PLAYER_DIRECTION_DOWN, 0);
}

void init(){
    DISPLAY_ON;
    /*
    *   first_tile : la case mémoire à partir de laquelle on va placer les tuiles (si on met 16 par exemple, la première tuile de notre tileset se trouvera dans la case 16, la seconde dans la case 17,... C'est ce numéro que l'on retrouvera dans la tilemap).
    *   nb_tiles : nombre de tuiles à copier dans la mémoire vidéo.
    *   data : pointeur vers les données de nos tuiles.
    */
    set_bkg_data(0, TILESET_TILE_COUNT, TILESET);

    /*
     *  x, y :  Coordonnées de destination de notre tilemap (là où elle sera collée sur la couche Background).
     *          Les coordonnées sont exprimées en tuiles (entier entre 0 et 31).
     *  w, h :  Largeur et hauteur de notre tilemap, exprimées en tuiles (entier entre 0 et 31).
     *  tiles : pointeur vers les données de la tilemap.
     */
    set_bkg_tiles(0, 0, SCREEN_TILE_HEIGHT, SCREEN_TILE_WIDTH, TILEMAP);

    set_bkg_data(TILESET_TILE_COUNT, WINDOW_TILESET_TILE_COUNT, WINDOW_TILESET);

    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
    move_win(7, 128);
    initUser();
}

void main() {
    init();
    updateSwitches();
    wait_vbl_done();
//    waitpad(J_START);
    while (1) {
        moveUser();
    }
}
