
//cd "C:\Users\Utilisateur\source\repos\SDLS3\x64\Debug" Path for testing in powershell, Personnal

#include <SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include "header.h"

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
        "Fenêtre SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280,
        720,
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Erreur création fenêtre: %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }


    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE); // Create Render with flag Software so we can use Surface on renderer
    if (!renderer) {
        SDL_Log("Erreur création renderer: %s\n", SDL_GetError());
        Clean_Ressources(window, renderer, texture);
        return 1;
    }

    picture = SDL_LoadBMP(argv[1]);
    if (!picture) {
        SDL_Log("Erreur création image: %s\n", SDL_GetError());
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
        SDL_Log("Erreur création texture : %s\n", SDL_GetError());
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
    if (!picture) return 1;

    int w = picture->w;
    int h = picture->h;

    
    SDL_Surface* rotated = SDL_CreateRGBSurfaceWithFormat(0, h, w, 32, picture->format->format);
    if (!rotated) {
        SDL_FreeSurface(picture);
        return 1;
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            Uint32 pixel = ((Uint32*)picture->pixels)[y * w + x];
            if (clockwise) {
                ((Uint32*)rotated->pixels)[x * h + (h - 1 - y)] = pixel;
            }
            else {
                ((Uint32*)rotated->pixels)[(w - 1 - x) * h + y] = pixel;
            }
        }
    }

    SDL_SaveBMP(rotated, filepath);

    SDL_FreeSurface(rotated);
    SDL_FreeSurface(picture);

    return 0;
}