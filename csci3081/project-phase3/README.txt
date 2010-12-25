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
Example:
	(in model configuration "model.config":)
	Person anne
	(at command line:)
	$ ./simulator -d 20 model.config anne.config
will run the simulator for 20 days using model specifications from model.config
and state configurations for the Person anne from anne.config.
  $ make run-tests
Generates and runs the unit tests for this project.

  $ make runner
Generates and builds the unit tests but does not run them.

  $ make runner.cpp
Generates the unit tests file but does not build or run it.


-------------------------------------------------------------------------------
    Running
-------------------------------------------------------------------------------

In order to run the simulation, you will need to include at least two
additional files: one for the models' configurations, and at least one for
the Person's states.

For information about how to write a configuration file, see the included
sample.config, as well as the phase2.config and phase2.state.  Information
about what is configurable for each model can be found in ConfigurationOptions.h.
In general, a line in the model configuration file should look like:
<Model> <model name> <attribute name> <value>
with only spaces seperating each of the fields.

For example, to configure the Oven model's bake time, you would use:
Oven theoven bake-time 40.0

Note: the name of Person must be included in the model configuration file, and
should match the name of the state file provided for that person.

To run the simulator, the program must first be compiled (see above). After
doing so, there should be a simulator executable file that was created in the
same directory, something like "simulator.exe". If not, there are most likely
errors with the code and the simulator is not fit to run yet. Please contact
the students that created this project and let them know what you encountered.
If you do see the executable file, something like "simulator.exe", then you can
run the program by typing the following: 
  $ ./simulator -d <# of days> <model config file> <Person1 config file> <Person2
  			 config file> ...
This will run the simulator for the specified number of days, use the specified
configuration files for the models and Person(s), and print to the "simulator.log"
log file.

If "-d <# of days>" is ommitted, the simulation will run for the default number of
days, which is 10.

Example:
	(in model configuration "model.config":)
	Person anne
	(at command line:)
	$ ./simulator -d 20 model.config anne.config
will run the simulator for 20 days using model specifications from model.config
and state configurations for the Person "anne" from anne.config.

To run the simulation like it was phase 2 with the included phase 2 config and
state files:
	$ ./simulator -d 10 phase2.config phase2.state
