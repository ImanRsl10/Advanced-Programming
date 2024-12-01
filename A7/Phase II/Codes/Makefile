CC_EXEC = g++
CC_FLAGS = -c
CC_STD = -std=c++11

CC = ${CC_EXEC} ${CC_STD} ${CC_FLAGS}

INCLUDE = include
SOURCE = source
BUILD_DIR = build

OBJECT_FILES = ${BUILD_DIR}/main.o ${BUILD_DIR}/player.o ${BUILD_DIR}/goal_keeper.o \
			   ${BUILD_DIR}/defender.o ${BUILD_DIR}/midfielder.o ${BUILD_DIR}/forward.o \
			   ${BUILD_DIR}/team.o ${BUILD_DIR}/match_team.o ${BUILD_DIR}/match.o \
			   ${BUILD_DIR}/week.o ${BUILD_DIR}/league.o ${BUILD_DIR}/inp_funcs.o \
			   ${BUILD_DIR}/prim_funcs.o ${BUILD_DIR}/squad_player.o ${BUILD_DIR}/squad.o \
			   ${BUILD_DIR}/user.o ${BUILD_DIR}/system.o 
			   
MAIN_HPP_FILES = ${INCLUDE}/constants.hpp ${INCLUDE}/player.hpp ${INCLUDE}/team.hpp \
				 ${INCLUDE}/match.hpp  ${INCLUDE}/week.hpp ${INCLUDE}/prim_funcs.hpp \
				 ${INCLUDE}/inp_funcs.hpp ${INCLUDE}/league.hpp ${INCLUDE}/process_cmd.hpp

futballFantasy.out: ${OBJECT_FILES}
	${CC_EXEC} ${CC_STD} ${OBJECT_FILES} -o futballFantasy.out

${BUILD_DIR}/main.o: ${MAIN_HPP_FILES}
	${CC} ${SOURCE}/main.cpp -o ${BUILD_DIR}/main.o

${BUILD_DIR}/player.o: ${SOURCE}/player.cpp ${INCLUDE}/player.hpp ${INCLUDE}/constants.hpp \
					   ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp ${INCLUDE}/match.hpp
	${CC} ${SOURCE}/player.cpp -o ${BUILD_DIR}/player.o

