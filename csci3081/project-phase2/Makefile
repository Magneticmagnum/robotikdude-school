# makefile for 3081 project phase 1

OS = $(shell uname)
CPP = g++
CXX_DIR = ../cxxtest
CXX = $(CXX_DIR)/cxxtestgen.pl
CFLAGS = -fprofile-arcs -ftest-coverage
LFLAGS = $(CFLAGS) -lgcov -lapr-1 -laprutil-1 -llog4cxx
ifeq (CYGWIN, $(findstring CYGWIN,$(OS)))
	LFLAGS = $(CFLAGS) -L/usr/local/lib -lgcov -lapr-1 -laprutil-1 -llog4cxx -lapr-1.dll -laprutil-1.dll
endif

# Not sure what these do but they make it work...
.SUFFIXES : .o .cpp .c
.cpp.o :
	$(CPP) -c -g $(CFLAGS) $<

# Name of the executable
EXECUTABLE = simulator
RUNNER = runner

# Add object files here
OBJECTS = \
	Model.o \
	Scheduler.o \
	Dishwasher.o \
	Microwave.o \
	Oven.o \
	PersonB.o \
	Refrigerator.o \
	Stove.o \
	Television.o \
	Toaster.o \
	WaterHeater.o

#Person.o

# Add test files here
TESTS = \
	ModelTest.h \
	SchedulerTest.h \
	DishwasherTest.h \
	MicrowaveTest.h \
	OvenTest.h \
	PersonTestB.h \
	RefrigeratorTest.h \
	StoveTest.h \
	TelevisionTest.h \
	ToasterTest.h \
	WaterHeaterTest.h

#PersonTest.h

# Default
all: $(EXECUTABLE) test-coverage

# Indavidual object files
Scheduler.o: Scheduler.h Scheduler.cpp
Model.o: Model.h Model.cpp
Dishwasher.o: Dishwasher.h Dishwasher.cpp
Microwave.o: Microwave.h Microwave.cpp
Oven.o: Oven.h Oven.cpp
#Person.o: Person.h Person.cpp
PersonB.o: PersonB.h PersonB.cpp
Refrigerator.o: Refrigerator.h Refrigerator.cpp
Stove.o: Stove.h Stove.cpp
Television.o: Television.h Television.cpp
Toaster.o: Toaster.h Toaster.cpp
WaterHeater.o: WaterHeater.h WaterHeater.cpp

# Build the executable
$(EXECUTABLE): $(OBJECTS) simulator.cpp
	$(CPP) -o $(EXECUTABLE) $(OBJECTS) simulator.cpp $(LFLAGS)

# Run the unit tests
run-tests: $(RUNNER)
	rm -f *.gcda
	./$(RUNNER)

# Build the test runner
$(RUNNER): $(RUNNER).cpp $(OBJECTS)
	$(CPP) -I$(CXX_DIR) -o $(RUNNER) $(OBJECTS) $(RUNNER).cpp  $(LFLAGS)

# Generate the test runner
$(RUNNER).cpp: $(TESTS)
	$(CXX) --error-printer --include=LoggerSetup.h -o $(RUNNER).cpp $(TESTS)

# Generate documentation
doc: Doxyfile $(OBJECTS)
	doxygen

# Runs gcov to get test coverage details
test-coverage: run-tests
	gcov $(OBJECTS) | grep "^File '[^/]" --after-context 1 --color=NEVER > COVERAGE.txt
	mkdir -p gcov
	mv *.gcov gcov

# Clean up
clean: 
	rm -fr *.o $(EXECUTABLE) $(RUNNER)* *.gcno *.gcda gcov COVERAGE.txt *.log