CC_EXEC = g++
CC_FLAGS = -c 
CC_STD = -std=c++11

CC = ${CC_EXEC} ${CC_STD} ${CC_FLAGS}

BUILD_DIR = build

FLAGS = -lsfml-graphics -lsfml-window -lsfml-system

OBJECT_FILES = ${BUILD_DIR}/main.o ${BUILD_DIR}/game.o \
 ${BUILD_DIR}/turtle.o ${BUILD_DIR}/manual.o ${BUILD_DIR}/map.o \
 ${BUILD_DIR}/map_stuff.o

turtix.out: ${OBJECT_FILES}
	${CC_EXEC} ${CC_STD} ${OBJECT_FILES} -o turtix.out ${FLAGS}

${BUILD_DIR}/main.o: main.cpp manual.hpp turtle.hpp game.hpp 
	${CC} main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/game.o: game.cpp game.hpp manual.hpp turtle.hpp map_stuff.hpp
	${CC} game.cpp -o ${BUILD_DIR}/game.o

${BUILD_DIR}/turtle.o: turtle.cpp turtle.hpp manual.hpp
	${CC} turtle.cpp -o ${BUILD_DIR}/turtle.o

${BUILD_DIR}/manual.o: manual.cpp manual.hpp
	${CC} manual.cpp -o ${BUILD_DIR}/manual.o	

${BUILD_DIR}/map.o: map.cpp map.hpp map_stuff.hpp
	${CC} map.cpp -o ${BUILD_DIR}/map.o

${BUILD_DIR}/map_stuff.o: map_stuff.cpp map_stuff.hpp
	${CC} map_stuff.cpp -o ${BUILD_DIR}/map_stuff.o

clean:
	rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}