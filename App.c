/*********************************************
* CEN118 - Algorithms and Programming Lab. 2
* MIDTERM HOMEWORK
* JUMP GAME
**********************************************
* Bilal Atakan Ünal - 2018556069
* Ahmet Özçelik - 2018556452
* Burcu Canbulat - 2017556008
**********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <time.h>

#define BLOCK_LIMIT 10
#define MAX_FRAME 6

typedef struct {
	float x;
	float y;
} PLAYER_COORDINATE;

typedef struct {
	int height;
	int width;
	PLAYER_COORDINATE COORDINATES;
} Player;

typedef struct {
	int height;
	int width;
	float x;
	int time;
	int point;
} Block;

typedef struct {
	int width;
	int height;
} CONFIG_DISPLAY;

typedef struct {
	int min;
	int max;
} BLOCKS_DELAY;

typedef struct {
	int max_width;
	int max_height;
	int min_width;
	int min_height;
	BLOCKS_DELAY BLOCKS_DELAY;
} CONFIG_BLOCKS;

typedef struct {
	CONFIG_DISPLAY DISPLAY;
	CONFIG_BLOCKS BLOCKS;
	int TIMER_SECOND;
	float BLOCK_SPEED;
	float JUMP_SPEED;
	int JUMP_LIMIT;
	int FASTEST_MAN_ALIVE;
} CONFIG;

void createBlock(CONFIG Con, Block blocks[], int* ptrRenderedBlock, int timerCount) {
	int h = Con.BLOCKS.min_height + rand() % (Con.BLOCKS.max_height - Con.BLOCKS.min_height);
	int w = Con.BLOCKS.min_width + rand() % (Con.BLOCKS.max_width - Con.BLOCKS.min_width);
	int time = timerCount + (Con.BLOCKS.BLOCKS_DELAY.min + rand() % (Con.BLOCKS.BLOCKS_DELAY.max - Con.BLOCKS.BLOCKS_DELAY.min));
	Block newBlock = { h,w, Con.DISPLAY.width + w, time, 0 };

	int indis = *ptrRenderedBlock % BLOCK_LIMIT;

	blocks[indis] = newBlock;

	*ptrRenderedBlock += 1;

}

int main() {

	/* CREATE RANDOM */
	srand(time(NULL));

	/* MAIN CCONFIGURATIONS */

	/* Game Configurations */
	CONFIG Con;
	CONFIG_DISPLAY DISPLAY = { 800, 400 }; Con.DISPLAY = DISPLAY;
	Con.TIMER_SECOND = 60; // Frame per Second
	Con.BLOCK_SPEED = 3.4;
	Con.JUMP_SPEED = 4.7;
	Con.JUMP_LIMIT = 30;
	BLOCKS_DELAY DELAY = { 60, 110 }; // Blocks created per random from first/FPS to second/FPS second
	CONFIG_BLOCKS BLOCKS = { 75, 50, 20, 10, DELAY };
	Con.BLOCKS = BLOCKS;
	Con.FASTEST_MAN_ALIVE = 1; // allow to stop jumping with key S or DOWN

	/* Player Configurations */
	Player Player;
	Player.height = 65;
	Player.width = 40;
	PLAYER_COORDINATE COORDINATES = { 110.0, DISPLAY.height - 120 - Player.height }; Player.COORDINATES = COORDINATES;
	
	/* END: MAIN CCONFIGURATIONS */

	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE* queue;
	ALLEGRO_BITMAP* bitmap;
	ALLEGRO_TIMER* timer;
	ALLEGRO_BITMAP* image[MAX_FRAME];
	ALLEGRO_FONT* font;
	ALLEGRO_FONT* font64;
	ALLEGRO_FONT* font15;

	al_init();
	display = al_create_display(Con.DISPLAY.width, Con.DISPLAY.height);
	timer = al_create_timer(1.0 / Con.TIMER_SECOND);
	queue = al_create_event_queue();

	al_init_primitives_addon();
	al_init_font_addon();
	al_init_ttf_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	Block blocks[BLOCK_LIMIT];

	/* STICKMAN CONFIGURATIONS */
	image[0] = al_load_bitmap("stickman/1.png");
	image[1] = al_load_bitmap("stickman/2.png");
	image[2] = al_load_bitmap("stickman/3.png");
	image[3] = al_load_bitmap("stickman/4.png");
	image[4] = al_load_bitmap("stickman/5.png");
	image[5] = al_load_bitmap("stickman/6.png");

	for (int i = 0; i < MAX_FRAME; i++)
		al_convert_mask_to_alpha(image[i], al_map_rgb(106, 76, 48));

	int curFrame = 0;
	int frameCount = 0;
	int frameDelay = 3;
	/* END: STICKMAN CONFIGURATIONS */

	/* FONT CONFIGURATIONS */
	font = al_load_ttf_font("roboto.ttf", 25, 0);
	font64 = al_load_ttf_font("roboto.ttf", 64, 0);
	font15 = al_load_ttf_font("roboto.ttf", 15, 0);
	/* END: FONT CONFIGURATIONS */

	int start = 0; // Game start
	int point = 0; // Score
	int best = 0; // Best Score
	int running = 1; // Loop Variable
	int renderedBlock = 0; // Rendered Blocks
	
	/* JUMPING EVENT */
	int jumping = 0;
	float jumping_moment = 0.0; 
	float jumping_moment_bottom = 0.0;
	/* END: JUMPING EVENT */

	int over_status = 0; // Game Over Status

	while (running) {
		int w = al_get_display_width(display);
		int h = al_get_display_height(display);

		al_clear_to_color(al_map_rgb(178, 34, 34));

		/* SCORE TITLES */
		
		char str_point[12];
		char str_best[12];
		sprintf(str_point, "%s %d", "SCORE: ",point);
		sprintf(str_best, "%s %d", "BEST: ",best);
		al_draw_text(font, al_map_rgb(255, 255, 255), w - 140, 20, 0, str_point);
		al_draw_text(font, al_map_rgb(255, 255, 255), 25, 20, 0, str_best);
		
		/* END: SCORE TITLES */

		/* GAME TITLES */

		if (over_status) {
			al_draw_text(font64, al_map_rgb(215, 215, 215), w / 2 - 170, h / 2 - 100, 0, "GAME OVER");
			al_draw_text(font15, al_map_rgb(215, 215, 215), w / 2 - 166, h / 2 - 25, 0, "PRESS \"ESCAPE\" TO EXIT | PRESS \"R\" TO RESTART");
		}
		if (!start) {
			al_draw_text(font64, al_map_rgb(215, 215, 215), w / 2 - 170, h / 2 - 100, 0, "JUMP GAME");
			al_draw_text(font15, al_map_rgb(215, 215, 215), w / 2 - 65, h / 2 - 25, 0, "PRESS ANY KEY TO START");
		}

		/* END TITLES */

		al_draw_filled_rectangle(0, h - 120, w, h, al_map_rgb(20, 20, 20)); // FLOOR

		/* DRAW BLOCKS */

		int for_limit = renderedBlock >= BLOCK_LIMIT ? BLOCK_LIMIT - 1 : renderedBlock;
		for (int i = 0; i <= for_limit && renderedBlock != 0; ++i) {
			al_draw_line(blocks[i].x, h - 120, blocks[i].x, h - 120 - (blocks[i].height), al_map_rgb(0, 0, 0), blocks[i].width);
		}

		/* END: DRAW BLOCKS */

		al_draw_bitmap(image[curFrame], Player.COORDINATES.x, Player.COORDINATES.y, 0); // DRAW PLAYER

		al_flip_display();

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);

		switch (event.type)
		{

		case ALLEGRO_EVENT_KEY_DOWN:

			/* SKILL EVENTS */

			if (!start)
				break;

			if ((event.keyboard.keycode == 23 || event.keyboard.keycode == 84) && !jumping) {
				// JUMPING EVENT
				jumping = 1;
			}

			if ((event.keyboard.keycode == 19 || event.keyboard.keycode == 85) && jumping && Con.FASTEST_MAN_ALIVE) {
				// FASTEST MAN ALIVE EVENT
				jumping = 0;
				jumping_moment = 0;
				jumping_moment_bottom = 0;
				Player.COORDINATES.y = DISPLAY.height - 120 - Player.height;
			}

			break;
		case ALLEGRO_EVENT_KEY_UP:
			
			/* GAME EVENTS */

			if (!start && event.keyboard.keycode != 59) {
				// GAME START EVENT
				start = 1;
				al_start_timer(timer);
				break;
			}

			if (event.keyboard.keycode == 59) {
				// GAME STOP EVENT
				running = 0;
			}

			if ((event.keyboard.keycode == 18) && over_status) {
				// GAME RESTART EVENT
				jumping = 0;
				jumping_moment = 0;
				jumping_moment_bottom = 0;
				Player.COORDINATES.y = DISPLAY.height - 120 - Player.height;
				over_status = 0;
				point = 0;
				for (int i = 0; i < BLOCK_LIMIT; i++) {
					Block emptyBlock = { 0,0, 0, 0, 1};
					blocks[i] = emptyBlock;
				}
				running = 1;
				al_start_timer(timer);
			}

			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			running = 0;
			break;
		case ALLEGRO_EVENT_TIMER:

			/* ANIMATION TIMER */
			if (++frameCount >= frameDelay) {
				if (++curFrame >= MAX_FRAME) 
					curFrame = 0;
				frameCount = 0;
			}

			/* DEATH */
			for (int i = 0; i <= for_limit && renderedBlock != 0; ++i) {
				float block_x = blocks[i].x - (blocks[i].width / 2);
				float player_x = Player.COORDINATES.x + Player.width;
				float block_y = h - 120 - (blocks[i].height);
				float player_y = Player.COORDINATES.y + Player.height;

				float block_x_low = block_x + blocks[i].width;
				float player_x_low = Player.COORDINATES.x;

				if (!blocks[i].point && player_x_low > block_x_low) {
					blocks[i].point = 1;
					point += 1;
				}

				if ((block_x <= player_x && block_y <= player_y) && player_x_low <= block_x_low) {
					over_status = 1;
					if (point > best) {
						best = point;
					}
					al_stop_timer(timer);

				}
			}

			/* CREATING BLOCKS */
			if (renderedBlock == 0 || blocks[renderedBlock >= BLOCK_LIMIT ? ((renderedBlock - 1) % BLOCK_LIMIT) : renderedBlock - 1].time <= event.timer.count) {
				createBlock(Con, blocks, &renderedBlock, event.timer.count);
			}

			/* MOVING BLOCKS */
			for (int i = for_limit; i >= 0; i--) {
				blocks[i].x -= Con.BLOCK_SPEED;
			}

			/* JUMP ANIMATION */
			if (jumping) {
				if (jumping_moment < Con.JUMP_LIMIT) {
					jumping_moment += 1;
					Player.COORDINATES.y = Player.COORDINATES.y - Con.JUMP_SPEED;

				}
				else if (jumping_moment_bottom < Con.JUMP_LIMIT) {
					Player.COORDINATES.y = Player.COORDINATES.y + Con.JUMP_SPEED;
					jumping_moment_bottom += 1;
				}
				else if (jumping_moment_bottom >= Con.JUMP_LIMIT) {
					jumping = 0;
					jumping_moment = 0;
					jumping_moment_bottom = 0;
				}
			}

			break;	
		}

	}

	for (int i = 0; i < MAX_FRAME; i++)
		al_destroy_bitmap(image[i]);
	al_destroy_display(display);
	al_uninstall_keyboard();

	return 0;
}