#ifndef SPRITE_H
#define SPRITE_H

// Généré par png_to_c_with_palette.py à partir de 'pixel-32x32.png'
#define SPRITE_WIDTH  64
#define SPRITE_HEIGHT 64

extern unsigned char palette_vga[256][3];
extern unsigned char sprite_data_player1[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_player2[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_player1_vertically[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_player1_running[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_player2_vertically[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_player2_running[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_skeleton[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char sprite_data_skeleton_running[SPRITE_WIDTH*SPRITE_HEIGHT];
extern unsigned char gameover[289*40];
extern unsigned char victoire[194*40];
extern unsigned char commands[185*320];
extern unsigned char touches1[217*43];
extern unsigned char touches2[438*78];

#endif