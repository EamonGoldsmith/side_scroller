#include <stdio.h>
#include <SDL2/SDL.h>

#define WIDTH 640
#define HEIGHT 480

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Surface *screen;

int loop;

SDL_Texture *loadMedia(const char path[]);

int main(int argc, char* argv[])
{
	struct sprite {
		int current_frame;
		float x, y, vx, vy, ax, ay;
		int width, height;
		int animation_direction;
		int animation_state;
		int tile_width, tile_height;
		SDL_Texture *texture;
	};

	//different animation states
	enum anim_type {
		WALKING,
		RUNNING,
		IDLE
	};
		
	//direction of the current animation
	enum anim_direction {
		FORWARD,
		RIGHT,
		BACK,
		LEFT
	};

	//initialise SDL components
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

	window = SDL_CreateWindow("QUI",
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			WIDTH, HEIGHT,
			SDL_WINDOW_SHOWN);

	renderer = SDL_CreateRenderer(window,
		       	-1, SDL_RENDERER_ACCELERATED);
	screen = SDL_GetWindowSurface(window);

	loop = 1;

	//Game stuff
	struct sprite player;
	player.texture = loadMedia("assets/W17_npc.bmp");
	player.tile_width = 20;
	player.tile_height = 20;
	player.width = 50;
	player.height = 50;

	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	SDL_Event event;

	while (loop)
	{
		while (SDL_PollEvent(&event) > 0)
		{
			loop = (event.type != SDL_QUIT);
		}

		//phys and anim
		if (keys[SDL_SCANCODE_UP]) {
			ply -= plv;
			player_frame = FORWARD;
		} if (keys[SDL_SCANCODE_DOWN]) {
			ply += plv;
			player_frame = BACK;
		} if (keys[SDL_SCANCODE_LEFT]) {
			plx -= plv;
			player_frame = LEFT;
		} if (keys[SDL_SCANCODE_RIGHT]) {
			plx += plv;
			player_frame = RIGHT;
		}

		SDL_Rect player_source = {
			(int)((player_frame * 2)*spr_tileWidth)%160,
			0,
			spr_tileWidth,
			spr_tileHeight};

		SDL_Rect player_target = {(int)plx, (int)ply, plw, plh};

		SDL_RenderClear(renderer);
		SDL_RenderCopy(
			renderer, player, &player_source, &player_target);
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyTexture(player);

	SDL_FreeSurface(screen);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	SDL_Quit();

	return 0;
}

/* return the loaded SDL_Texture from a bitmap image */
SDL_Texture *loadMedia(const char path[])
{
	SDL_Surface *raw = SDL_LoadBMP(path);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, raw);
	SDL_FreeSurface(raw);
	return texture;
}
