//
// Created by Jean-Paul BELLA on 2019-07-21.
//
#include "../../includes/main.h"

int ft_strlen(char *str){
    int size;

    size = 0;
    while (str[size] != '\0'){
        size++;
    }
    return size;
}

void resetTileMap(){
//    int i;
//    int j;
//
//    i = 0;
//    j = 0;
//    while (j < WINDOW_TILEMAP_HEIGHT){
//        i = 0;
//        while (i < WINDOW_TILEMAP_WIDTH){
//            WINDOW_TILEMAP[i + j * WINDOW_TILEMAP_WIDTH] = 47;
//            i++;
//        }
//        j++;
//    }
//    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, WINDOW_TILEMAP);
    set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, BLANK_WINDOW);
    move_win(7, 128);
    wait_vbl_done();
}

void convert_text(char *text){
    int size = ft_strlen(text);
    int i;

    i = 0;
    while (i < size){
//        if (65 < text[i] && text[i] < 90){
        text[i] = text[i] - 48;
//        }
        i++;
    }
}

//void    *ft_memcpy(void *dest, const void *src, size_t n)
//{
//    unsigned char			*dst;
//    const unsigned char		*s;
//
//    dst = dest;
//    s = src;
//    while (n--)
//        *dst++ = *s++;
//    return (dest);
//}

//int write_on_screen(char *text){
//    int cursor;
//    int size;
//    int i;
//    int j;
//    UINT8 window_text[WINDOW_TILEMAP_HEIGHT * WINDOW_TILEMAP_WIDTH];
//
//    convert_text(text);
//    size = ft_strlen(text);
//
//    cursor = 0;
//    SHOW_WIN;
//    waitpadup();
////    ft_memcpy(window_text, BLANK_WINDOW, WINDOW_TILEMAP_HEIGHT * WINDOW_TILEMAP_WIDTH);
//    while (cursor < size){
//
//        j = 0;
//        while (j < WINDOW_TILEMAP_HEIGHT){
//            i = 0;
//            while (i < WINDOW_TILEMAP_WIDTH){
//                window_text[i + j * WINDOW_TILEMAP_WIDTH] = (cursor < size) ? text[cursor] : 47;
//                i++;
//                cursor++;
//            }
//            j++;
//        }
//        set_win_tiles(0, 0, WINDOW_TILEMAP_WIDTH, WINDOW_TILEMAP_HEIGHT, window_text);
//        move_win(7, 128);
//        wait_vbl_done();
//        waitpad(J_START);
//        waitpadup();
//    }
//    HIDE_WIN;
//    resetTileMap();
//    return (1);
//}
