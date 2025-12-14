#ifndef SPRITE_H
#define SPRITE_H

#define SPRITE_WIDTH  64
#define SPRITE_HEIGHT 64

extern unsigned char palette_vga[256][3];
extern unsigned char sprite_data_player1[SPRITE_WIDTH*SPRITE_HEIGHT]; // basic sprite data for player 1
extern unsigned char sprite_data_player2[SPRITE_WIDTH*SPRITE_HEIGHT]; // basic sprite data for player 2
extern unsigned char sprite_data_player1_vertically[SPRITE_WIDTH*SPRITE_HEIGHT]; // sprite data for player 1 when moving vertically
extern unsigned char sprite_data_player1_running[SPRITE_WIDTH*SPRITE_HEIGHT]; // sprite data for player 1 when moving horizontally
extern unsigned char sprite_data_player2_vertically[SPRITE_WIDTH*SPRITE_HEIGHT]; // sprite data for player 2 when moving vertically
extern unsigned char sprite_data_player2_running[SPRITE_WIDTH*SPRITE_HEIGHT]; // sprite data for player 2 when moving horizontally
extern unsigned char sprite_data_skeleton[SPRITE_WIDTH*SPRITE_HEIGHT]; // basic sprite data for skeleton mob
extern unsigned char sprite_data_skeleton_running[SPRITE_WIDTH*SPRITE_HEIGHT]; // sprite data for skeleton mob when moving
extern unsigned char gameover[289*40]; // sprite data for game over screen
extern unsigned char victoire[194*40]; // sprite data for victory screen
extern unsigned char commands[185*320]; // sprite data for in-game commands screen
extern unsigned char touches1[217*43]; 
extern unsigned char touches2[438*78];

#endif