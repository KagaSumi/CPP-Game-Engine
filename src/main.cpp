
#include "Game.h"
#include "utils/Vector2D.h"
#include "iostream"

//global Variable
Game *game = nullptr;
int testVector2D() {
    Vector2D a(3, 4);
    Vector2D b(1, 2);

    std::cout << "Prior to addition a = " << a << '\n';
    a += b;              // a is now (4, 6)
    Vector2D c = a - b;  // c is (3, 4)
    Vector2D d = a * 2;  // d is (8, 12)
    Vector2D e = 2 * a;  // e is also (8, 12)
    Vector2D f = -a;     // f is (-4, -6)
    bool same = (a == b); // false
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "c = " << c << '\n';
    std::cout << "d = " << d << '\n';
    std::cout << "e = " << e << '\n';
    std::cout << "f = " << f << '\n';
    std::cout << "a == b ? " << std::boolalpha << same << '\n';

    return 0;
}

int main(){
    //testVector2D();
    const int FPS = 60; //60 is the norm
    const int desiredFrametime = 1000/FPS;

    Uint64 ticks = SDL_GetTicks(); //time in ms since we initialized SDL
    float deltaTime = 0.0f;
    int actualFrameTime ;

    game = new Game();
    game->init("Assignment 1", 800,600, false);

    while (game->running()) {

        Uint64 currentTicks = SDL_GetTicks();
        deltaTime = (currentTicks - ticks) / 1000.0f;
        ticks = currentTicks;

        game->handleEvents();
        game->update(deltaTime);
        game->render();

        actualFrameTime = SDL_GetTicks() - ticks;// Elapsed time in ms it took the frame

        //Frame Limiter
        if (actualFrameTime < desiredFrametime) {
            SDL_Delay((desiredFrametime - actualFrameTime));
            //If the frame took less time than desired frame (delay the difference)
        }

    }
    delete game;

    return 0;
}
