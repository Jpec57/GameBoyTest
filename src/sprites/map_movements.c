void keep_sprites_static(int bkg_dir_x, int bkg_dir_y){
    int     i;

    i = 2;
    scroll_bkg(bkg_dir_x, bkg_dir_y);
    while (i <= MAX_SPRITE_NUM){
        scroll_sprite(i, bkg_dir_x * (-1), bkg_dir_y * (-1));
        i++;
    }
}

//int random_walk(int sprite_num, int sprite_size){
//    return sprite_num + sprite_size;
//}
