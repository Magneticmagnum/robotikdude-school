/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "RefrigeratorTest.h"

static RefrigeratorTest suite_RefrigeratorTest;

static CxxTest::List Tests_RefrigeratorTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_RefrigeratorTest( "RefrigeratorTest.h", 12, "RefrigeratorTest", suite_RefrigeratorTest, Tests_RefrigeratorTest );

static class TestDescription_RefrigeratorTest_test_initialConditions : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_initialConditions() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 19, "test_initialConditions" ) {}
 void runTest() { suite_RefrigeratorTest.test_initialConditions(); }
} testDescription_RefrigeratorTest_test_initialConditions;

static class TestDescription_RefrigeratorTest_test_turningOff : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_turningOff() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 28, "test_turningOff" ) {}
 void runTest() { suite_RefrigeratorTest.test_turningOff(); }
} testDescription_RefrigeratorTest_test_turningOff;

static class TestDescription_RefrigeratorTest_test_turningOn : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_turningOn() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 45, "test_turningOn" ) {}
 void runTest() { suite_RefrigeratorTest.test_turningOn(); }
} testDescription_RefrigeratorTest_test_turningOn;

static class TestDescription_RefrigeratorTest_test_power : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_power() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 77, "test_power" ) {}
 void runTest() { suite_RefrigeratorTest.test_power(); }
} testDescription_RefrigeratorTest_test_power;

static class TestDescription_RefrigeratorTest_test_energy : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_energy() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 87, "test_energy" ) {}
 void runTest() { suite_RefrigeratorTest.test_energy(); }
} testDescription_RefrigeratorTest_test_energy;

static class TestDescription_RefrigeratorTest_test_printToLogger : public CxxTest::RealTestDescription {
public:
 TestDescription_RefrigeratorTest_test_printToLogger() : CxxTest::RealTestDescription( Tests_RefrigeratorTest, suiteDescription_RefrigeratorTest, 135, "test_printToLogger" ) {}
 void runTest() { suite_RefrigeratorTest.test_printToLogger(); }
} testDescription_RefrigeratorTest_test_printToLogger;

#include "SchedulerTest.h"

static SchedulerTest suite_SchedulerTest;

static CxxTest::List Tests_SchedulerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_SchedulerTest( "SchedulerTest.h", 10, "SchedulerTest", suite_SchedulerTest, Tests_SchedulerTest );

static class TestDescription_SchedulerTest_test_initialTimeModels : public CxxTest::RealTestDescription {
public:
 TestDescription_SchedulerTest_test_initialTimeModels() : CxxTest::RealTestDescription( Tests_SchedulerTest, suiteDescription_SchedulerTest, 17, "test_initialTimeModels" ) {}
 void runTest() { suite_SchedulerTest.test_initialTimeModels(); }
} testDescription_SchedulerTest_test_initialTimeModels;

static class TestDescription_SchedulerTest_test_addModel : public CxxTest::RealTestDescription {
public:
 TestDescription_SchedulerTest_test_addModel() : CxxTest::RealTestDescription( Tests_SchedulerTest, suiteDescription_SchedulerTest, 29, "test_addModel" ) {}
 void runTest() { suite_SchedulerTest.test_addModel(); }
} testDescription_SchedulerTest_test_addModel;

static class TestDescription_SchedulerTest_test_runScheduler : public CxxTest::RealTestDescription {
public:
 TestDescription_SchedulerTest_test_runScheduler() : CxxTest::RealTestDescription( Tests_SchedulerTest, suiteDescription_SchedulerTest, 49, "test_runScheduler" ) {}
 void runTest() { suite_SchedulerTest.test_runScheduler(); }
} testDescription_SchedulerTest_test_runScheduler;

#include "LoggerTest.h"

static LoggerTest suite_LoggerTest;

static CxxTest::List Tests_LoggerTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_LoggerTest( "LoggerTest.h", 15, "LoggerTest", suite_LoggerTest, Tests_LoggerTest );

static class TestDescription_LoggerTest_test_initialization : public CxxTest::RealTestDescription {
public:
 TestDescription_LoggerTest_test_initialization() : CxxTest::RealTestDescription( Tests_LoggerTest, suiteDescription_LoggerTest, 19, "test_initialization" ) {}
 void runTest() { suite_LoggerTest.test_initialization(); }
} testDescription_LoggerTest_test_initialization;

static class TestDescription_LoggerTest_test_truncation : public CxxTest::RealTestDescription {
public:
 TestDescription_LoggerTest_test_truncation() : CxxTest::RealTestDescription( Tests_LoggerTest, suiteDescription_LoggerTest, 33, "test_truncation" ) {}
 void runTest() { suite_LoggerTest.test_truncation(); }
} testDescription_LoggerTest_test_truncation;

static class TestDescription_LoggerTest_test_print : public CxxTest::RealTestDescription {
public:
 TestDescription_LoggerTest_test_print() : CxxTest::RealTestDescription( Tests_LoggerTest, suiteDescription_LoggerTest, 58, "test_print" ) {}
 void runTest() { suite_LoggerTest.test_print(); }
} testDescription_LoggerTest_test_print;

#include <cxxtest/Root.cpp>
