#include "cube.h"
#include "Renderer3D.h"
#include <iostream>
#include <vector>
#include <SDL.h>

//Creates an array of points
std::vector<Point3D> points{
    Point3D{ (-10.0f / 3) * 20,  (10.0f / 3) * 20, (-10.0f / 3) * 20 }, // Base point 1
    Point3D{ (10.0f / 3) * 20,   (10.0f / 3) * 20, (-10.0f / 3) * 20 }, // Base point 2
    Point3D{ (-10.0f / 3) * 20,  (10.0f / 3) * 20, (10.0f / 3) * 20  }, // Base point 3
    Point3D{ (10.0f / 3) * 20,   (10.0f / 3) * 20, (10.0f / 3) * 20  }, // Base point 4
    Point3D{ 0,                  (-10.0f / 3) * 20, 0                 }  // Apex point
};

//creates an array of edges (This hold indices referencing to the points array)
std::vector<Edge> edges{
         Edge{ 0, 1 },
         Edge{ 1, 3 },
         Edge{ 3, 2 },
         Edge{ 2, 0 },
         Edge{ 0, 4 },
         Edge{ 1, 4 },
         Edge{ 2, 4 },
         Edge{ 3, 4 },

};


//default C++ function
int main(int argc, char* argv[])
{
    //creating a window and a renderer
    SDL_Window* window;
    SDL_Renderer* renderer;

    //creates a centered window with 960 width and 540 height
    window = SDL_CreateWindow("Cube Renderer", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 540, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    bool running = true;

    //Creating an instance of the the Renderer3D class
    Renderer3D render3D(window, renderer, points, edges);

    while (running)
    {
        //if the quit button is pressed, the loop breaks
        if (SDL_QuitRequested()) { running = false; break; }

        //Calls the function created in the Renderer3D class (render 3D is an instance of the class defined above)
        render3D.render();
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "SDL initialization failed. SDL Error: " << SDL_GetError();
    }
    else
    {
        std::cout << "SDL initialization succeeded!";
    }

    std::cin.get();
    return 0;


    return 0;
}