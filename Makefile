INC=-Iinc
SRC=hw4.cpp glinit.cpp glentry.cpp utils.cpp	
DIRS=glm/ inc/ res/

all:
	g++ $(SRC) $(INC) -o hw4 -lGL -lGLU -lglut -lpthread
	
dist:
	@tar -czvf hw4.tar.gz $(DIRS) $(SRC) Makefile --exclude "*~"
