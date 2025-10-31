#ifndef SDL_RUNNER_H
#define SDL_RUNNER_H


int run_sdl_image(const char* filepath);
int rotate_image_90(const char* filepath, int clockwise);
void Close_All(FILE* file, char** Matrice);

Uint32 get_pixel(SDL_Surface* img, unsigned x, unsigned y);
void set_pixel(SDL_Surface* img, unsigned x, unsigned y, Uint32 pixel);
void image_split_x(SDL_Surface* surface);

void extractLettersToFolder(const char* inputFile, const char* outputDir);
#endif
