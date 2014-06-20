#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <SDL.h>


#include "ShaderLibrary.h"
#include "TerrainPatch.h"
#include "Renderer.h"

#define PROGRAM_NAME "Tutorial1"

const int WIDTH = 1024;
const int HEIGHT = 768;

using namespace std;

void sdldie(const char *msg)
{
    printf("%s: %s\n", msg, SDL_GetError());
    SDL_Quit();
    exit(1);
}

void checkSDLError(int line = -1)
{
        const char *error = SDL_GetError();
        if (*error != '\0')
        {
                printf("SDL Error: %s\n", error);
                if (line != -1)
                        printf(" + line: %i\n", line);
                SDL_ClearError();
        }
}


int main()
{
   
    int oldTicks=0;

    SDL_Window *mainwindow;
    SDL_GLContext maincontext;
    
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) <0)
    {
        cout << "err";
    }

        
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");
        
        
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);
    
    SDL_GL_SetSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    glewInit();

    ShaderLibrary *sl = &ShaderLibrary::getInstance();
    sl->addShader("basic", "../resources/shaders/basic.vs", "../resources/shaders/basic.fs");


    SDL_Event event;

    Renderer *renderer = new Renderer(WIDTH, HEIGHT);
    renderer->init();
     
    TerrainPatch *terrain = new TerrainPatch();
    terrain->init();
 
    int done = 0;
    int interval = 20;

    while (done == 0)
    {
        int currentTick;
        int waitTicks;

        currentTick = SDL_GetTicks();
        waitTicks = (oldTicks + interval) - currentTick;
        oldTicks = currentTick;

        if (waitTicks>0)
        {
            SDL_Delay(waitTicks);
        }

        while (SDL_PollEvent(&event)) 
        {
            if (event.type == SDL_QUIT) { done = 1;}
            if (event.type == SDL_KEYDOWN)
            {
                done = 1;
            }
        }

        // Clear our buffer with a red background */
        glClearColor ( 0.2, 0.2, 0.2, 1.0 );
        glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
        /* Swap our back buffer to the front */

        renderer->draw();

        //terrain->draw();



        SDL_GL_SwapWindow(mainwindow);

    }
    
    delete terrain;
    delete renderer;

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    return 0;
}