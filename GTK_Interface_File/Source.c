
//cd "C:\Users\Utilisateur\source\repos\SDLS3\x64\Debug" Path for testing in powershell, Personnal

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Header.h"

/*
void Clean_Ressources(SDL_Window* w, SDL_Renderer* r, SDL_Texture* t) {  // Instead of Destroying manually, this function do it for us 
    
    if (t != NULL) {
        SDL_DestroyTexture(t);
    }
    if (r != NULL) {
        SDL_DestroyRenderer(r);
    }
    if (w != NULL) {
        SDL_DestroyWindow(w);
    }
    SDL_Quit();
}

int run_sdl_image(const char* filepath) {
    
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Surface* picture = NULL;
    SDL_Texture* texture = NULL;
    SDL_Rect Rectangle = {0, 0, 1280, 720 }; // Create a rectangle of scale the size of the windw, at coordonate 0,0 (top left corner)
    double angle = 0;

    if (argc < 2 || argc > 2) {

        printf("Pas d'image, je compile pas %s\n", argv[0]);
        return 1;

    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("Erreur SDL: %s\n", SDL_GetError());
        return 1;
    }

    window = SDL_CreateWindow(
        "Fen tre SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Erreur cr ation fen tre: %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // Create Render with flag Software so we can use Surface on renderer
    if (!renderer) {
        SDL_Log("Erreur cr ation renderer: %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }

    picture = SDL_LoadBMP(argv[1]);
    if (!picture) {
        SDL_Log("Erreur cr ation image: %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }

    if (SDL_MUSTLOCK(picture)) {
        SDL_LockSurface(picture); // Must lock the surface to edit pixels
    }

    //Uint32* pixels = (Uint32*)(*picture).pixels; // Get a grid with all the pixel of the picture

    int w = (*picture).w; // Get weight of picture
    int h = (*picture).h; // Get Height of picture

    for (int i = 0; i < h; i++) {
        Uint8* row = (Uint8*)(*picture).pixels + i * (*picture).pitch;
        Uint32* pixels = (Uint32*)row;
        for (int j = 0; j < w; j++) { // Loop to navigate throught this matrice
            Uint32 pixel = pixels[j];

            Uint8 r, g, b; // r, g and b are Uint 8 values
            SDL_GetRGB(pixel, (*picture).format, &r, &g, &b); // Set a value to r,g b
            Uint8 gray = 0.299 * r + 0.587 * g + 0.114 * b; // Grayscale function depening on r g b
            pixels[j] = SDL_MapRGB((*picture).format, gray, gray, gray);
        }
    }
    if (SDL_MUSTLOCK(picture)) SDL_UnlockSurface(picture);

    texture = SDL_CreateTextureFromSurface(renderer, picture);
    SDL_FreeSurface(picture);
    if (!texture) {
        SDL_Log("Erreur cr ation texture : %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    int SDLQT = SDL_QueryTexture(texture, NULL, NULL, &Rectangle.w, &Rectangle.h); //Apply the texture on the dimension of the rectangle 
    if (SDLQT != 0) {
        SDL_Log("Erreur query texture : %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }

    int SDLRC = SDL_RenderCopy(renderer, texture, NULL, &Rectangle); // Apply texture on renderer
    if (SDLRC != 0) {
        SDL_Log("Erreur renderer copy : %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }

    SDL_RenderPresent(renderer);


    int running = 0;
    SDL_Event event;

    while (running == 0) {


        while (SDL_PollEvent(&event)) {

            switch (event.type) {

            case SDL_QUIT:
                running = 1;
                if (SDL_SaveBMP(picture, "Image.bmp") != 0) {
                    SDL_Log("Erreur sauvegarde image : %s\n", SDL_GetError());
                }
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {

                    running = 1;
                    if (SDL_SaveBMP(picture, "Image.bmp") != 0) {
                        SDL_Log("Erreur sauvegarde image : %s\n", SDL_GetError());
                    }
                    break;

                }
                if (event.key.keysym.sym == SDLK_e) {

                    angle += 90;
                   
                }
                if (event.key.keysym.sym == SDLK_a) {

                    angle -= 90;

                }

            }


        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 30, 255);
        SDL_RenderClear(renderer);

        SDL_Point center = { Rectangle.w / 2, Rectangle.h / 2 };
        SDL_RenderCopyEx(renderer, texture, NULL, &Rectangle, angle, &center, SDL_FLIP_NONE); // Reset everytime the renderer to apply new angle value
      
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // ~60 FPS

    }
    Clean_Ressources(window, renderer, texture);
    return 0;
}*/

