#ifndef SDL_RUNNER_H
#define SDL_RUNNER_H


int run_sdl_image(const char* filepath);
int rotate_image_90(const char* filepath, int clockwise);
void Close_All(FILE* file, char** Matrice);

int Check_Vertically(char* Word, char** Matrice);

int Check_Horizontally(char* Word, char** Matrice);
int Check_Diagonally(char* Word, char** Matrice);
int Check_Diagonnaly2(char* Word, char** Mat);
#endif
