/* IMG_Load for TecnoballZ on AmigaOS (see include/SDL/SDL_image.h), on
 * libpng: there is no SDL_image 1.2 for OpenGPU's SDL 1.2. The game's
 * pictures are all palette PNGs (4 or 8 bits) and it draws in 8 bits with
 * their palettes, so they become 8-bit surfaces with the PNG's palette, as
 * SDL_image makes them. The AmiCradle Team. GPL 3 or later, like TecnoballZ. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <png.h>
#include "SDL_image.h"

SDL_Surface *IMG_Load(const char *file)
{
	FILE *f = fopen(file, "rb");
	png_structp png = NULL;
	png_infop info = NULL;
	SDL_Surface *volatile surf = NULL;
	png_bytep *volatile rows = NULL;
	png_uint_32 w, h, y;
	int depth, ctype;

	if (!f) {
		SDL_SetError("IMG_Load: can't open %s", file);
		return NULL;
	}
	png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png)
		info = png_create_info_struct(png);
	if (!png || !info) {
		SDL_SetError("IMG_Load: out of memory");
		goto out;
	}
	if (setjmp(png_jmpbuf(png))) {
		SDL_SetError("IMG_Load: bad PNG %s", file);
		if (surf)
			SDL_FreeSurface(surf);
		surf = NULL;
		goto out;
	}
	png_init_io(png, f);
	png_read_info(png, info);
	png_get_IHDR(png, info, &w, &h, &depth, &ctype, NULL, NULL, NULL);
	if (ctype == PNG_COLOR_TYPE_PALETTE) {
		png_colorp pal;
		int n, i;
		SDL_Color colors[256];

		if (depth < 8)
			png_set_packing(png);
		png_read_update_info(png, info);
		surf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 8, 0, 0, 0, 0);
		if (!surf)
			goto out;
		if (png_get_PLTE(png, info, &pal, &n)) {
			if (n > 256)
				n = 256;
			for (i = 0; i < n; i++) {
				colors[i].r = pal[i].red;
				colors[i].g = pal[i].green;
				colors[i].b = pal[i].blue;
				colors[i].unused = 0;
			}
			SDL_SetColors(surf, colors, 0, n);
		}
	} else {
		/* not in TecnoballZ's data: 32-bit RGBA, for completeness */
		if (depth == 16)
			png_set_strip_16(png);
		if (ctype == PNG_COLOR_TYPE_GRAY || ctype == PNG_COLOR_TYPE_GRAY_ALPHA)
			png_set_gray_to_rgb(png);
		if (depth < 8)
			png_set_expand(png);
		if (png_get_valid(png, info, PNG_INFO_tRNS))
			png_set_tRNS_to_alpha(png);
		if (!(ctype & PNG_COLOR_MASK_ALPHA))
			png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
		png_read_update_info(png, info);
		surf = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
			0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
		if (!surf)
			goto out;
	}
	rows = malloc(sizeof(png_bytep) * h);
	if (!rows) {
		SDL_FreeSurface(surf);
		surf = NULL;
		goto out;
	}
	for (y = 0; y < h; y++)
		rows[y] = (png_bytep) surf->pixels + y * surf->pitch;
	png_read_image(png, rows);
	png_read_end(png, NULL);
out:
	free(rows);
	if (png)
		png_destroy_read_struct(&png, info ? &info : NULL, NULL);
	fclose(f);
	return surf;
}
