#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int BALL_RADIUS = 72;

struct Ball {
    int x, y;
    int dx, dy;
};

Ball ball;
SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
SDL_Texture* ballText = NULL;  // Moved ballText here to make it globally accessible

SDL_Texture* loadTexture(const std::string& path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL) {
        printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (newTexture == NULL) {
        printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
    }
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

bool initSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gWindow = SDL_CreateWindow("2D Ball Movement", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }
    return true;
}

void closeSDL() {
    SDL_DestroyTexture(ballText);  // Now correctly accessible
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    IMG_Quit();
    SDL_Quit();
}

void updateBall() {
    ball.x += ball.dx;
    ball.y += ball.dy;

    // Boundary checks to reverse the direction if needed
    if (ball.x < 0 || ball.x + BALL_RADIUS > SCREEN_WIDTH) {
        ball.dx = -ball.dx;
        ball.x = (ball.x < 0) ? 0 : SCREEN_WIDTH - BALL_RADIUS;
    }
    if (ball.y < 0 || ball.y + BALL_RADIUS > SCREEN_HEIGHT) {
        ball.dy = -ball.dy;
        ball.y = (ball.y < 0) ? 0 : SCREEN_HEIGHT - BALL_RADIUS;
    }
}

void randomizeDirection() {
    do {
        ball.dx = (rand() % 7) - 3; // Random dx between -3 and 3, excluding 0
        ball.dy = (rand() % 7) - 3; // Random dy between -3 and 3, excluding 0
    } while (ball.dx == 0 || ball.dy == 0); // Ensure neither are zero
}

int main(int argc, char* argv[]) {
    srand(time(NULL));  // Seed random number generator
    if (!initSDL()) {
        printf("Failed to initialize SDL!\n");
        return -1;
    }

    ballText = loadTexture("./Assets/ball.png");
    if (!ballText) {
        printf("Failed to load texture!\n");
        closeSDL();
        return -1;
    }

    randomizeDirection(); // Random initial direction
    ball.x = 0; // Start at top-left corner
    ball.y = 0;

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_RenderClear(gRenderer);
        updateBall();
        SDL_Rect ballRect = { ball.x, ball.y, BALL_RADIUS, BALL_RADIUS };
        SDL_RenderCopy(gRenderer, ballText, NULL, &ballRect);
        SDL_RenderPresent(gRenderer);

        SDL_Delay(10);  // Delay to control frame rate
    }

    closeSDL();
    return 0;
}
