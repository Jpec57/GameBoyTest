#include "../includes/main.h"

UINT8 player[2];
UINT8 player_direction;
UINT8 player_animation_frame;
UINT8 is_player_walking;
UINT8 screen_offset[2];

int check_if_ground_is_walkable(int pos_x, int pos_y, int sprite_size){
    int i;
    int pos1;
    int pos2;

    i = 0;
    pos1 = TILEMAP[(pos_y / 8) * TILEMAP_HEIGHT + (pos_x / 8)];
    pos2 = TILEMAP[((pos_y - 1) / 8) * TILEMAP_HEIGHT + ((pos_x - 1) / 8)];
    while (i < WALKABLE_GROUND_SIZE){
        if (WALKABLE_GROUND[i] == pos1){
            sprite_size -= 1;
        }
        if (WALKABLE_GROUND[i] == pos2){
            sprite_size -= 1;
        }
        if (!sprite_size){
            return (1);
        }
        i++;
    }
    return (0);
}

void change_indic(){
    char text[] = "THIS IS A TEST THIS IS A TEST THIS IS A TEST THIS IS A JPEC 57\0";

//    write_on_screen(text);
    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
    move_win(7, 128);
}

void check_if_is_colliding(UINT8 previous_coord[2]){
    if (check_if_ground_is_walkable(player[0], player[1], 2)){
        if (player_direction == PLAYER_DIRECTION_DOWN) {
            if (80 < player[1] && screen_offset[1] < (TILEMAP_HEIGHT - WINDOW_TILEMAP_HEIGHT) * 8 - (72 * 2)){
                keep_sprites_static_while_moving(0, 1);
                screen_offset[1] += 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, 0, 1);
                scroll_sprite(PLAYER_SPRITE_R_ID, 0, 1);
            }
        }
        if (player_direction == PLAYER_DIRECTION_UP) {
            if (0 < player[1] && 0 < screen_offset[1]){
                keep_sprites_static_while_moving(0, -1);
                screen_offset[1] -= 1;
            } else {
                scroll_sprite(PLAYER_SPRITE_L_ID, 0, -1);
                scroll_sprite(PLAYER_SPRITE_R_ID, 0, -1);
            }
        }

        if (player_direction == PLAYER_DIRECTION_LEFT) {
            if (0 < player[0] && 0 < screen_offset[0]){
                keep_sprites_static_while_moving(-1, 0);
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
                keep_sprites_static_while_moving(1, 0);
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
//    SHOW_WIN;
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

    //todo
    move_sprite(2, player[0] + 16, player[1]);
    set_sprite_prop(2, S_PALETTE);
    move_sprite(3, player[0] + 8 + 16, player[1]);
    set_sprite_prop(3, S_PALETTE);

    update_sprite_animation(2,  PLAYER_SPRITE_ANIM_L, PLAYER_DIRECTION_DOWN, 0);
    update_sprite_animation(3, PLAYER_SPRITE_ANIM_R, PLAYER_DIRECTION_DOWN, 0);
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
//    resetTileMap();
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
    while (1) {
        move_user();
    }
}
