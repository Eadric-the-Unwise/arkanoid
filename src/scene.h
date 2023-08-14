#include <gb/gb.h>
#include <gbdk/metasprites.h>
#include <stdio.h>

#include "../res/tiles/arkanoid_tiles.h"
#include "../res/tiles/ball.h"
#include "../res/tiles/black.h"
#include "../res/tiles/collision_map.h"
#include "../res/tiles/paddle.h"

#define CHANGED_BUTTONS (last_joy ^ joy)
#define CLICKED(x) ((joy & x) && (joy & x) != (last_joy & x))
#define RELEASED(x) (!(joy & x) && (joy & x) != (last_joy & x))
#define ISDOWN(x) (joy & (x))

// typedef enum {
//     game,
//     pause,
//     gameover
// } gamestates_e;

// typedef enum {
//     tick,
//     drain,
//     reload
// } timerstate_e;
// // typedef enum {
// //     ON_NOTHING,
// //     ON_TURTLE,
// //     ON_LOG3,
// //     ON_LOG2,
// //     ON_LOG1
// // } position_e;

// typedef enum {
//     UP,
//     DOWN,
//     LEFT,
//     RIGHT
// } direction_e;

typedef struct GameCharacter_t {
    // UBYTE spawn;
    // UBYTE flash;
    UINT8 x;
    UINT8 y;
    INT16 SpdX;  // ?
    INT8 SpdY;
    // position_e position;
    // direction_e direction;
} GameCharacter_t;
