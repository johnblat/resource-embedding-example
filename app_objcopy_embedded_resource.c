#include <stdlib.h>
#include "include/SDL3/SDL.h"
#include <stdint.h>
#define STB_IMAGE_IMPLEMENTATION
#include "include/stb_image.h"

// UNIX-Y
extern char _binary_waving_person_png_start[];
extern char _binary_waving_person_png_end[];
extern char _binary_waving_person_png_size[];

#define WAVING_PERSON_PNG_DATA _binary_waving_person_png_start
#define WAVING_PERSON_PNG_SIZE ((int)(_binary_waving_person_png_end - _binary_waving_person_png_start))
// UNIX-Y

SDL_Window *window;
SDL_Renderer *renderer;

int main()
{
  
	// CREATE WINDOW AND RENDERER (CANVAS TO DRAW ON)
	int ok = SDL_CreateWindowAndRenderer("objcopy method of resource embedding example",720, 720, 0, &window, &renderer);
	if (ok < 0)
	{
		fprintf(stderr, "Error: Could not initialize SDL\n");
		return 1;
	}

	// LOAD UNCOMPRESSED IMAGE BYTES FROM PNG DATA
	int32_t img_x, img_y, img_channels;
	unsigned char *img_bytes = stbi_load_from_memory(WAVING_PERSON_PNG_DATA, WAVING_PERSON_PNG_SIZE, &img_x, &img_y, &img_channels, 4);
	if(img_bytes == NULL)
	{
		fprintf(stderr, "error: unable to load image bytes\n");
		return 0;
	}

	// CONVERT IMAGE BYTES TO SDL SURFACE (RGBA PIXELS IN CPU MEMORY)
	SDL_Surface *surface = SDL_CreateSurfaceFrom(img_x, img_y, SDL_PIXELFORMAT_RGBA32, img_bytes, img_x * 4);
	if (surface == NULL)
	{
		char *error = SDL_GetError();
		fprintf(stderr, "error: %s", error);
		return 1;
	}

	// CONVERT RGBA PIXELS IN CPU MEMORY TO GPU TEXTURE
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
	if (texture == NULL)
	{
		char *error = SDL_GetError();
		fprintf(stderr, "error: %s", error);
		return 1;
	}

	while(1)
	{
		// IF USER CLOSES WINDOW, STOP RUNNING	
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			if (event.type == SDL_EVENT_WINDOW_CLOSE_REQUESTED)
			{
				return 0;
			}
		}

		{
			// CLEAR CANVAS
			SDL_SetRenderDrawColor(renderer, 255,255,255,255);
			SDL_RenderClear(renderer);

			// DRAW TEXTURE ON CANVAS
			bool success = SDL_RenderTexture(renderer, texture, NULL, NULL);
			if (success == false)
			{
				char *error = SDL_GetError();
				fprintf(stderr, "error: %s", error);
				return 1;
			}

			// PRESENT DRAWN CANVAS ON WINDOW
			SDL_RenderPresent(renderer);

			// WAIT 16 ms
			SDL_Delay(16);
		}
	}
}