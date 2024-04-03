#include "cubeNoOOP.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <SDL.h>

struct Point2D { float x; float y; };
struct Point3D { float x; float y; float z; };
struct Edge { int start; int end; };

int WindowSizeX;
int WindowSizeY;
SDL_Renderer* renderer;
float DeltaTime = 0;
float FL = 5;


//Creates an array of points
/*std::vector<Point3D> points2{
         Point3D{ -1, -1, -1 }, Point3D{ -1, -1, 1 },
         Point3D{ 1,  -1, -1 }, Point3D{ -1,  1, -1 },
         Point3D{ -1, 1, 1 }, Point3D{ 1,  -1, 1 },
         Point3D{ 1,  1, -1 }, Point3D{ 1,  1, 1 }
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
*/

Point2D projection2(Point3D point)
{
    return Point2D{ WindowSizeX / 2 + (point.x * FL) / (FL + point.z) * 100, WindowSizeY / 2 + (point.y * FL) / (FL + point.z) * 100 };
}

void render2(std::vector<Point3D> points, std::vector<Edge> edges)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);

    //rotation += 1 * DeltaTime;

    for (auto& edge : edges) {
        Point2D start = projection2(points[edge.start]);
        Point2D end = projection2(points[edge.end]);

        SDL_RenderDrawLine(renderer, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(renderer);
}



