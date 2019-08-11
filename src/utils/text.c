//
// Created by Jean-Paul BELLA on 2019-07-21.
//
#include <stdio.h>

int ft_strlen(char *str){
    int size;

    size = 0;
    while (str[size] != '\0'){
        size++;
    }
    return size;
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

//int main(void){
//    char text[] = "THISISATEST\0";
//    int size = ft_strlen(text);
//
//    change_indic();
//    return (1);
//}