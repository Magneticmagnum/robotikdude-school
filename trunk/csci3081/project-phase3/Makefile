# makefile for 3081 project phase 1

OS = $(shell uname)
CPP = g++

CXX_DIR = ../cxxtest
SRC_DIR = src
INCLUDE_DIR = include
OBJ_DIR = obj
TEST_DIR = test
GCOV_DIR = gcov

CXX = $(CXX_DIR)/cxxtestgen.pl
CFLAGS = -fprofile-arcs -ftest-coverage -I$(INCLUDE_DIR)
LFLAGS = $(CFLAGS) -lgcov -lapr-1 -laprutil-1 -llog4cxx
ifeq (CYGWIN, $(findstring CYGWIN,$(OS)))
	LFLAGS = $(CFLAGS) -L/usr/local/lib -lgcov -lapr-1 -laprutil-1 -llog4cxx -lapr-1.dll -laprutil-1.dll
endif

#vpath %.cpp $(SRC_DIR)

# Not sure what these do but they make it work...
.SUFFIXES : .o .cpp
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cpp
	$(CPP) $< -c -g $(CFLAGS) -o $@

# Name of the executable
EXECUTABLE = simulator
RUNNER = runner

# Add object files here
OBJECTS = \
	Model.o \
	ModelFactory.o \
	Scheduler.o \
	House.o \
	Bath.o \
	Dishwasher.o \
	Microwave.o \
	Oven.o \
	PersonB.o \
	Refrigerator.o \
	Shower.o \
	Stove.o \
	Television.o \
	Toaster.o \
	WaterHeater.o \
	Random.o


# Add test files here
TESTS = \
	ModelTest.h \
	ModelFactoryTest.h \
	SchedulerTest.h \
	HouseTest.h \
	BathTest.h \
	DishwasherTest.h \
	MicrowaveTest.h \
	OvenTest.h \
	PersonTestB.h \
	RefrigeratorTest.h \
	ShowerTest.h \
	StoveTest.h \
	TelevisionTest.h \
	ToasterTest.h \
	WaterHeaterTest.h \
	RandomTest.h


FLDR_TESTS = $(addprefix $(TEST_DIR)/, $(TESTS))
FLDR_OBJECTS = $(addprefix $(OBJ_DIR)/, $(OBJECTS))

# Default
all: $(EXECUTABLE) test-coverage

# Indavidual object files
Model.o: Model.h Model.cpp
ModelFactory.o: ModelFactory.h ModelFactory.cpp
Scheduler.o: Scheduler.h Scheduler.cpp
House.o: House.h House.cpp
Bath.o: Bath.h Bath.cpp
Dishwasher.o: Dishwasher.h Dishwasher.cpp
Microwave.o: Microwave.h Microwave.cpp
Oven.o: Oven.h Oven.cpp
Person.o: Person.h Person.cpp
PersonB.o: PersonB.h PersonB.cpp
Refrigerator.o: Refrigerator.h Refrigerator.cpp
Shower.o: Shower.h Shower.cpp
Stove.o: Stove.h Stove.cpp
Television.o: Television.h Television.cpp
Toaster.o: Toaster.h Toaster.cpp
WaterHeater.o: WaterHeater.h WaterHeater.cpp
Random.o: Random.h Random.cpp

# Build the executable
$(EXECUTABLE): $(FLDR_OBJECTS) simulator.cpp
	$(CPP) -o $(EXECUTABLE) $(FLDR_OBJECTS) simulator.cpp $(LFLAGS)
	mv $(EXECUTABLE).gcno $(OBJ_DIR)

# Run the unit tests
run-tests: $(RUNNER)
	rm -f $(OBJ_DIR)/*.gcda
	./$(RUNNER)
	mv -f *.gcda $(OBJ_DIR)

# Build the test runner
$(RUNNER): $(RUNNER).cpp $(FLDR_OBJECTS)
	$(CPP) -I$(CXX_DIR) -o $(RUNNER) $(FLDR_OBJECTS) $(RUNNER).cpp  $(LFLAGS)
	mv $(RUNNER).gcno $(OBJ_DIR)

# Generate the test runner
$(RUNNER).cpp: $(FLDR_TESTS)
	$(CXX) --error-printer --include=$(TEST_DIR)/LoggerSetup.h -o $(RUNNER).cpp $(FLDR_TESTS)

# Generate documentation
doc: Doxyfile $(FLDR_OBJECTS)
	doxygen

# Runs gcov to get test coverage details
test-coverage: run-tests
	gcov -o $(OBJ_DIR) $(OBJECTS) | grep "^File '[^/]" --after-context 1 --color=NEVER > COVERAGE.txt
	mkdir -p $(GCOV_DIR)
	mv *.gcov $(GCOV_DIR)

# Clean up
clean: 
	rm -fr $(EXECUTABLE) $(RUNNER)* $(OBJ_DIR)/* $(GCOV_DIR) COVERAGE.txt *.log