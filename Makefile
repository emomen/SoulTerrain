CFLAGS = -I ./include
##LIB    = ./libggfonts.so
LFLAGS = -lrt -lX11 -lGLU -lGL -pthread -lm #-lXrandr

all: asteroids

asteroids: asteroids.cpp log.cpp timers.cpp emomen.cpp nromasanta.cpp iruiz.cpp acardenassil.cpp
	g++ $(CFLAGS) asteroids.cpp log.cpp timers.cpp nromasanta.cpp emomen.cpp acardenassil.cpp iruiz.cpp libggfonts.a -Wall -Wextra $(LFLAGS) -oasteroids

clean:
	rm -f asteroids
	rm -f *.o
