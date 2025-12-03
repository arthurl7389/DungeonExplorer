#include <hal/multiboot.h>
#include <drivers/Ecran.h>
#include <drivers/PortSerie.h>

// TP2
#include <sextant/interruptions/idt.h>
#include <sextant/interruptions/irq.h>
#include <sextant/interruptions/handler/handler_tic.h>
#include <sextant/interruptions/handler/handler_clavier.h>
#include <drivers/timer.h>
#include <drivers/Clavier.h>
// TP3
#include <sextant/memoire/memoire.h>

// TP4
#include <sextant/ordonnancements/cpu_context.h>
#include <sextant/ordonnancements/preemptif/thread.h>
#include <sextant/types.h>


#include <sextant/Synchronisation/Spinlock/Spinlock.h>

#include <hal/pci.h>
#include <drivers/vga.h>
#include <drivers/EcranBochs.h>

#include <sextant/sprite.h>

#include <Applications/DungeonExplorer/DungeonExplorer.h>


extern char __e_kernel,__b_kernel, __b_data, __e_data,  __b_stack, __e_load ;
int i;

extern vaddr_t bootstrap_stack_bottom; //Adresse de début de la pile d'exécution
extern size_t bootstrap_stack_size;//Taille de la pile d'exécution

void demo_vga() {
	set_vga_mode13(); // set VGA mode
	set_palette_vga(palette_vga); // set to given palette

	ui16_t offset = 0;
	while(1) {
		clear_vga_screen(0); // put the color 0 on each pixel
		plot_square(offset, 50, 25, 4); // plot a square of 25 width at 50,50 of color 4
		draw_sprite(sprite_data_player1, 64, 64, 100,100); // draw the 64x64 sprite at 100,100
		offset = (offset + 1) % 640;
	}
}

void demo_bochs_8() {
    ui16_t WIDTH = 640, HEIGHT = 400;
    EcranBochs vga(WIDTH, HEIGHT, VBE_MODE::_8);
    const char SPEED = 1;
    Clavier c;

	AZERTY::scancodes controls[2][4] = {
		{AZERTY::K_Z, AZERTY::K_Q, AZERTY::K_S, AZERTY::K_D}, // Player 1
		{AZERTY::K_O, AZERTY::K_K, AZERTY::K_L, AZERTY::K_M}  // Player 2
	};

    vga.init();
    vga.clear(0);

    // only usefull in 4 or 8 bits modes
    vga.set_palette(palette_vga);
    vga.plot_palette(0, 0, 25);

    int x = 0, y = 0;
	int x2 = 100, y2 = 0;

    while (true) {

        if (c.is_pressed(controls[0][0])) {
            y -= SPEED;
            if (y < 0) y += HEIGHT;
        }
        if (c.is_pressed(AZERTY::K_Q)) {
            x -= SPEED;
            if (x < 0) x += WIDTH;
        }
        if (c.is_pressed(AZERTY::K_S)) {
            y = (y + SPEED) % HEIGHT;
        }
        if (c.is_pressed(AZERTY::K_D)) {
            x = (x + SPEED) % WIDTH;
        }

		// and player 2 
		if (c.is_pressed(AZERTY::K_O)) {
            y2 -= SPEED;
            if (y2 < 0) y2 += HEIGHT;
        }
        if (c.is_pressed(AZERTY::K_K)) {
            x2 -= SPEED;
            if (x2 < 0) x2 += WIDTH;
        }
        if (c.is_pressed(AZERTY::K_L)) {
            y2 = (y2 + SPEED) % HEIGHT;
        }
        if (c.is_pressed(AZERTY::K_M)) {
            x2 = (x2 + SPEED) % WIDTH;
        }
        
        vga.clear(1);
        vga.plot_sprite(sprite_data_player1, SPRITE_WIDTH, SPRITE_HEIGHT, x, y);
		vga.plot_sprite(sprite_data_player2, SPRITE_WIDTH, SPRITE_HEIGHT, x2, y2);
		vga.plot_sprite(sprite_data_skeleton, SPRITE_WIDTH, SPRITE_HEIGHT, (x + x2)/2, (y + y2)/2);
        vga.swapBuffer(); // call this after you finish drawing your frame to display it, it avoids screen tearing
    }
}

void demo_bochs_32() {
	EcranBochs vga(640, 400, VBE_MODE::_32);

	vga.init();
	
	ui8_t offset = 0;
	while(true) {
		
		for (int y = 0; y < vga.getHeight(); y++) {
			for (int x = 0; x < vga.getWidth(); x++) {
				vga.paint(x, y, 
					(~x << y%3) + offset & y, 
					~offset * (x & ~y), 
					offset | (~y < 2 - x % 16));
			}
		}
		++offset;
	}
}

extern "C" void Sextant_main(unsigned long magic, unsigned long addr){
	Ecran ecran;
	Clavier clavier;
	Timer timer;
	DungeonExplorer game;

	idt_setup();
	irq_setup();
	//Initialisation de la frequence de l'horloge

	timer.i8254_set_frequency(1000);
	irq_set_routine(IRQ_TIMER, ticTac);

	asm volatile("sti\n");//Autorise les interruptions

	irq_set_routine(IRQ_KEYBOARD, handler_clavier);

	multiboot_info_t* mbi;
	mbi = (multiboot_info_t*)addr;

	mem_setup(& __e_kernel,(mbi->mem_upper<<10) + (1<<20),&ecran);

	ecran.effacerEcran(NOIR);

	thread_subsystem_setup(bootstrap_stack_bottom,bootstrap_stack_size);
	sched_subsystem_setup();

	irq_set_routine(IRQ_TIMER, sched_clk);
	
	// initialize pci bus to detect GPU address
	checkBus(0);

	//demo_vga();
	//demo_bochs_8();
	//demo_bochs_32();

	// L'écran qu'on va vraiment utiliser:
	ui16_t WIDTH = 640, HEIGHT = 400;
    EcranBochs vga(WIDTH, HEIGHT, VBE_MODE::_8);
	vga.init();
    vga.clear(0);
    // only usefull in 4 or 8 bits modes
    vga.set_palette(palette_vga);
    vga.plot_palette(0, 0, 25);

	// Brouillon : 
	//char tab[1024];
	//Cons conso(&sem1,tab,&ecran);
	//Prod produ(&sem1,tab,&ecran);
	//conso.start();
	//produ.start();
	//ok done

	//on met l'écran boch dans le main parce qu'on veut qu'un écran et on fait tout avec.
	game.init(&vga,&clavier,WIDTH,HEIGHT);
	game.start();
}
