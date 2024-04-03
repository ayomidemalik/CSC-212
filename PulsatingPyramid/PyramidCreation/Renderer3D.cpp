#include <SDL.h>
#include <vector>
#include <chrono>
#include <cmath>

struct Point3D {
    float x, y, z;
};

struct Point2D {
    int x, y;
};

struct Edge {
    int start, end; // Points indices in the vector
};

class Renderer3D {
public:
    Renderer3D(SDL_Window* _window, SDL_Renderer* renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges);

    void render();

private:
    SDL_Renderer* SDL_render;
    int WindowSizeX, WindowSizeY;
    std::vector<Point3D> points;
    std::vector<Edge> edges;

    float FL = 500.0f; // The focal length

    // Timing for pulsation
    float totalTime = 0.0f; // Keep track of total time passed
    float pulseSpeed = 3.0f; // Pulsation speed

    Point2D projection(Point3D point);
    Point3D scalePoint(Point3D point, float scale);
};

Renderer3D::Renderer3D(SDL_Window* _window, SDL_Renderer* renderer, std::vector<Point3D>& _points, std::vector<Edge>& _edges) {
    SDL_GetWindowSize(_window, &WindowSizeX, &WindowSizeY);
    SDL_render = renderer;
    points = _points;
    edges = _edges;
}

void Renderer3D::render() {
    auto currentTime = std::chrono::high_resolution_clock::now();
    static auto lastFrameTime = currentTime;
    std::chrono::duration<float> elapsed = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
    float deltaTime = elapsed.count();

    totalTime += deltaTime;
    
    float scale = 1.0f + 1.0f * sin(totalTime * pulseSpeed);

    SDL_SetRenderDrawColor(SDL_render, 0, 0, 0, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(SDL_render);
    SDL_SetRenderDrawColor(SDL_render, 255, 255, 255, SDL_ALPHA_OPAQUE); // Colour of pyramid is white

    for (auto& edge : edges) {
        Point3D scaledPointStart = scalePoint(points[edge.start], scale);
        Point3D scaledPointEnd = scalePoint(points[edge.end], scale);
        Point2D start = projection(scaledPointStart);
        Point2D end = projection(scaledPointEnd);

        SDL_RenderDrawLine(SDL_render, start.x, start.y, end.x, end.y);
    }

    SDL_RenderPresent(SDL_render);
}

Point2D Renderer3D::projection(Point3D point) {
    return Point2D{ WindowSizeX / 2 + static_cast<int>((point.x * FL) / (FL + point.z)),
                    WindowSizeY / 2 + static_cast<int>((point.y * FL) / (FL + point.z)) };
}

Point3D Renderer3D::scalePoint(Point3D point, float scale) {
    Point3D scaledPoint;
    scaledPoint.x = point.x * scale;
    scaledPoint.y = point.y * scale;
    scaledPoint.z = point.z * scale;
    return scaledPoint;
}
