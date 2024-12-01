CC_EXEC = g++
CC_FLAGS = -c
CC_STD = -std=c++11

CC = ${CC_EXEC} ${CC_STD} ${CC_FLAGS}

BUILD_DIR = build

OBJECT_FILES =  ${BUILD_DIR}/main.o ${BUILD_DIR}/functions.o ${BUILD_DIR}/mission.o \
				${BUILD_DIR}/driver.o ${BUILD_DIR}/mission_system.o  ${BUILD_DIR}/process_cmd.o \
				${BUILD_DIR}/ride.o
				
main: ${OBJECT_FILES}
	${CC_EXEC} ${CC_STD} ${OBJECT_FILES} -o main 

${BUILD_DIR}/main.o: main.cpp process_cmd.hpp constants.hpp functions.hpp mission.hpp mission_system.hpp ride.hpp
	${CC} main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/functions.o: functions.cpp functions.hpp constants.hpp mission.hpp
	${CC} functions.cpp -o ${BUILD_DIR}/functions.o

${BUILD_DIR}/mission.o: mission.cpp mission.hpp functions.hpp constants.hpp
	${CC} mission.cpp -o ${BUILD_DIR}/mission.o

${BUILD_DIR}/driver.o: driver.cpp driver.hpp ride.hpp constants.hpp functions.hpp
	${CC} driver.cpp -o ${BUILD_DIR}/driver.o

${BUILD_DIR}/mission_system.o: mission_system.cpp mission_system.hpp mission.hpp driver.hpp ride.hpp
	${CC} mission_system.cpp -o ${BUILD_DIR}/mission_system.o

${BUILD_DIR}/process_cmd.o: process_cmd.cpp process_cmd.hpp constants.hpp functions.hpp mission.hpp mission_system.hpp ride.hpp
	${CC} process_cmd.cpp -o ${BUILD_DIR}/process_cmd.o

${BUILD_DIR}/ride.o: ride.cpp ride.hpp
	${CC} ride.cpp -o ${BUILD_DIR}/ride.o

clean:
	rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}