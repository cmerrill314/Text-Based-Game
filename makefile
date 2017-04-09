CXX = main.cpp
CXX += Game.cpp
CXX += Game.hpp
CXX += Space.cpp
CXX += Space.hpp
CXX += Chambers.cpp
CXX += Chambers.hpp
CXX += Dungeon.cpp
CXX += Dungeon.hpp
CXX += GrandHall.cpp
CXX += GrandHall.hpp
CXX += Library.cpp
CXX += Library.hpp
CXX += Tower.cpp
CXX += Tower.hpp
CXX += Treasury.cpp
CXX += Treasury.hpp

PROG1 = thief
PROGS = ${PROG1}

default:
	g++ ${CXX} -o thief

clean:
	rm -f ${PROGS} *.o *~