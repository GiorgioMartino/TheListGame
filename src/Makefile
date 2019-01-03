OBJ=main.o partita.o manche.o distance.o
#DEBUG_FLAGS=-D DEBUG_MODE					#Definizione macro DEBUG_MODE
CXXFLAGS=$(DEBUG_FLAGS) -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS=-export-dynamic `pkg-config --libs gtk+-3.0`

EXE: $(OBJ)
	g++ -o EXE $(OBJ) $(LDFLAGS)

-include dependencies

.PHONY: depend clean cleanall

depend:
	g++ -MM *.cc > dependencies
clean:
	rm -f *.o
cleanall:
	rm -f EXE dependencies *.o *~
