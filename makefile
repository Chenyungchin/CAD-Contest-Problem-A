# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3



# optimized version
exe	:  graph_opt.o
		$(CC) $(OPTFLAGS)  graph_opt.o -o 
# main_opt.o 	   	: src/main.cpp 
# 			$(CC) $(CFLAGS) $<  -o $@
graph_opt.o	: netlist2graph.cpp graph.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@
# clean all the .o and executable files
clean:
		rm -rf *.o 
		

