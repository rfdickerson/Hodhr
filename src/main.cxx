#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <SDL.h>


#include "ShaderLibrary.h"
#include "TerrainPatch.h"

#define PROGRAM_NAME "Tutorial1"

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
   

    SDL_Window *mainwindow;
    SDL_GLContext maincontext;
    
    if (SDL_Init(SDL_INIT_VIDEO) <0)
    {
        cout << "err";
    }

        
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    
    mainwindow = SDL_CreateWindow(PROGRAM_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        512, 512, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!mainwindow) /* Die if creation failed */
        sdldie("Unable to create window");
        
        
    maincontext = SDL_GL_CreateContext(mainwindow);
    checkSDLError(__LINE__);
    
    SDL_GL_SetSwapInterval(1);
    
    glewExperimental = GL_TRUE;
    glewInit();

    ShaderLibrary *sl = &ShaderLibrary::getInstance();
    sl->addShader("resources/shaders/basic.vs", "resources/shaders/basic.fs");

     
    TerrainPatch *terrain = new TerrainPatch();
    terrain->init();
 
    /* Clear our buffer with a red background */
    glClearColor ( 1.0, 0.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    /* Swap our back buffer to the front */
    SDL_GL_SwapWindow(mainwindow);
    /* Wait 2 seconds */
    SDL_Delay(2000);
    
     /* Same as above, but green */
    glClearColor ( 0.0, 1.0, 0.0, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(mainwindow);
    SDL_Delay(2000);
        
    
    delete terrain;
    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    return 0;
}
