# makefile for 3081 project phase 1

CPP = g++
CXX_DIR = ../cxxtest
CXX = $(CXX_DIR)/cxxtestgen.pl
CFLAGS = -fprofile-arcs -ftest-coverage
LFLAGS = $(CFLAGS) -lgcov -llog4cxx -lapr-1 -laprutil-1

# Not sure what these do but they make it work...
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) -c -g $(CFLAGS) $<

# Name of the executable
EXECUTABLE = simulator
RUNNER = runner

# Add object files here
OBJECTS = \
	Refrigerator.o \
	Scheduler.o

# Add test files here
TESTS = \
	RefrigeratorTest.h \
	SchedulerTest.h

# Default
all: $(EXECUTABLE) test-coverage
	rm *.gcov

Refrigerator.o: Refrigerator.h Refrigerator.cpp
Scheduler.o: Scheduler.h Scheduler.cpp

# Build the executable
$(EXECUTABLE): $(OBJECTS) simulator.cpp
	$(CPP) -g -o $(EXECUTABLE) $(OBJECTS) simulator.cpp $(LFLAGS) 

# Run the unit tests
run-tests: $(RUNNER)
	./$(RUNNER)

# Build the test runner
$(RUNNER): $(RUNNER).cpp $(OBJECTS)
	$(CPP) -I$(CXX_DIR) -o $(RUNNER) $(OBJECTS) $(RUNNER).cpp -lgcov $(LFLAGS)

# Generate the test runner
$(RUNNER).cpp: $(TESTS)
	$(CXX) --include=LoggerSetup.h --error-printer -o $(RUNNER).cpp $(TESTS)

# Generate documentation
doc: Doxyfile $(OBJECTS)
	doxygen

# Runs gcov to get 
test-coverage: run-tests
	gcov $(OBJECTS) | grep "^File '[^/]" --after-context 1 --color=NEVER

# Clean up
clean: 
	rm -f *.o $(EXECUTABLE) $(RUNNER)* *.gcno *.gcda *.gcov *.log