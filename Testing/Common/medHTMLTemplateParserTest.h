/*=========================================================================
Program:   Multimod Application Framework
Module:    $RCSfile: medHTMLTemplateParserTest.h,v $
Language:  C++
Date:      $Date: 2012-02-28 16:33:46 $
Version:   $Revision: 1.1.2.2 $
Authors:   Gianluigi Crimi
==========================================================================
Copyright (c) 2002/2004 
CINECA - Interuniversity Consortium (www.cineca.it)
=========================================================================*/

#ifndef __CPP_UNIT_medHTMLTemplateParserTest_H__
#define __CPP_UNIT_medHTMLTemplateParserTest_H__

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>



class medHTMLTemplateParserTest : public CPPUNIT_NS::TestFixture
{
  public:
  
  // CPPUNIT fixture: executed before each test
  void setUp();

  // CPPUNIT fixture: executed after each test
  void tearDown();

  CPPUNIT_TEST_SUITE( medHTMLTemplateParserTest );
  CPPUNIT_TEST( TestConstructorDestuctor );
  CPPUNIT_TEST( TestSetWriteTemplateFile );
  CPPUNIT_TEST( TestSetGetTemplateString );
  CPPUNIT_TEST( TestParse );
  CPPUNIT_TEST_SUITE_END();

  protected:
    
    void TestConstructorDestuctor();
    void TestSetWriteTemplateFile();
    void TestSetGetTemplateString();
    void TestParse();
};


int
main( int argc, char* argv[] )
{
  // Create the event manager and test controller
  CPPUNIT_NS::TestResult controller;

  // Add a listener that colllects test result
  CPPUNIT_NS::TestResultCollector result;
  controller.addListener( &result );        

  // Add a listener that print dots as test run.
  CPPUNIT_NS::BriefTestProgressListener progress;
  controller.addListener( &progress );      

  // Add the top suite to the test runner
  CPPUNIT_NS::TestRunner runner;
  runner.addTest( medHTMLTemplateParserTest::suite());
  runner.run( controller );

  // Print test in a compiler compatible format.
  CPPUNIT_NS::CompilerOutputter outputter( &result, CPPUNIT_NS::stdCOut() );
  outputter.write(); 

  system("pause");


  return result.wasSuccessful() ? 0 : 1;
}

#endif