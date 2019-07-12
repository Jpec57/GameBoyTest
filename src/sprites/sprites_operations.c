//
// Created by Jean-Paul BELLA on 2019-07-11.
//

void flip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) | S_FLIPX);
}

void unflip_sprite_horiz(UINT8 sprite_id) {
    set_sprite_prop(sprite_id, get_sprite_prop(sprite_id) & ~S_FLIPX);
}

// Met à jour les tuiles d'un sprite pour l'animer.
//
// sprite_id: l'id ("nb") du sprite à modifier
// anim:      pointeur vers les données de l'animation
// direction: direction de l'animation (= offset de la sous-animation)
// frame:     la nouvelle frame de l'animation qui doit être affichée
//
// Retourne la prochaine frame de l'animation.
UINT8 update_sprite_animation(UINT8 sprite_id, UINT8 *anim, UINT8 direction, UINT8 frame) {
    UINT8 len = anim[direction];
    UINT8 flip = anim[direction + 1];
    UINT8 tile_id = anim[direction + 2 + frame];

    if (flip) {
        flip_sprite_horiz(sprite_id);
    } else {
        unflip_sprite_horiz(sprite_id);
    }

    set_sprite_tile(sprite_id, tile_id);

    return (frame + 1) % len;
}
