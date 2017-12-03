all: chessprog

clean:
	-rm -rf *o chessprog

chessprog: MinMax.o console_services.o Logic.o main.o parseUserInput.o services.o settings.o unitTests.o xml.o Gui.o
	gcc  -o chessprog MinMax.o Gui.o console_services.o Logic.o main.o parseUserInput.o services.o settings.o unitTests.o xml.o -lm -std=c99 -pedantic-errors -g `sdl-config --libs`

console_services.o: console_services.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm console_services.c `sdl-config --cflags`

Logic.o: Logic.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Logic.c `sdl-config --cflags`

main.o: main.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm main.c `sdl-config --cflags`

parseUserInput.o: parseUserInput.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm parseUserInput.c `sdl-config --cflags`

services.o: services.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm services.c `sdl-config --cflags`

settings.o: settings.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm settings.c `sdl-config --cflags`

unitTests.o: unitTests.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm unitTests.c `sdl-config --cflags`

xml.o: xml.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm xml.c `sdl-config --cflags`
	
Gui.o: Gui.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm Gui.c `sdl-config --cflags`

MinMax.o: MinMax.c
	gcc  -std=c99 -pedantic-errors -c -Wall -g -lm MinMax.c `sdl-config --cflags`
