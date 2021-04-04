all: g++
	@echo "Done."

g++: *.cpp
	g++ -c *.cpp tinyxml/*.cpp 
	g++ -o trabalhocg *.h *.o -lGL -lGLU -lglut -lm

clean:
	rm -rf *.o trabalhocg