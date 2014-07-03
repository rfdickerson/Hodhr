#include <iostream>

#include <GL/glew.h>
#include <GL/glut.h>

#include <SDL.h>
#include <memory>

#include "SceneNode.h"
#include "ShaderLibrary.h"
#include "TerrainPatch.h"
#include "AssetLibrary.h"
#include "Renderer.h"
#include "Camera.h"
#include "CubeMesh.h"
#include "Model.h"

#define PROGRAM_NAME "World Viewer"

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

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
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

    SDL_GL_MakeCurrent(mainwindow, maincontext);

    SDL_GL_SetSwapInterval(1);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    glewExperimental = GL_TRUE;
    GLenum result = glewInit();
    if (result != GLEW_OK)
      {
	cerr << "Problem initializing GLEW" << endl;
      }

    if (GLEW_VERSION_1_1)
      {
	cout << "Graphics Successfully Initialized" << endl;
	cout << "  Version: " << glGetString(GL_VERSION) << endl;
	cout << "  Vendor: " << glGetString(GL_VENDOR) << endl;
	cout << " Renderer: " << glGetString(GL_RENDERER) << endl;
      }

    if (SDL_HasSSE42)
      {
	cout << "CPU has SSE4.2 features!" << endl;
      }

    cout << "Number of logical CPU cores: " << SDL_GetCPUCount() << endl;
    cout << "System has " << SDL_GetSystemRAM() << " memory" << endl;
    //ShaderLibrary *sl = &ShaderLibrary::getInstance();



    SDL_Event event;

    auto sl = make_unique<ShaderLibrary>();
    sl->addShader("basic", "resources/shaders/basic.vs", "resources/shaders/basic.fs");
    sl->addShader("screen", "resources/shaders/screen.vs", "resources/shaders/screen.fs");

    auto renderer = make_unique<Renderer> (WIDTH, HEIGHT);
    renderer->init();
    
    auto camera = make_unique<Camera> (WIDTH, HEIGHT);

    Shader* screenShader = sl->getShader("screen");
    renderer->setScreenShader(screenShader);

    Shader* basicShader = sl->getShader("basic");

    // load the assets
    auto assets = make_unique<AssetLibrary>();
    assets->addTerrainPatch("simpleterrain");

    Model* terrainModel = assets->getModel("simpleterrain");
    terrainModel->setShader(basicShader);
    terrainModel->init();

    auto cubeMesh = make_unique<CubeMesh>();
    cubeMesh->setShader(basicShader);
    cubeMesh->init();
    assets->addAsset("cube", std::move(cubeMesh));
    
    Model* c = assets->getModel("cube");

    // make the scene graph
    auto rootNode = make_unique<SceneNode>("root node");

    // make the terrain node
    unique_ptr<SceneNode> terrainNode ( new SceneNode("terrain node"));
    terrainNode->setAsset(terrainModel);

    // make the cube node
    auto cubeNode = make_unique<SceneNode>("cube node");
    cubeNode->setAsset(c);


    rootNode->addChild( std::move(terrainNode) );
    rootNode->addChild( std::move(cubeNode) );

    renderer->setRootSceneNode( std::move(rootNode));
    renderer->setCamera( camera.get() );

    int done = 0;
    int interval = 20;

    int x,y;

    int currentTick;
    int lastTick;
    float dt;

    while (done == 0)
    {
      	
        currentTick = SDL_GetTicks();
	dt = ((float)(currentTick-lastTick))*0.1;
	lastTick = currentTick;
        //waitTicks = (oldTicks + interval) - currentTick;
        //oldTicks = currentTick;

        //if (waitTicks>0)
        //{
        //    SDL_Delay(1);
        //}

        while (SDL_PollEvent(&event))
        {
            if ( event.type == SDL_MOUSEMOTION )
            {
                x = event.motion.x;
                y = event.motion.y;

		//cout << "dt:" << dt << " dx: " 
		//     << event.motion.xrel << " dy: " << event.motion.yrel << endl;
		camera->rotate( dt, event.motion.xrel, event.motion.yrel);

                //cout << "X: " << x << " Y: " << y << endl;
            }

            if (event.type == SDL_QUIT) { done = 1;}
            if (event.type == SDL_KEYDOWN)
            {

	      switch ( event.key.keysym.sym ) {
	      case SDLK_w:
		camera->move( dt, .02);
		break;
	      case SDLK_s:
		camera->move( dt, -0.02);
		break;
	      case SDLK_ESCAPE:
		done = 1;
		break;
	      default:
		break;
	      }
	      //done = 1;
            }
        }

	/* draw the scene */
        renderer->draw();

        SDL_GL_SwapWindow(mainwindow);

    }

    //delete terrain;
    // delete renderer;
   

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    return 0;
}
