#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdio.h>
#include <string.h> // memcpy

#include "scene.h"
//------------GOALS-------------//

#define PADDLE_METASPRITE paddle_metasprites[0]
#define BALL_METASPRITE ball_metasprites[0]
#define PADDLEY 120                                                // ball Y when touching paddle
#define YMIN 0                                                     // top of stage
#define YMAX 144                                                   // bottom of stage
#define XMIN 0                                                     // left edge of stage
#define XMAX (160 - ball_WIDTH)                                    // right edge of stage
#define COLLISION_MAP_SIZE collision_mapWidth *collision_mapHeight // calculate size of the collision map array
#define BALLSPDY 2                                                 // speed of ball
#define PADDLESPDX 1
#define PADDLE_INITX 68
#define PADDLE_INITY 120
#define PADDLE_MINX 0
#define PADDLE_MAXX (160 - paddle_WIDTH)
#define BALL_INITY (PADDLE_INITY - ball_HEIGHT)

extern const unsigned char collision_map[]; // ? do I need this here?

const unsigned char blank_tile[1] = {0x00}; // blank tile after brick breaks

UINT8 joy, last_joy; // CHECKS FOR CURRENT AND PREVIOUS JOY INPUTS IN MAIN WHILE()

GameCharacter_t PADDLE;
GameCharacter_t BALL;

UBYTE ball_moving;

unsigned char collision_map_ram[COLLISION_MAP_SIZE]; // ROM to WRAM copy of collision_map

void load_sprites()
{ // load sprites into vram
    // UINT8 hiwater = 0;
    set_sprite_data(0, paddle_TILE_COUNT, paddle_tiles);             // load paddle tiles into vram
    set_sprite_data(paddle_TILE_COUNT, ball_TILE_COUNT, ball_tiles); // load ball tiles into vram
    set_sprite_tile(1, 0x00);                                        // set paddle sprite in OAM
    // hiwater += 3;                                                    // raise OAM hiwater for next OAM sprite (sizeof(paddle_tiles) >> 4)
    set_sprite_tile(3, 0x02); // set ball sprite in OAM
}
void copy_collision_data() // copy ROM to WRAM
{
    unsigned char *ram_pointer = collision_map_ram; // point to the ROM collision map data
    memcpy(ram_pointer, collision_map, COLLISION_MAP_SIZE);
}

// void collision_check(UINT8 ballx, UINT8 bally) {  // check for ball collision with bricks
//     UINT8 x_tile, y_tile, x_offset, y_offset;     // 0-255
//     UINT16 tileindex;                             // 16 bit integer

//     // // calculate where the ball is moving, and which side of the ball to check for brick collisions
//     if (BALL.SpdX > 0)
//         x_offset = ball_WIDTH;  // right side of ball
//     else
//         x_offset = 0;  // left side of ball
//     if (BALL.SpdY > 0)
//         y_offset = ball_HEIGHT;  // bottom side of ball
//     else
//         y_offset = 0;  // top side of ball

//     x_tile = (ballx + x_offset) / 8;                   // pixels to tiles x
//     y_tile = (bally + y_offset) / 8;                   // pixels to tiles y
//     tileindex = collision_mapWidth * y_tile + x_tile;  // MULTIPLY THE WIDTH BY THE Y TILE TO FIND THE Y ROW. THEN ADD THE X TILE TO SHIFT THE COLUMN. FINDS THE TILE YOU'RE LOOKING FOR

//     if (collision_map_ram[tileindex] == 0x01) {  // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
//         // ball_moving = FALSE;
//         BALL.SpdY = -BALL.SpdY;                           // reverse ball speed
//         set_bkg_tiles(x_tile, y_tile, 1, 1, blank_tile);  // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
//         collision_map_ram[tileindex] = 0x00;              // UPDATE BRICK TO BECOME BLANK IN WRAM //
//     }
// }

