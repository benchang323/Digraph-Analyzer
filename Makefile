# Makefile
# Flags for the compiler
CC = g++
CFLAGS = -std=c++11 -pedantic -Wall -Wextra -g

# Main targets
# Link files for main executable
digraph_analyzer: digraph_functions.o digraph_analyzer.o
	$(CC) $(CFLAGS) -o digraph_analyzer digraph_functions.o digraph_analyzer.o

# Create object files for digraph_function
digraph_functions.o: digraph_functions.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_functions.cpp

# Create object files for digraph_analyzer
digraph_analyzer.o: digraph_analyzer.cpp digraph_functions.h
	$(CC) $(CFLAGS) -c digraph_analyzer.cpp

# Clean up the directory
clean:
	rm -f *.o digraph_analyzer

# Test targets
# Run valgrind on the main executable with argument r
valgrind_digraph_analyzer_r: digraph_analyzer
	valgrind --leak-check=full ./digraph_analyzer input.txt r

# Run valgrind on the main executable with argument a
valgrind_digraph_analyzer_a: digraph_analyzer
	valgrind --leak-check=full ./digraph_analyzer input.txt a

# Run valgrind on the main executable with argument c
valgrind_digraph_analyzer_c: digraph_analyzer
	valgrind --leak-check=full ./digraph_analyzer input.txt c

# Run the main executable with r argument
run_r_digraph_analyzer: digraph_analyzer
	./digraph_analyzer input.txt r

# Run the main executable with a argument
run_a_digraph_analyzer: digraph_analyzer
	./digraph_analyzer input.txt a
	
# Run the main executable with c argument
run_c_digraph_analyzer: digraph_analyzer
	./digraph_analyzer input.txt c