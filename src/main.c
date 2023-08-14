#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdio.h>
#include <string.h>  // memcpy

#include "scene.h"
//------------GOALS-------------//

#define PADDLE_METASPRITE paddle_metasprites[0]
#define BALL_METASPRITE ball_metasprites[0]
#define YMIN 120                                                    // ball Y when touching paddle
#define COLLISION_MAP_SIZE collision_mapWidth *collision_mapHeight  // calculate size of the collision map array
#define ballSpdY 2                                                  // speed of ball
#define PADDLE_INITX 68
#define PADDLE_INITY 120

extern const unsigned char collision_map[];  // ? do I need this here?

const unsigned char blank_tile[1] = {0x00};  // blank tile after brick breaks

UINT8 joy, last_joy;  // CHECKS FOR CURRENT AND PREVIOUS JOY INPUTS IN MAIN WHILE()

GameCharacter_t PADDLE;
GameCharacter_t BALL;

UBYTE ball_moving;

unsigned char collision_map_ram[COLLISION_MAP_SIZE];  // ROM to WRAM copy of collision_map

void load_sprites() {  // load sprites into vram
    // UINT8 hiwater = 0;
    set_sprite_data(0, paddle_TILE_COUNT, paddle_tiles);              // load paddle tiles into vram
    set_sprite_data(paddle_TILE_COUNT, ball_TILE_COUNT, ball_tiles);  // load ball tiles into vram
    set_sprite_tile(1, 0x00);                                         // set paddle sprite in OAM
    // hiwater += 3;                                                    // raise OAM hiwater for next OAM sprite (sizeof(paddle_tiles) >> 4)
    set_sprite_tile(3, 0x02);  // set ball sprite in OAM
}
void copy_collision_data()  // copy ROM to WRAM
{
    unsigned char *ram_pointer = collision_map_ram;  // point to the ROM collision map data
    memcpy(ram_pointer, collision_map, COLLISION_MAP_SIZE);
}

void collision_check(UINT8 ballx, UINT8 bally) {    // check for ball collision with bricks
    UINT8 topy, leftx;                              // 0-255
    UINT16 tileindex;                               // 16 bit integer
    topy = bally / 8;                               // pixels to tiles y
    leftx = ballx / 8;                              // pixels to tiles x
    tileindex = collision_mapWidth * topy + leftx;  // MULTIPLY THE WIDTH BY THE Y TILE TO FIND THE Y ROW. THEN ADD THE X TILE TO SHIFT THE COLUMN. FINDS THE TILE YOU'RE LOOKING FOR

    if (collision_map_ram[tileindex] == 0x01) {  // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
        // ball_moving = FALSE;
        BALL.SpdY = -BALL.SpdY;                        // reverse ball speed
        set_bkg_tiles(leftx, topy, 1, 1, blank_tile);  // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x, y, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex] = 0x00;           // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }
}

BYTE overlap(INT16 r1_y, INT16 r1_x, INT16 l1_y, INT16 l1_x, INT16 r2_y, INT16 r2_x, INT16 l2_y, INT16 l2_x) {  // BYTE IS SAME AS BOOLEAN (ONLY SHORTER NAME)
    // Standard rectangle-to-rectangle collision check

    if (l1_x == r1_x || l1_y == r1_y || l2_x == r2_x || l2_y == r2_y) {
        // the line cannot have positive overlap
        return 0x00U;
    }
    if ((l1_x >= r2_x) || (l2_x >= r1_x)) {
        return 0x00U;
    }
    if ((r1_y >= l2_y) || (r2_y >= l1_y)) {
        return 0X00U;
    }

    return 0x01U;
}

void main() {
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    load_sprites();                 // load all sprite tiles into VRAM
    copy_collision_data();          // copy collision map array from ROM to RAM
    set_bkg_data(1, 1, black);      // load black tile;
    fill_bkg_rect(0, 0, 20, 6, 1);  // draw a column of black tiles over the screen to visualize scroll

    // set some arbitrary scroll offsets for some lines

    DISABLE_VBL_TRANSFER;
    OBP0_REG = 0b11100100;  // color pallette
    OBP1_REG = 0b10011100;  // color pallette
    SPRITES_8x8;            // MUST be 8x16 or 8x8. Can change in different scenes only
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    PADDLE.x = PADDLE_INITX;  // dead center for PADDLE (-12 offset from 80)
    PADDLE.y = PADDLE_INITY;  // 120
    BALL.y = PADDLE.y - 8;

    BALL.SpdY = ballSpdY;  // 2

    while (1) {
        last_joy = joy;
        joy = joypad();

        if (joy & J_LEFT) {
            PADDLE.x -= 1;  // MOVE PADDLE LEFT
        } else if (joy & J_RIGHT) {
            PADDLE.x += 1;  // MOVE PADDLE RIGHT
        }
        if (CHANGED_BUTTONS & J_A && !ball_moving) {
            ball_moving = TRUE;  // ball is moving, not in spawn position
        }
        if (ball_moving) {
            collision_check(BALL.x, BALL.y);                                                              // check for brick collisions
            BALL.y -= BALL.SpdY;                                                                          // move ball vertically
            if (BALL.y + ball_HEIGHT >= YMIN && BALL.x >= PADDLE.x && BALL.x <= PADDLE.x + paddle_WIDTH)  // check for paddle collision
                BALL.SpdY = -BALL.SpdY;
        } else {                // spawn
            BALL.x = PADDLE.x;  // ball spawns on paddle, follows paddle until player launches ball by pressing A
        }
        move_metasprite(PADDLE_METASPRITE, 0x00, 0, PADDLE.x, PADDLE.y);  // update position on screen
        move_metasprite(BALL_METASPRITE, 0x02, 3, BALL.x, BALL.y);        // update position on screen

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