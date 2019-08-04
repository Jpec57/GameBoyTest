#include <gb/gb.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/main.h"

UINT8 player[2];
UINT8 player_direction;
UINT8 player_animation_frame;
UINT8 is_player_walking;
UINT8 screen_offset[2];

int check_if_ground_is_walkable(){
    int i;
    int pos1;
    int pos2;
    int threshold;

    i = 0;
    threshold = 2;
    pos1 = TILEMAP[(player[1] / 8) * TILEMAP_HEIGHT + (player[0] / 8)];
    pos2 = TILEMAP[((player[1] - 1) / 8) * TILEMAP_HEIGHT + ((player[0] - 1) / 8)];
    while (i < WALKABLE_GROUND_SIZE){
        if (WALKABLE_GROUND[i] == pos1){
            threshold -= 1;
        }
        if (WALKABLE_GROUND[i] == pos2){
            threshold -= 1;
        }
        if (!threshold){
            return (1);
        }
        i++;
    }
    return (0);
}

void    *ft_memcpy(void *dest, const void *src, size_t n)
{
    unsigned char			*dst;
    const unsigned char		*s;

    dst = dest;
    s = src;
    while (n--)
        *dst++ = *s++;
    return (dest);
}

//int get_number_size(int num){
//    int size;
//    int i;
//
//    i = 0;
//    size = 0;
//    if (num < 0){
//        size++;
//    }
//    while (num > 9){
//        size++;
//        num = num / 10;
//    }
//    return size;
//}
//
//UINT8   show_number(int num){
//    int size = get_number_size(num);
//    UINT8 res[size];
//
//    if (num < 0){
//        res[0] = 10;
//        res[1] = num % 10;
//    } else {
//        res[0] = num % 10;
//    }
//
//    while (num > 9){
//        size = size - 1;
//        res[size - 1];
//        num = num / 10;
//    }
//    return res;
//}

int write_on_screen(char *text){
    int cursor;
    int size;
    int i;
    int j;

    convert_text(text);
    size = ft_strlen(text);

    i = 0;
    j = 0;
    cursor = 0;
    while (cursor < size){
        if (cursor != 0)
            waitpad(J_START);
        while (j < WINDOW_TILEMAP_HEIGHT){
            i = 0;
            while (i < WINDOW_TILEMAP_WIDTH){
                WINDOW_TILEMAP[i + j * WINDOW_TILEMAP_WIDTH] = text[cursor];
                i++;
                cursor++;
            }
            j++;
         }
         j = 0;
        set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
        move_win(7, 128);
        wait_vbl_done();
    }

}

void change_indic(){
    char text[] = "THISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATESTTHISISATEST\0";
//    WINDOW_TILEMAP[4] = 55;
//    WINDOW_TILEMAP[5] = 56;
//    WINDOW_TILEMAP[24] = 67;
//    WINDOW_TILEMAP[25] = 68;

//    WINDOW_TILEMAP[0] = 36;
//    WINDOW_TILEMAP[1] = 24;
//    WINDOW_TILEMAP[2] = 25;
//    WINDOW_TILEMAP[3] = 35;

    write_on_screen(text);
    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
    move_win(7, 128);
}
void check_if_is_colliding(UINT8 previous_coord[2]){
    if (check_if_ground_is_walkable()){
        if (player_direction == PLAYER_DIRECTION_DOWN) {
            //TODO
//            if (80 < player[1] && screen_offset[1] < TILEMAP_HEIGHT * 8 - (72 * 2)){
            if (screen_offset[1] < TILEMAP_HEIGHT * 8 - (72 * 2)){
                scroll_bkg(0, 1);
                screen_offset[1] -= 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, 0, 1);
                scroll_sprite(PLAYER_SPRITE_R_ID, 0, 1);
            }
        }
        if (player_direction == PLAYER_DIRECTION_UP) {
            if (0 < player[1] && 0 < screen_offset[1]){
                scroll_bkg(0, -1);
                screen_offset[1] += 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, 0, -1);
                scroll_sprite(PLAYER_SPRITE_R_ID, 0, -1);
            }
        }

        if (player_direction == PLAYER_DIRECTION_LEFT) {
            if (0 < player[0] && 0 < screen_offset[0]){
                scroll_bkg(-1, 0);
                screen_offset[0] -= 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, -1, 0);
                scroll_sprite(PLAYER_SPRITE_R_ID, -1, 0);
//                move_sprite(PLAYER_SPRITE_L_ID, player[0], player[1]);
//                move_sprite(PLAYER_SPRITE_R_ID, player[0] + 8, player[1]);
            }
        }
        if (player_direction == PLAYER_DIRECTION_RIGHT) {
            if (80 < player[0] && screen_offset[0] < TILEMAP_WIDTH * 8 - 160){
                scroll_bkg(1, 0);
                screen_offset[0] += 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, 1, 0);
                scroll_sprite(PLAYER_SPRITE_R_ID, 1, 0);
            }
        }


    } else {
        player[0] = previous_coord[0];
        player[1] = previous_coord[1];
    }
}

void move_user(){
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
            change_indic();
        }

        if (is_player_walking) {
            check_if_is_colliding(previous_coord);
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
}

void update_switches() {
    SHOW_WIN;
    SHOW_SPRITES;
    SHOW_BKG;
}

void init_user(){
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
/**
 * Set tiles in memory
 */
void set_tile_data(){
    /*
*   first_tile : la case mémoire à partir de laquelle on va placer les tuiles (si on met 16 par exemple, la première tuile de notre tileset se trouvera dans la case 16, la seconde dans la case 17,... C'est ce numéro que l'on retrouvera dans la tilemap).
*   nb_tiles : nombre de tuiles à copier dans la mémoire vidéo.
*   data : pointeur vers les données de nos tuiles.
*/
    //ALPHA
    set_bkg_data(0, 47, alpha);
    //FIRST MAP
    set_bkg_data(47, TILESET_TILE_COUNT, TILESET);
    //WINDOW
    set_bkg_data(47 + TILESET_TILE_COUNT, WINDOW_TILESET_TILE_COUNT, WINDOW_TILESET);
}

void init(){
    DISPLAY_ON;

    set_tile_data();
    /*
 *  x, y :  Coordonnées de destination de notre tilemap (là où elle sera collée sur la couche Background).
 *          Les coordonnées sont exprimées en tuiles (entier entre 0 et 31).
 *  w, h :  Largeur et hauteur de notre tilemap, exprimées en tuiles (entier entre 0 et 31).
 *  tiles : pointeur vers les données de la tilemap.
 */
    set_bkg_tiles(0, 0, TILEMAP_HEIGHT, TILEMAP_WIDTH, TILEMAP);

    //window
    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
    move_win(7, 128);

    screen_offset[0] = 0;
    screen_offset[1] = 0;
    init_user();
}

void main() {
    init();
    update_switches();
    wait_vbl_done();
//    waitpad(J_START);
    while (1) {
        move_user();
    }
}