void Clean_Ressources(SDL_Surface* picture) {
    if (picture) SDL_FreeSurface(picture);
}

// Main Function : Convert and save picture
int run_sdl_image(const char* filepath) {
    SDL_Surface* picture = SDL_LoadBMP(filepath);
    if (!picture) {
        SDL_Log("Erreur chargement image: %s\n", SDL_GetError());
        return 1;
    }

    if (SDL_MUSTLOCK(picture)) SDL_LockSurface(picture);

    int w = picture->w;
    int h = picture->h;

    for (int i = 0; i < h; i++) {
        Uint8* row = (Uint8*)picture->pixels + i * picture->pitch;
        Uint32* pixels = (Uint32*)row;
        for (int j = 0; j < w; j++) {
            Uint32 pixel = pixels[j];
            Uint8 r, g, b;
            SDL_GetRGB(pixel, picture->format, &r, &g, &b);
            Uint8 gray = 0.299 * r + 0.587 * g + 0.114 * b;
            pixels[j] = SDL_MapRGB(picture->format, gray, gray, gray);
        }
    }

    if (SDL_MUSTLOCK(picture)) SDL_UnlockSurface(picture);

    // Save Image in black and white
    if (SDL_SaveBMP(picture, "Image.bmp") != 0) {
        SDL_Log("Erreur sauvegarde image: %s\n", SDL_GetError());
        Clean_Ressources(picture);
        return 1;
    }

    Clean_Ressources(picture);
    return 0;
}

// Function to rotate image 
int rotate_image_90(const char* filepath, int clockwise) {
    SDL_Surface* picture = SDL_LoadBMP(filepath);
    if (!picture) {
        fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
        return 1;
    }

    int w = picture->w;
    int h = picture->h;

    SDL_Surface* rotated = SDL_CreateRGBSurfaceWithFormat(0, h, w, 32, picture->format->format);
    if (!rotated) {
        fprintf(stderr, "Erreur cr ation surface : %s\n", SDL_GetError());
        SDL_FreeSurface(picture);
        return 1;
    }

    Uint32* src = (Uint32*)picture->pixels;
    Uint32* dst = (Uint32*)rotated->pixels;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Uint32 pixel = src[y * w + x];

            if (clockwise) {
                // Rotation vers la droite
                dst[x * rotated->w + (rotated->w - y - 1)] = pixel;
            }
            else {
                // Rotation vers la gauche
                dst[(rotated->h - x - 1) * rotated->w + y] = pixel;
            }
        }
    }

    if (SDL_SaveBMP(rotated, filepath) != 0) {
        fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
    }

    SDL_FreeSurface(rotated);
    SDL_FreeSurface(picture);
    return 0;
}

Uint32 rgb_to_pixel(Uint8 r, Uint8 g, Uint8 b)
{
    return 255 * pow(2, 24) + r * pow(2, 16) + g * pow(2, 8) + b;
}

Uint8 to_gray(Uint8 r, Uint8 g, Uint8 b)
{
    Uint8 gray = 0.299 * r + 0.587 * g + 0.114 * b;
    return gray;
}

int is_white(Uint32 pixel)
{
    return pixel == 4294967295;
}


static inline Uint8* pixel_ref(SDL_Surface* surf, unsigned x, unsigned y)
{
    int bpp = surf->format->BytesPerPixel;
    return (Uint8*)surf->pixels + y * surf->pitch + x * bpp;
}


