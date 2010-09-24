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
#include "QueueTest.h"

static QueueTest suite_QueueTest;

static CxxTest::List Tests_QueueTest = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_QueueTest( "QueueTest.h", 7, "QueueTest", suite_QueueTest, Tests_QueueTest );

static class TestDescription_QueueTest_test_global_Queue_Queue : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_test_global_Queue_Queue() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 15, "test_global_Queue_Queue" ) {}
 void runTest() { suite_QueueTest.test_global_Queue_Queue(); }
} testDescription_QueueTest_test_global_Queue_Queue;

static class TestDescription_QueueTest_testGet_EmptyQueue : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testGet_EmptyQueue() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 26, "testGet_EmptyQueue" ) {}
 void runTest() { suite_QueueTest.testGet_EmptyQueue(); }
} testDescription_QueueTest_testGet_EmptyQueue;

static class TestDescription_QueueTest_testGet_Size : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testGet_Size() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 46, "testGet_Size" ) {}
 void runTest() { suite_QueueTest.testGet_Size(); }
} testDescription_QueueTest_testGet_Size;

static class TestDescription_QueueTest_testGet_FIFO : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testGet_FIFO() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 65, "testGet_FIFO" ) {}
 void runTest() { suite_QueueTest.testGet_FIFO(); }
} testDescription_QueueTest_testGet_FIFO;

static class TestDescription_QueueTest_testGet_Values : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testGet_Values() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 83, "testGet_Values" ) {}
 void runTest() { suite_QueueTest.testGet_Values(); }
} testDescription_QueueTest_testGet_Values;

static class TestDescription_QueueTest_testPut_Size : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testPut_Size() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 102, "testPut_Size" ) {}
 void runTest() { suite_QueueTest.testPut_Size(); }
} testDescription_QueueTest_testPut_Size;

static class TestDescription_QueueTest_testSize : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_testSize() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 118, "testSize" ) {}
 void runTest() { suite_QueueTest.testSize(); }
} testDescription_QueueTest_testSize;

static class TestDescription_QueueTest_test_global_Queue_QueueCopy_Size : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_test_global_Queue_QueueCopy_Size() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 152, "test_global_Queue_QueueCopy_Size" ) {}
 void runTest() { suite_QueueTest.test_global_Queue_QueueCopy_Size(); }
} testDescription_QueueTest_test_global_Queue_QueueCopy_Size;

static class TestDescription_QueueTest_test_global_Queue_QueueCopy_Contents : public CxxTest::RealTestDescription {
public:
 TestDescription_QueueTest_test_global_Queue_QueueCopy_Contents() : CxxTest::RealTestDescription( Tests_QueueTest, suiteDescription_QueueTest, 172, "test_global_Queue_QueueCopy_Contents" ) {}
 void runTest() { suite_QueueTest.test_global_Queue_QueueCopy_Contents(); }
} testDescription_QueueTest_test_global_Queue_QueueCopy_Contents;

#include <cxxtest/Root.cpp>
