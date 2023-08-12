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
#define PADDLE_METASPRITE paddle_metasprites[0]
#define BALL_METASPRITE ball_metasprites[0]

UINT8 joy, last_joy; // CHECKS FOR CURRENT AND PREVIOUS JOY INPUTS IN MAIN WHILE()

// const uint8_t black[16] = {0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xff, 0xff, 0xff, 0x00};

GameCharacter_t PADDLE;
GameCharacter_t BALL;

// set_sprite_data(0x24, 4, log_frog_tiles);
// set_sprite_data(0x28, 4, fly_tiles);
// set_bkg_data(0, 47, BKG_TILES);
// set_bkg_data(47, 1, FROG_LIVES); // TESTING FROG LIFE UPDATE
// set_bkg_data(0x80, 68, FONT);
// set_bkg_tiles(0, 0, 32, 32, BKG_MAP);
// set_bkg_tile_xy(4, 16, 0x90); // set furthest '0' on the righthand side of score on Stage 1 init only (is updated as soon as PADDLE gains points)

void load_sprites()
{
    // UINT8 hiwater = 0;
    set_sprite_data(0, paddle_TILE_COUNT, paddle_tiles); // load paddle tiles into vram
    // set_sprite_data(paddle_TILE_COUNT, ball_TILE_COUNT, ball_tiles); // load ball tiles into vram
    set_sprite_tile(1, 0x00); // set paddle sprite in OAM
    // hiwater += 3;                                                    // raise OAM hiwater for next OAM sprite (sizeof(paddle_tiles) >> 4)
    // set_sprite_tile(3, 0x02); // set ball sprite in OAM
}

void main()
{

    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    load_sprites();
    set_bkg_data(1, 1, black);     // load black tile;
    fill_bkg_rect(0, 0, 20, 6, 1); // draw a column of black tiles over the screen to visualize scroll

    // set some arbitrary scroll offsets for some lines

    DISABLE_VBL_TRANSFER;
    OBP0_REG = 0b11100100;
    OBP1_REG = 0b10011100;
    SPRITES_8x8; // MUST be 8x16 or 8x8. Can change in different scenes only
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    PADDLE.x = 68; // dead center for PADDLE (-12 offset from 80)
    PADDLE.y = 120;
    // BALL.x = PADDLE.x;
    // BALL.y = 120;

    while (1)
    {
        last_joy = joy;
        joy = joypad();

        if (joy & J_LEFT) // play music
        {
            PADDLE.x -= 1;
        }
        else if (joy & J_RIGHT) // play music
        {
            PADDLE.x += 1;
        }
        BALL.x = PADDLE.x;
        move_metasprite(PADDLE_METASPRITE, 0x00, 0, PADDLE.x, PADDLE.y);
        // move_sprite(3, BALL.x, BALL.y);

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