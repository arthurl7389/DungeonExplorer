#include "StartScreen.h"

#include <sextant/sprite.h>
#include <Applications/Draw/Draw.h>
#include <Applications/Draw/sprite_tile.h>
#include <sextant/interruptions/handler/handler_tic.h>

static bool any_key_pressed(Clavier &c)
{ // simple function to check if any key is pressed
    for (int sc = 0; sc < 126; sc++) {
        if (c.is_pressed(sc))
            return true;
    }
    return false;
}

void start_screen(EcranBochs &vga, Clavier &c)
{
    bool blink = false; // blinking "PRESS ANY KEY" flag

    while (true)
    {
        vga.clear(0);

        // title Dungeon Explorer
        draw_text(vga, "DUNGEON", 152, 60, 3, 15);  // 640/2 - (7*16)*3/2 = 152
        draw_text(vga, "EXPLORER", 128, 126, 3, 15);  // 640/2 - (8*16)*3/2 = 128

        // Press Any Key
        if (blink)
        {
            draw_text(vga, "PRESS ANY KEY", 216, 200, 1, 50);  // 640/2 - (13*16)*1/2 = 216
        }

        draw_tile(vga, sprite_wall, 0, 340, 640, 60, SPRITE_WALL_W, SPRITE_WALL_H, 5);

        draw_sprite_scaled(vga, sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, 200, 220, 2);
        draw_sprite_scaled(vga, sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, 120, 220, 2);
        draw_sprite_scaled(vga, sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, 340, 230, 2, 15, true);

        vga.swapBuffer();

        if (any_key_pressed(c))
            break; // exit on any key press

        if ((compt / 500) % 2 == 0) // toggle blink every 500 tics
            blink = true;
        else
            blink = false;
    }

    vga.clear(0); // clear screen before exiting and swapping buffer
    vga.swapBuffer();
}
