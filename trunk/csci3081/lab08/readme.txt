Brian Norman      : 4332223
Ross Noren        : 2401369
Jeremy Vermillion : 4320276
Travis Kroeten    : 3841243


-------------------------------------------------------------------------------
    Compiling
-------------------------------------------------------------------------------

To compile this program simply navigate in a terminal to the directory
containing the source files and Makefile and type "make" without the
quotations. This will build the executable and run some unit tests to make sure
that program is working properly. If any of these fail or the executable fails
to compile you should see an error printed to the terminal output.

There are several other options that you can use when building this program.
These will be briefly described in the following lines.

  $ make all
This is the default, the same as typing make.

  $ make clean
Removes all the object files, executable, and unit test runner.

  $ make doc
Generates the documentation for this project using the doxygen file.

  $ make test-coverage
Will display the coverage percentage of the unit tests.

  $ make run-tests
Generates and runs the unit tests for this project.

  $ make runner
Generates and builds the unit tests but does not run them.

  $ make runner.cpp
Generates the unit tests file but does not build or run it.

You can also build an individual object file by typing make followed by the
object name. Examples:

  $ make Scheduler.o
Will create the Scheduler object file.

  $ make Model.o Refrigerator.o
Will create the Model and Refrigerator object files.


-------------------------------------------------------------------------------
    Running
-------------------------------------------------------------------------------

To run the simulator, the program must first be compiled (see above). After
doing so, there should be a simulator executable file that was created in the
same directory, something like "simulator.exe". If not, there are most likely
errors with the code and the simulator is not fit to run yet. Please contact
the students that created this project and let them know what you encountered.
If you do see the executable file, something like "simulator.exe", then you can
run the program by typing the following: 
  $ ./simulator
This will run the simulator with the default arguments which are 90 ticks and
printing to the "simulator.log" log file.

There are a couple command line arguments that you can use to control how many
ticks the simulator goes through and also where the simulator prints its log
messages too. You can include either one or both of these options but they must
appear in a particular order. A usage message will get printed out and the
program will exit if you fail to comply to the rules for convenience. Here are
some examples:

  $ ./simulator 50
Will make the simulator go through 50 ticks and print to the "simulator.log"
file (the default).

  $ ./simulator temp.log
Will make the simulator go through 90 ticks (the default) and print to the
"temp.log" file.

  $ ./simulator 50 temp.log
Will make the simulator go through 50 ticks and print to the "temp.log" file.