// get pixel in bmp thanks to its coordinates x = width and y = height
Uint32 get_pixel(SDL_Surface* img, unsigned x, unsigned y)
{
    Uint8* p = pixel_ref(img, x, y);

    switch (img->format->BytesPerPixel)
    {
    case 1:
        return *p;

    case 2:
        return *(Uint16*)p;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
            return p[0] << 16 | p[1] << 8 | p[2];
        else
            return p[0] | p[1] << 8 | p[2] << 16;

    case 4:
        return *(Uint32*)p;
    }

    return 0;
}


void set_pixel(SDL_Surface* img, unsigned x, unsigned y, Uint32 pixel)
{
    Uint8* p = pixel_ref(img, x, y);

    switch (img->format->BytesPerPixel)
    {
    case 1:
        *p = pixel;
        break;

    case 2:
        *(Uint16*)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        }
        else
        {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        *(Uint32*)p = pixel;
        break;
    }
}







void image_split_x(SDL_Surface* surface)
{
    int w = surface->w;
    int h = surface->h;


    SDL_Surface* left = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface->format->format);
    SDL_Surface* right = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface->format->format);

    int first_black_encountered = 0;
    int white_encountered_again = 0;
    int is_column_white = 0;

    int x = 0;
    while (white_encountered_again == 0)
    {
        for (int y = 0; y < h; y++)
        {
            Uint32 pixel = get_pixel(surface, x, y);

            if (!is_white(pixel))
            {
                first_black_encountered = 1;
            }
            set_pixel(left, x, y, pixel);
        }

        if (first_black_encountered)
        {
            is_column_white += 1;
            for (int y = 0; y < h; y++)
            {
                if (!is_white(get_pixel(surface, x, y)))
                {
                    is_column_white = 0;
                }
            }
            if (is_column_white == 10) // 10 is number of white columns to encounter to split image
            {
                white_encountered_again = 1;
            }
        }

        x++;
    }

    int is_left_list = 0;
    if (x < w / 2)
    {
        if (SDL_SaveBMP(left, "list.bmp") != 0) {
            fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
        }
        int is_left_list = 1;
    }
    else
    {
        if (SDL_SaveBMP(left, "grid.bmp") != 0) {
            fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
        }
    }

    while (x < w)
    {
        for (int y = 0; y < h; y++)
        {
            Uint32 pixel = get_pixel(surface, x, y);
            set_pixel(right, x, y, pixel);
        }
        x++;
    }


    /*
    // saving the surface
    char* buffer[255];
    char* c = itoa(*count, buffer, 10);
    char* ptr = strcat(c, "_is_img.bmp");

    if (SDL_SaveBMP(left, c) != 0) {
        fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
    }*/

    
    if (is_left_list == 1)
    {
        if (SDL_SaveBMP(right, "grid.bmp") != 0) {
            fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
        }
    }
    else
    {
        if (SDL_SaveBMP(right, "list.bmp") != 0) {
            fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
        }
    }
}
void image_split_y(SDL_Surface* surface) 
{
    int w = surface->w;
    int h = surface->h;


    SDL_Surface* top = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface->format->format);
    SDL_Surface* bottom = SDL_CreateRGBSurfaceWithFormat(0, w, h, 32, surface->format->format);
    
    int first_black_encountered = 0;
    int white_encountered_again = 0;
    int white_rows = 0;

    int y = 0;
    while (white_encountered_again == 0)
    {
        for (int x = 0; x < w; x++)
        {
            Uint32 pixel = get_pixel(surface, x, y);

            if (!is_white(pixel))
            {
                first_black_encountered = 1;
            }
            set_pixel(top, x, y, pixel);
        }

        if (first_black_encountered)
        {
            white_rows += 1;
            for (int x = 0; x < w; x++)
            {
                if (!is_white(get_pixel(surface, x, y)))
                {
                    white_rows = 0;
                }
            }
            if (white_rows == 10) // 10 is number of white rows to encounter to split image
            {
                white_encountered_again = 1;
            }
        }

        x++;
    }

    while (y < h)
    {
        for (int x = 0; x < w; x++)
        {
            Uint32 pixel = get_pixel(surface, x, y);
            set_pixel(bottom, x, y, pixel);
        }
        x++;
    }

    if (SDL_SaveBMP(top, "top.bmp") != 0) {
        fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
    }
    if (SDL_SaveBMP(bottom, "bottom.bmp") != 0) {
        fprintf(stderr, "Erreur sauvegarde : %s\n", SDL_GetError());
    }
}