void collision_check(UINT8 ballx, UINT8 bally)
{                                                                         // check for ball collision with bricks
    UINT8 TL_x_tile, TR_x_tile, TL_y_tile, BL_y_tile, x_offset, y_offset; // 0-255
    UINT16 tileindex_TL, tileindex_TR, tileindex_BL, tileindex_BR;        // 16 bit integer

    x_offset = ball_WIDTH;  // right side of ball
    y_offset = ball_HEIGHT; // bottom side of ball

    TL_x_tile = (ballx) / 8;            // pixels to tiles x
    TR_x_tile = (ballx + x_offset) / 8; // pixels to tiles x
    TL_y_tile = (bally) / 8;            // pixels to tiles y
    BL_y_tile = (bally + y_offset) / 8;

    tileindex_TL = collision_mapWidth * TL_y_tile + TL_x_tile; // MULTIPLY THE WIDTH BY THE Y TILE TO FIND THE Y ROW. THEN ADD THE X TILE TO SHIFT THE COLUMN. FINDS THE TILE YOU'RE LOOKING FOR
    tileindex_TR = collision_mapWidth * TL_y_tile + TR_x_tile;
    tileindex_BL = collision_mapWidth * BL_y_tile + TL_x_tile;
    tileindex_BR = collision_mapWidth * BL_y_tile + TR_x_tile;

    if (collision_map_ram[tileindex_TL] == 0x01 && collision_map_ram[tileindex_TR] == 0x01)
    {
        BALL.SpdY = -BALL.SpdY;                                // reverse ball speed
        set_bkg_tiles(TL_x_tile, TL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_TL] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
        set_bkg_tiles(TR_x_tile, TL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_TR] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }

    else if (collision_map_ram[tileindex_TL] == 0x01)
    { // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
        // ball_moving = FALSE;
        BALL.SpdY = -BALL.SpdY;                                // reverse ball speed
        set_bkg_tiles(TL_x_tile, TL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_TL] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }
    else if (collision_map_ram[tileindex_TR] == 0x01)
    { // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
        // ball_moving = FALSE;
        BALL.SpdY = -BALL.SpdY;                                // reverse ball speed
        set_bkg_tiles(TR_x_tile, TL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_TR] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }
    if (collision_map_ram[tileindex_BL] == 0x01)
    { // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
        // ball_moving = FALSE;
        BALL.SpdY = -BALL.SpdY;                                // reverse ball speed
        set_bkg_tiles(TL_x_tile, BL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_BL] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }
    if (collision_map_ram[tileindex_BR] == 0x01)
    { // if ball touches 0x01 brick, update the WRAM array, then update the bkg_tile visually
        // ball_moving = FALSE;
        BALL.SpdY = -BALL.SpdY;                                // reverse ball speed
        set_bkg_tiles(TR_x_tile, BL_y_tile, 1, 1, blank_tile); // UPDATE BRICK TO BECOME BLANK VISUALLY ON SCREEN // x tile, y tile, tile width, tile height, unsigned char tile[]{}
        collision_map_ram[tileindex_BR] = 0x00;                // UPDATE BRICK TO BECOME BLANK IN WRAM //
    }
}

void ball_reset()
{
    BALL.SpdY = BALL.SpdX = 0;
    BALL.y = BALL_INITY;
    BALL.x = PADDLE.x;
    ball_moving = FALSE;
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

void main()
{
    NR52_REG = 0x80;
    NR51_REG = 0xFF;
    NR50_REG = 0x77;

    load_sprites();            // load all sprite tiles into VRAM
    copy_collision_data();     // copy collision map array from ROM to RAM
    set_bkg_data(1, 1, black); // load black tile;
    set_bkg_tiles(0, 0, bkg_mapWidth, bkg_mapHeight, bkg_map);

    // set some arbitrary scroll offsets for some lines

    DISABLE_VBL_TRANSFER;
    OBP0_REG = 0b11100100; // color pallette
    OBP1_REG = 0b10011100; // color pallette
    SPRITES_8x8;           // MUST be 8x16 or 8x8. Can change in different scenes only
    SHOW_BKG;
    SHOW_SPRITES;
    DISPLAY_ON;

    PADDLE.x = PADDLE_INITX; // dead center for PADDLE (-12 offset from 80)
    PADDLE.y = PADDLE_INITY; // 120
    BALL.y = BALL_INITY;
    BALL.x = PADDLE.x;

    while (1)
    {
        last_joy = joy;
        joy = joypad();

        if (joy & J_LEFT)
        {
            PADDLE.SpdX = -PADDLESPDX;
            PADDLE.x += PADDLE.SpdX;    // move paddle left
            if (PADDLE.x < PADDLE_MINX) // check left edges for paddle
                PADDLE.x = PADDLE_MINX;
        }
        else if (joy & J_RIGHT)
        {
            PADDLE.SpdX = PADDLESPDX;
            PADDLE.x += PADDLE.SpdX;     // move paddle right
            if (PADDLE.x >= PADDLE_MAXX) // check right edges for paddle
                PADDLE.x = PADDLE_MAXX;
        }
        else
            PADDLE.SpdX = 0; // not moving paddle

        if (CHANGED_BUTTONS & J_A && !ball_moving)
        {
            ball_moving = TRUE;      // ball is moving, not in spawn position
            BALL.SpdY = -BALLSPDY;   // launch speed
            BALL.SpdX = PADDLE.SpdX; // launch speed, if paddle is moving
        }
        if (ball_moving)
        {
            if (BALL.SpdY > 0 && BALL.y + ball_HEIGHT == PADDLEY && (BALL.x + ball_WIDTH) >= PADDLE.x && BALL.x <= PADDLE.x + paddle_WIDTH) // check for paddle collision, only when it is moving downward toward paddle
                BALL.SpdY = -BALL.SpdY;                                                                                                     // reverse Y speed
            if (BALL.y >= YMAX)                                                                                                             // if ball reaches bottom of the stage
                ball_reset();
            else if (BALL.y <= YMIN)
                BALL.SpdY = -BALL.SpdY; // reset ball to spawn position on paddle
            if (BALL.x >= XMAX)
                BALL.SpdX = -BALL.SpdX;
            else if (BALL.x <= XMIN)
                BALL.SpdX = -BALL.SpdX;

            collision_check(BALL.x, BALL.y); // check for brick collisions
        }
        else
        {                      // ball is on paddle, follow paddle
            BALL.x = PADDLE.x; // ball spawns on paddle, follows paddle until player launches ball by pressing A
        }

        BALL.y += BALL.SpdY;                                             // move ball vertically
        BALL.x += BALL.SpdX;                                             // move ball horizontally
        move_metasprite(PADDLE_METASPRITE, 0x00, 0, PADDLE.x, PADDLE.y); // update position on screen
        move_metasprite(BALL_METASPRITE, 0x02, 3, BALL.x, BALL.y);       // update position on screen

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