#include <gb/gb.h>
#include <stdio.h>
#include "../includes/main.h"

void init(){
    DISPLAY_ON;		// Turn on the display
    set_bkg_data(0, 47, alpha);		// Load 47 tiles into background memory
    set_bkg_tiles(0, 6, 10, 2, helloWorld);
    //    set_bkg_data(0, 1, TILESET);
    //    set_bkg_tiles(0, 0, 8, 16, TILEMAP);
}

void updateSwitches() {
    HIDE_WIN;
    SHOW_SPRITES;
    SHOW_BKG;
}

void checkInput(){

}

void main() {
    UINT8 keys;
    UINT8 prev_keys = 0;
    init();
//    printf("JpecProgramming\n");
//    printf("Press Start\n");
//    waitpad(J_START);

    while (1) {
        set_bkg_data(0, 47, alpha);		// Load 47 tiles into background memory
        set_bkg_tiles(0, 6, 10, 2, helloWorld);

        updateSwitches();
        keys = joypad();
        if ((keys & J_A) && !(prev_keys & J_A)) {
            printf("You pressed A\n");
        }
        if ((keys & J_B) && !(prev_keys & J_B)){
            printf("You pressed B\n");
        }
        if (!(keys & J_A) && (prev_keys & J_A)){
            printf("A release\n");
        }
        if (!(keys & J_B) && (prev_keys & J_B)){
            printf("B Released\n");
        }
        prev_keys = keys;
        //Attend que l'écran soit raffraichi
        wait_vbl_done();
    }
}