typedef struct {
    int x, y;
} Point;

typedef struct {
    int minX, maxX, minY, maxY;
} BoundingBox;

void floodFillIterative(Uint32* pixels, Uint8* visited, int w, int h,
    int startX, int startY, SDL_PixelFormat* fmt,
    Uint8 threshold, BoundingBox* box) {
    const int maxSize = w * h;
    Point* queue = malloc(sizeof(Point) * maxSize);
    int qStart = 0, qEnd = 0;

    queue[qEnd++] = (Point){ startX, startY };
    visited[startY * w + startX] = 1;

    while (qStart < qEnd) {
        Point p = queue[qStart++];
        int x = p.x, y = p.y;

        if (x < box->minX) box->minX = x;
        if (x > box->maxX) box->maxX = x;
        if (y < box->minY) box->minY = y;
        if (y > box->maxY) box->maxY = y;

        // 4-connected neighbors
        const int dx[4] = { 1, -1, 0, 0 };
        const int dy[4] = { 0, 0, 1, -1 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx < 0 || nx >= w || ny < 0 || ny >= h) continue;

            int nidx = ny * w + nx;
            if (visited[nidx]) continue;

            Uint8 r, g, b;
            SDL_GetRGB(pixels[nidx], fmt, &r, &g, &b);
            Uint8 brightness = (r + g + b) / 3;

            if (brightness > threshold) continue; // background

            visited[nidx] = 1;
            queue[qEnd++] = (Point){ nx, ny };
        }
    }

    free(queue);
}

void extractLetters(const char* inputFile) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("SDL_Init Error: %s\n", SDL_GetError());
        return;
    }

    SDL_Surface* image = SDL_LoadBMP(inputFile);
    if (!image) {
        printf("Unable to load image %s: %s\n", inputFile, SDL_GetError());
        SDL_Quit();
        return;
    }

    if (SDL_LockSurface(image) != 0) {
        printf("Unable to lock surface: %s\n", SDL_GetError());
        SDL_FreeSurface(image);
        SDL_Quit();
        return;
    }

    int w = image->w, h = image->h;
    Uint32* pixels = (Uint32*)image->pixels;
    Uint8* visited = calloc(w * h, 1);
    if (!visited) {
        printf("Memory allocation failed.\n");
        SDL_UnlockSurface(image);
        SDL_FreeSurface(image);
        SDL_Quit();
        return;
    }

    const Uint8 threshold = 200;
    int letterCount = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int idx = y * w + x;
            if (visited[idx]) continue;

            Uint8 r, g, b;
            SDL_GetRGB(pixels[idx], image->format, &r, &g, &b);
            Uint8 brightness = (r + g + b) / 3;
            if (brightness > threshold) continue; // background

            BoundingBox box = { x, x, y, y };
            floodFillIterative(pixels, visited, w, h, x, y, image->format, threshold, &box);

            int bw = box.maxX - box.minX + 1;
            int bh = box.maxY - box.minY + 1;
            if (bw < 3 || bh < 3) continue;

            SDL_Surface* letter = SDL_CreateRGBSurface(0, bw, bh, 32,
                0x00FF0000,
                0x0000FF00,
                0x000000FF,
                0xFF000000);
            if (!letter) continue;

            Uint32* dst = (Uint32*)letter->pixels;
            for (int ly = 0; ly < bh; ly++) {
                for (int lx = 0; lx < bw; lx++) {
                    dst[ly * bw + lx] = pixels[(box.minY + ly) * w + (box.minX + lx)];
                }
            }

            char filename[64];
            snprintf(filename, sizeof(filename), "letter_%03d.bmp", letterCount++);
            SDL_SaveBMP(letter, filename);
            SDL_FreeSurface(letter);
        }
    }

    printf("Extracted %d letters.\n", letterCount);

    free(visited);
    SDL_UnlockSurface(image);
    SDL_FreeSurface(image);
    SDL_Quit();
}

