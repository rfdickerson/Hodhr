// Copyright Robert Dickerson 2014

#include <GL/glew.h>
#include <GL/glut.h>

#include <SDL.h>
// #include <memory>

#include "hodhr.h"

#define PROGRAM_NAME "Hodhr"

const int WIDTH = 1280;
const int HEIGHT = 768;

const float SPEED = 0.4f;

void sdldie(const char *msg) {
  printf("%s: %s\n", msg, SDL_GetError());
  SDL_Quit();
  exit(1);
}

void checkSDLError(int line = -1) {
  const char *error = SDL_GetError();
  if (*error != '\0') {
    printf("SDL Error: %s\n", error);
    if (line != -1)
      printf(" + line: %i\n", line);
    SDL_ClearError();
  }
}


int main() {
  // int oldTicks = 0;
  
  SDL_Window *mainwindow;
  SDL_GLContext maincontext;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) <0) {
    fprintf(stderr, "Could not initialize SDL\n");
  }
  
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                      SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
  
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
  SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
  
  // multisample antialiasing
  // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
  // SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);

  mainwindow = SDL_CreateWindow(PROGRAM_NAME,
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				WIDTH, HEIGHT,
				SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if (!mainwindow) /* Die if creation failed */
    sdldie("Unable to create window");
  
  
  maincontext = SDL_GL_CreateContext(mainwindow);
  checkSDLError(__LINE__);
  
  SDL_GL_MakeCurrent(mainwindow, maincontext);
  
  SDL_GL_SetSwapInterval(0);
  SDL_SetRelativeMouseMode(SDL_TRUE);
  
  glewExperimental = GL_TRUE;
  GLenum result = glewInit();
  if (result != GLEW_OK) {
    fprintf(stderr, "Problem initializing GLEW\n");
  }

  if (GLEW_VERSION_1_1) {
    fprintf(stderr, "Graphics successfully initialized\n");
    fprintf(stderr, "Version: %s\n", glGetString(GL_VERSION));
    fprintf(stderr, "Vendor: %s\n", glGetString(GL_VENDOR));
    fprintf(stderr, "Renderer: %s\n", glGetString(GL_RENDERER));
  }

  if (SDL_HasSSE42())      {
    fprintf(stderr, "CPU has SSE4.2 features!\n");
  }

  fprintf(stderr, "CPU has %i logical CPU cores\n", SDL_GetCPUCount());
  fprintf(stderr, "System has %i MB of memory\n", SDL_GetSystemRAM());



    SDL_Event event;

    //auto sl = make_unique<Hodhr::ShaderLibrary>();
    Hodhr::ShaderLibrary sl;
    sl.AddShader("basic",
                  "resources/shaders/basic.vert",
                  "resources/shaders/basic.frag");
    sl.AddShader("screen",
                  "resources/shaders/screen.vert",
                  "resources/shaders/screen.frag");
    sl.AddShader("flat",
                      "resources/shaders/flat.vert",
                      "resources/shaders/flat.frag");

    Hodhr::Renderer renderer(WIDTH, HEIGHT);
    renderer.init();
    checkSDLError(__LINE__);

    Hodhr::Camera camera(WIDTH, HEIGHT);

    Hodhr::Shader* screenShader = sl.GetShader("screen");
    renderer.setScreenShader(screenShader);

    Hodhr::Shader* basicShader = sl.GetShader("basic");
    // Hodhr::Shader* flatShader = sl.GetShader("flat");

    Hodhr::TextureManager tm;
    Hodhr::Texture* grassTexture = tm.LoadTexture("cube",
                        "resources/images/cube.png", true);
    
    /**
    Hodhr::Texture* artTexture = tm.LoadTexture("art",
						"./resources/images/principes.jpg", false);
    **/

    // load the assets
    Hodhr::AssetLibrary assets;


    // initialize the UI

    // auto user_interface = std::make_unique<Hodhr::UI>(WIDTH, HEIGHT);

    /*
    auto custom_label = std::make_unique<Hodhr::UILabel>();
    custom_label->setShader(flatShader);
    custom_label->create_text("Leveled Up!");
    user_interface->addWidget(std::move(custom_label));
    */
    
    /**
    auto custom_image = std::make_unique<Hodhr::UIImage>();
    custom_image->setShader(flatShader);
    custom_image->setImageTexture(artTexture);
    user_interface->addWidget(std::move(custom_image));
    **/
    
    /**
    auto custom_panel = std::make_unique<Hodhr::UIPanel>(1280,100);
    custom_panel->setShader(flatShader);
    user_interface->addWidget(std::move(custom_panel));
    
    renderer->setUserInterface(user_interface.get());
    **/

    Hodhr::TerrainPatch terrainModel;
    terrainModel.setShader(basicShader);
    terrainModel.setTexture(grassTexture);
    terrainModel.init();
    assets.addAsset("terrain", &terrainModel);


/*
    Hodhr::CubeMesh cubeMesh = new Hodhr::CubeMesh();
    cubeMesh->setShader(basicShader);
    cubeMesh->init();
    assets->addAsset("cube", &cubeMesh);
*/

    // make the obj model

    Hodhr::ObjModel custom_model;
    custom_model.setShader(basicShader);
    custom_model.setTexture(grassTexture);
    custom_model.LoadFile("resources/models/cube.obj");
    assets.addAsset("gadget", &custom_model);


    /**
    Hodhr::Model* custom_m = assets->getModel("gadget");
    if (custom_m == NULL) {
      fprintf(stderr, "Model could not be found\n");
     
    }
    **/

    // Hodhr::Model* c = assets->getModel("cube");
    // Hodhr::Model* t = assets->getModel("terrain");

    // t.setShader(basicShader);
    // t.init();

    // make the scene graph
    Hodhr::SceneNode rootNode ("root node");

    // make the terrain node


    Hodhr::SceneNode terrainNode("terrain node");
    terrainNode.setAsset(&terrainModel);
    // terrainNode->setPosition(0.0f, 1.0f, 0.0f);
    terrainNode.setScale(5.0f);
    // rootNode.addChild( &terrainNode );


    for (int j = 0; j < 3; ++j) {
      for (int i = 0; i < 3; i++) {
        Hodhr::SceneNode* cubeNode = new Hodhr::SceneNode("cube node");
        cubeNode->setAsset(&custom_model);
        cubeNode->setPosition(i*1.5, 0, j*1.5);
        cubeNode->setScale(0.2);
        rootNode.addChild( cubeNode);
        // rootNode->addChild(std::move(cubeNode));
      }
    }


    /**
    auto custom_model_node = make_unique<Hodhr::SceneNode>("custom object");
    custom_model_node->setAsset(custom_m);
    custom_model_node->setScale(.2);
    rootNode->addChild(std::move(custom_model_node));
    **/

    renderer.setRootSceneNode( &rootNode);
    renderer.setCamera( &camera );

    int done = 0;
    // int interval = 20;

    int x, y;

    int currentTick;
    int lastTick;
    float dt;

    bool keysHeld[323] = {false};

    glClearColor(0.2f, 0.2f, 0.3f, 0.0f);


    while (done == 0) {
      currentTick = SDL_GetTicks();
      dt = static_cast<float>((currentTick-lastTick))*0.1f;
      lastTick = currentTick;
      // waitTicks = (oldTicks + interval) - currentTick;
      // oldTicks = currentTick;
      
      while (SDL_PollEvent(&event))        {
        if ( event.type == SDL_MOUSEMOTION ) {
          x = event.motion.x;
          y = event.motion.y;
          

          camera.rotate(dt, event.motion.xrel, event.motion.yrel);

          
        }

        if (event.type == SDL_QUIT) { done = 1;}
        if (event.type == SDL_KEYDOWN) {
          keysHeld[event.key.keysym.sym] = true;
        }
        if (event.type == SDL_KEYUP) {
          keysHeld[event.key.keysym.sym] = false;
        }
        

      }

      if (keysHeld[SDLK_ESCAPE]) {
        done = 1;
      }
      if (keysHeld[SDLK_w]) {
        camera.move(dt, SPEED);
      }
      if (keysHeld[SDLK_s]) {
        camera.move(dt, -SPEED);
      }


      //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      //glViewport(0, 0, WIDTH, HEIGHT);

      /* draw the scene */
      renderer.draw();

      SDL_GL_SwapWindow(mainwindow);

      SDL_Delay(1);
    }

    SDL_GL_DeleteContext(maincontext);
    SDL_DestroyWindow(mainwindow);
    SDL_Quit();
    return 0;
}
