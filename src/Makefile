all: hodhr	

CC := g++
CFLAGS := -g -c -Wall -std=c++11
LDFLAGS := -lSDL2 -lSDL2_image

OBJECTS := terrainpatch.o model.o texture.o main.o scenenode.o shader.o camera.o common.o shaderlibrary.o renderer.o texturemanager.o assetlibrary.o objmodel.o
INCLUDES := -I../include -I/usr/local/include/glm
SDL_CFLAGS := $(shell sdl2-config --cflags) $(shell pkg-config --cflags cairo pango glew)
SDL_LDFLAGS := $(shell sdl2-config --libs) $(shell pkg-config --libs cairo pango glew)

hodhr: $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(SDL_LDFLAGS) $(LDFLAGS)
	mv hodhr ..

%.o: %.cc
	$(CC) $(INCLUDES) $(CFLAGS) $(SDL_CFLAGS) $< -o $@

clean:
	rm -rf *o hodhr
