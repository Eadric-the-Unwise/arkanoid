#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdio.h>
// #include <string.h>
// #include <rand.h>
// #include "../sound/hUGEDriver.h"
// #include "../sound/sound.h"
// #include "../sound/musicmanager.h"
#include "scene.h"
//------------GOALS-------------//

// extern const hUGESong_t sample_song;

UINT8 joy, last_joy; // CHECKS FOR CURRENT AND PREVIOUS JOY INPUTS IN MAIN WHILE()

const uint8_t black[16] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00};

GameCharacter_t PLAYER;

// set_sprite_data(0x24, 4, log_frog_tiles);
// set_sprite_data(0x28, 4, fly_tiles);
// set_bkg_data(0, 47, BKG_TILES);
// set_bkg_data(47, 1, FROG_LIVES); // TESTING FROG LIFE UPDATE
// set_bkg_data(0x80, 68, FONT);
// set_bkg_tiles(0, 0, 32, 32, BKG_MAP);
// set_bkg_tile_xy(4, 16, 0x90); // set furthest '0' on the righthand side of score on Stage 1 init only (is updated as soon as player gains points)

void main()
{

    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    set_sprite_data(0, 2, paddle_tiles);
    set_sprite_data(2, 2, ball_tiles);
    set_sprite_tile(1, 0x01); // set paddle sprite in OAM
    set_sprite_tile(2, 0x02); // set ball sprite in OAM
    move_sprite(0x02, 72, 120);
    set_bkg_data(1, 1, black);     // load black tile;
    fill_bkg_rect(0, 0, 20, 6, 1); // draw a column of black tiles over the screen to visualize scroll

    // set some arbitrary scroll offsets for some lines

    DISABLE_VBL_TRANSFER;
    OBP0_REG = 0b11100100;
    OBP1_REG = 0b10011100;
    SPRITES_8x16; // MUST be 8x16 or 8x8. Can change in different scenes only
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    PLAYER.x = 72;
    PLAYER.y = 128;

    move_metasprite(paddle_metasprites[0], 0, 0, PLAYER.x, PLAYER.y);

    while (1)
    {
        last_joy = joy;
        joy = joypad();

        if (joy & J_LEFT) // play music
        {
            PLAYER.x -= 1;
        }
        else if (joy & J_RIGHT) // play music
        {
            PLAYER.x += 1;
        }
        move_metasprite(paddle_metasprites[0], 0, 0, PLAYER.x, PLAYER.y);
        wait_vbl_done();
        refresh_OAM();
    }
}

// switch (joy)
// {
// case J_LEFT:
//     if (CHANGED_BUTTONS & J_LEFT)
//     {
//     }
//     break;
// case J_RIGHT:
//     if (CHANGED_BUTTONS & J_RIGHT)
//     {
//         // LYs[ROW1].scroll += 1;
//     }
//     break;
// case J_UP:
//     if (CHANGED_BUTTONS & J_UP)
//     {
//     }
//     break;
// case J_DOWN:

//     {
//     }
//     break;
// }