CC_EXEC = g++
CC_FLAGS = -c
CC_STD = -std=c++11

CC = ${CC_EXEC} ${CC_STD} ${CC_FLAGS}

BUILD_DIR = build

OBJECT_FILES = ${BUILD_DIR}/main.o ${BUILD_DIR}/player.o ${BUILD_DIR}/team.o \
			   ${BUILD_DIR}/match.o ${BUILD_DIR}/week.o ${BUILD_DIR}/league.o \
			   ${BUILD_DIR}/inp_funcs.o ${BUILD_DIR}/prim_funcs.o \
			   ${BUILD_DIR}/squad.o ${BUILD_DIR}/user.o ${BUILD_DIR}/system.o 
			   
MAIN_HPP_FILES = constants.hpp player.hpp team.hpp match.hpp week.hpp prim_funcs.hpp \
				 inp_funcs.hpp league.hpp process_cmd.hpp

futballFantasy.out: ${OBJECT_FILES}
	${CC_EXEC} ${CC_STD} ${OBJECT_FILES} -o futballFantasy.out

${BUILD_DIR}/main.o: ${MAIN_HPP_FILES}
	${CC} main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/player.o: player.cpp player.hpp constants.hpp structs.hpp 
	${CC} player.cpp -o ${BUILD_DIR}/player.o

${BUILD_DIR}/team.o: team.cpp team.hpp player.hpp prim_funcs.hpp
	${CC} team.cpp -o ${BUILD_DIR}/team.o

${BUILD_DIR}/match.o: match.cpp match.hpp constants.hpp structs.hpp
	${CC} match.cpp -o ${BUILD_DIR}/match.o

${BUILD_DIR}/week.o: week.cpp week.hpp player.hpp team.hpp constants.hpp match.hpp structs.hpp
	${CC} week.cpp -o ${BUILD_DIR}/week.o

${BUILD_DIR}/league.o: league.cpp league.hpp player.hpp team.hpp match.hpp week.hpp prim_funcs.hpp
	${CC} league.cpp -o ${BUILD_DIR}/league.o

${BUILD_DIR}/inp_funcs.o: inp_funcs.cpp inp_funcs.hpp league.hpp player.hpp team.hpp \
						  match.hpp week.hpp constants.hpp prim_funcs.hpp
	${CC} inp_funcs.cpp -o ${BUILD_DIR}/inp_funcs.o

${BUILD_DIR}/prim_funcs.o: prim_funcs.cpp prim_funcs.hpp constants.hpp player.hpp team.hpp user.hpp
	${CC} prim_funcs.cpp -o ${BUILD_DIR}/prim_funcs.o

${BUILD_DIR}/process_cmd.o: process_cmd.cpp process_cmd.hpp constants.hpp league.hpp \
							player.hpp team.hpp match.hpp week.hpp prim_funcs.hpp
	${CC} process_cmd.cpp -o ${BUILD_DIR}/process_cmd.o 

${BUILD_DIR}/squad.o: squad.cpp squad.hpp constants.hpp player.hpp structs.hpp
	${CC} squad.cpp -o ${BUILD_DIR}/squad.o

${BUILD_DIR}/user.o: user.cpp user.hpp squad.hpp constants.hpp player.hpp structs.hpp
	${CC} user.cpp -o ${BUILD_DIR}/user.o

${BUILD_DIR}/system.o: system.cpp system.hpp constants.hpp admin.hpp league.hpp prim_funcs.hpp \
					   inp_funcs.hpp player.hpp team.hpp match.hpp week.hpp user.hpp squad.hpp
	${CC} system.cpp -o ${BUILD_DIR}/system.o
				
clean:
	rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}