${BUILD_DIR}/goal_keeper.o: ${SOURCE}/goal_keeper.cpp ${INCLUDE}/goal_keeper.hpp ${INCLUDE}/player.hpp \
							${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/goal_keeper.cpp -o ${BUILD_DIR}/goal_keeper.o

${BUILD_DIR}/defender.o: ${SOURCE}/defender.cpp ${INCLUDE}/defender.hpp ${INCLUDE}/player.hpp \
						 ${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/defender.cpp -o ${BUILD_DIR}/defender.o

${BUILD_DIR}/midfielder.o: ${SOURCE}/midfielder.cpp ${INCLUDE}/midfielder.hpp ${INCLUDE}/player.hpp \
					       ${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/midfielder.cpp -o ${BUILD_DIR}/midfielder.o

${BUILD_DIR}/forward.o: ${SOURCE}/forward.cpp ${INCLUDE}/forward.hpp ${INCLUDE}/player.hpp \
						${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/forward.cpp -o ${BUILD_DIR}/forward.o

${BUILD_DIR}/team.o: ${SOURCE}/team.cpp ${INCLUDE}/team.hpp ${INCLUDE}/player.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/team.cpp -o ${BUILD_DIR}/team.o

${BUILD_DIR}/match_team.o: ${SOURCE}/match_team.cpp ${INCLUDE}/match_team.hpp ${INCLUDE}/constants.hpp
	${CC} ${SOURCE}/match_team.cpp -o ${BUILD_DIR}/match_team.o

${BUILD_DIR}/match.o: ${SOURCE}/match.cpp ${INCLUDE}/match.hpp ${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp \
					  ${INCLUDE}/match_team.hpp
	${CC} ${SOURCE}/match.cpp -o ${BUILD_DIR}/match.o

${BUILD_DIR}/week.o: ${SOURCE}/week.cpp ${INCLUDE}/week.hpp ${INCLUDE}/constants.hpp ${INCLUDE}/player.hpp \
					 ${INCLUDE}/team.hpp ${INCLUDE}/match_team.hpp ${INCLUDE}/match.hpp ${INCLUDE}/structs.hpp
	${CC} ${SOURCE}/week.cpp -o ${BUILD_DIR}/week.o

${BUILD_DIR}/league.o: ${SOURCE}/league.cpp ${INCLUDE}/league.hpp ${INCLUDE}/player.hpp ${INCLUDE}/team.hpp \
					   ${INCLUDE}/match.hpp ${INCLUDE}/week.hpp ${INCLUDE}/prim_funcs.hpp
	${CC} ${SOURCE}/league.cpp -o ${BUILD_DIR}/league.o

${BUILD_DIR}/inp_funcs.o: ${SOURCE}/inp_funcs.cpp ${INCLUDE}/inp_funcs.hpp ${INCLUDE}/league.hpp ${INCLUDE}/player.hpp \
						  ${INCLUDE}/team.hpp ${INCLUDE}/match.hpp ${INCLUDE}/week.hpp ${INCLUDE}/constants.hpp \
						  ${INCLUDE}/prim_funcs.hpp ${INCLUDE}/goal_keeper.hpp
	${CC} ${SOURCE}/inp_funcs.cpp -o ${BUILD_DIR}/inp_funcs.o

${BUILD_DIR}/prim_funcs.o: ${SOURCE}/prim_funcs.cpp ${INCLUDE}/prim_funcs.hpp ${INCLUDE}/constants.hpp \
						   ${INCLUDE}/player.hpp ${INCLUDE}/team.hpp ${INCLUDE}/user.hpp
	${CC} ${SOURCE}/prim_funcs.cpp -o ${BUILD_DIR}/prim_funcs.o

${BUILD_DIR}/squad_player.o: ${SOURCE}/squad_player.cpp ${INCLUDE}/squad_player.hpp ${INCLUDE}/player.hpp \
							 ${INCLUDE}/constants.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/prim_funcs.hpp \
							 ${INCLUDE}/match.hpp
	${CC} ${SOURCE}/squad_player.cpp -o ${BUILD_DIR}/squad_player.o

${BUILD_DIR}/squad.o: ${SOURCE}/squad.cpp ${INCLUDE}/squad.hpp ${INCLUDE}/constants.hpp ${INCLUDE}/player.hpp \
					  ${INCLUDE}/structs.hpp ${INCLUDE}/squad_player.hpp
	${CC} ${SOURCE}/squad.cpp -o ${BUILD_DIR}/squad.o

${BUILD_DIR}/user.o: ${SOURCE}/user.cpp ${INCLUDE}/user.hpp ${INCLUDE}/squad.hpp ${INCLUDE}/constants.hpp \
					 ${INCLUDE}/player.hpp ${INCLUDE}/structs.hpp ${INCLUDE}/squad_player.hpp
	${CC} ${SOURCE}/user.cpp -o ${BUILD_DIR}/user.o

${BUILD_DIR}/system.o: ${SOURCE}/system.cpp ${INCLUDE}/system.hpp ${INCLUDE}/constants.hpp ${INCLUDE}/admin.hpp \
					   ${INCLUDE}/league.hpp ${INCLUDE}/prim_funcs.hpp ${INCLUDE}/inp_funcs.hpp \
					   ${INCLUDE}/player.hpp ${INCLUDE}/team.hpp ${INCLUDE}/match.hpp ${INCLUDE}/week.hpp \
					   ${INCLUDE}/user.hpp ${INCLUDE}/squad.hpp
	${CC} ${SOURCE}/system.cpp -o ${BUILD_DIR}/system.o
			
clean:
	rm -rf ${BUILD_DIR} && mkdir ${BUILD_DIR}