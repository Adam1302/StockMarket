CXX = g++
CXXFLAGS = -std=c++14 -MMD
OBJECTS = controller.o main.o observer.o stock.o stockTrader.o subject.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = stockMarketSim

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -lX11 -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
