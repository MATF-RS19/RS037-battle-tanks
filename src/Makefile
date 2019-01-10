CFLAGS = -Wall -Wextra -std=c++11 -lglut -lGLU -lGL -lSOIL

tank: main.o draw.o fire.o gamers.o 
	g++ $^ $(CFLAGS) -o $@
	
main.o: main.cpp draw.hpp fire.hpp gamers.hpp
	g++ -c $< $(CFLAGS)
	
draw.o: draw.cpp draw.hpp
	g++ -c $< $(CFLAGS)

fire.o: fire.cpp fire.hpp
	g++ -c $< $(CFLAGS)

gamers.o: gamers.cpp gamers.hpp
	g++ -c $< $(CFLAGS)

	
.PHONY: clean dist

clean:
	-rm *.o $(PROGRAM) *core

dist: clean
	-tar -chvj -C .. -f ../$(PROGRAM).tar.bz2 $(PROGRAM)

