# makefile for 3081 lab 6

CPP = g++
CXX_DIR = ../cxxtest
CXX = $(CXX_DIR)/cxxtestgen.pl

# Not sure what these do but they make it work...
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) -c -g -fprofile-arcs -ftest-coverage $<

# Name of the executable
RUNNER = runner

# Add object files here
OBJECTS = \
	Stack.o

# Add test files here
TESTS = \
	StackTest.h

# Default
all: test-coverage
	rm *.gcov

# Indavidual object files
Stack.o: Stack.cpp Stack.h

# Run the unit tests
run-tests: $(RUNNER)
	./$(RUNNER)

# Build the test runner
$(RUNNER): $(RUNNER).cpp $(OBJECTS)
	$(CPP) -I$(CXX_DIR) -o $(RUNNER) $(OBJECTS) $(RUNNER).cpp -lgcov

# Generate the test runner
runner.cpp: $(TESTS)
	$(CXX) --error-printer -o $(RUNNER).cpp $(TESTS)

# Runs gcov to get 
test-coverage: run-tests
	gcov $(OBJECTS) | grep "^File '[^/]" --after-context 1 --color=NEVER

# Clean up
clean: 
	rm *.o $(EXECUTABLE) $(RUNNER)* *.gcno *.gcda *.gcov