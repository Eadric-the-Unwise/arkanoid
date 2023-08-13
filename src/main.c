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

GameCharacter_t PADDLE;
GameCharacter_t BALL;

UBYTE ball_moving;
#define COLLISION_MAP_SIZE sizeof(collision_map)
unsigned char collision_map_ram[COLLISION_MAP_SIZE]; // ROM to WRAM copy of collision_map

void load_sprites()
{
    // UINT8 hiwater = 0;
    set_sprite_data(0, paddle_TILE_COUNT, paddle_tiles);             // load paddle tiles into vram
    set_sprite_data(paddle_TILE_COUNT, ball_TILE_COUNT, ball_tiles); // load ball tiles into vram
    set_sprite_tile(1, 0x00);                                        // set paddle sprite in OAM
    // hiwater += 3;                                                    // raise OAM hiwater for next OAM sprite (sizeof(paddle_tiles) >> 4)
    set_sprite_tile(3, 0x02); // set ball sprite in OAM
}

BYTE overlap(INT16 r1_y, INT16 r1_x, INT16 l1_y, INT16 l1_x, INT16 r2_y, INT16 r2_x, INT16 l2_y, INT16 l2_x)
{ // BYTE IS SAME AS BOOLEAN (ONLY SHORTER NAME)
    // Standard rectangle-to-rectangle collision check

    if (l1_x == r1_x || l1_y == r1_y || l2_x == r2_x || l2_y == r2_y)
    {
        // the line cannot have positive overlap
        return 0x00U;
    }
    if ((l1_x >= r2_x) || (l2_x >= r1_x))
    {
        return 0x00U;
    }
    if ((r1_y >= l2_y) || (r2_y >= l1_y))
    {
        return 0X00U;
    }

    return 0x01U;
}

void copy_collision_map() // copy ROM to WRAM
{
    // Copy data from ROM to RAM
    memcpy(collision_map_ram, collision_map, COLLISION_MAP_SIZE);
}

void collision_check(UINT8 ballx, UINT8 bally)
{
    UINT8 topy, leftx, tileindex;
    topy = bally / 8;                              // pixels to tiles y
    leftx = ballx / 8;                             // pixels to tiles x
    tileindex = collision_mapWidth * topy + ballx; // MULTIPLY THE WIDTH BY THE Y TILE TO FIND THE Y ROW. THEN ADD THE X TILE TO SHIFT THE COLUMN. FINDS THE TILE YOU'RE LOOKING FOR

    if (collision_map_ram[tileindex] == 0x01)
        ball_moving = FALSE;
}
void main()
{

    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    load_sprites();
    copy_collision_map();
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
    BALL.x = 0;
    BALL.y = PADDLE.y - 8;

    BALL.SpdY = 2;

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
        if (CHANGED_BUTTONS & J_A && !ball_moving)
        {
            ball_moving = TRUE;
        }
        if (ball_moving)
        {
            collision_check(BALL.x, BALL.y);
            BALL.y -= BALL.SpdY;
        }
        BALL.x = PADDLE.x;
        move_metasprite(PADDLE_METASPRITE, 0x00, 0, PADDLE.x, PADDLE.y);
        move_metasprite(BALL_METASPRITE, 0x02, 3, BALL.x, BALL.y);

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