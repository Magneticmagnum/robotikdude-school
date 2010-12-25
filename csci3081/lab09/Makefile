# makefile for 3081 project phase 1

CPP = g++
CXX_DIR = ../cxxtest
CXX = $(CXX_DIR)/cxxtestgen.pl

# Not sure what these do but they make it work...
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) -c -g -fprofile-arcs -ftest-coverage $<

# Name of the executable
EXECUTABLE = simulator
RUNNER = runner

# Add object files here
OBJECTS = \
	Model.o \
	Oven.o \
	Stove.o \
	Television.o \
	Toaster.o \
	WaterHeater.o \
	Refrigerator.o \
	Scheduler.o

# Add test files here
TESTS = \
	ModelTest.h \
	RefrigeratorTest.h \
	SchedulerTest.h \
	WaterHeaterTest.h

# Default
all: $(EXECUTABLE) test-coverage

# Indavidual object files
Model.o: Model.h Model.cpp
Refrigerator.o: Refrigerator.h Refrigerator.cpp
Scheduler.o: Scheduler.h Scheduler.cpp
Oven.o: Oven.h Oven.cpp
Stove.o: Stove.h Stove.cpp
Television.o: Television.h Television.cpp
Toaster.o: Toaster.h Toaster.cpp
WaterHeater.o: WaterHeater.h WaterHeater.cpp

# Build the executable
$(EXECUTABLE): $(OBJECTS) simulator.cpp
	$(CPP) -g -o $(EXECUTABLE) $(OBJECTS) simulator.cpp -lgcov

# Run the unit tests
run-tests: $(RUNNER)
	./$(RUNNER)

# Build the test runner
runner: $(RUNNER).cpp $(OBJECTS)
	$(CPP) -I$(CXX_DIR) -o $(RUNNER) $(OBJECTS) $(RUNNER).cpp -lgcov

# Generate the test runner
runner.cpp: $(TESTS)
	$(CXX) --error-printer -o $(RUNNER).cpp $(TESTS)

# Generate documentation
doc: Doxyfile $(OBJECTS)
	doxygen

# Runs gcov to get 
test-coverage: run-tests
	gcov $(OBJECTS) | grep "^File '[^/]" --after-context 1 --color=NEVER > test_coverage.txt
	mkdir -p gcov
	mv *.gcov gcov

# Clean up
clean: 
	rm -f *.o $(EXECUTABLE) $(RUNNER)* *.gcno *.gcda *.gcov test_coverage.txt