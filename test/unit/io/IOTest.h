#pragma once

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "avr_mcu_section.h"
#include "Tools.h"
}

#define ATMEGA328p "atmega328p"
#define F_CPU 16000000
#define STEPS 100000
#define INVALID_DDR "INVALID DDRx"
#define INVALID_PORT "INVALID PORTx"
#define INVALID_PIN "INVALID PINx"
#define WRONG_REG "CHANGED WRONG REGISTER"
#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

class IOTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(IOTest);

    CPPUNIT_TEST(SetPinMode_Pin0SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin0SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin7SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin7SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin8SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin8SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin13SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin13SetOUT_ExpectOUT);
    // CPPUNIT_TEST(SetPinMode_Pin13SetLessThan0_ExpectNoChange);
    // CPPUNIT_TEST(SetPinMode_Pin13SetHigherThan1_ExpectNoChange);

    CPPUNIT_TEST(WritePin_Pin0WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin7WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin8WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin13WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin0WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin7WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin8WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin13WriteHIGH_ExpectHIGH);
    // CPPUNIT_TEST(WritePin_Pin13WriteHigherThan1_ExpectNoChange);
    // CPPUNIT_TEST(WritePin_Pin13WriteLessThan0_ExpectNoChange);

    CPPUNIT_TEST(ReadPin_Pin0ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin7ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin8ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin13ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin0ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin7ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin8ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin13ReadHIGH_ExpectHIGH);

    CPPUNIT_TEST_SUITE_END();

  public:
    void SetPinMode_Pin0SetIN_ExpectIN();

    void SetPinMode_Pin7SetIN_ExpectIN();

    void SetPinMode_Pin8SetIN_ExpectIN();

    void SetPinMode_Pin13SetIN_ExpectIN();

    void SetPinMode_Pin0SetOUT_ExpectOUT();

    void SetPinMode_Pin7SetOUT_ExpectOUT();

    void SetPinMode_Pin8SetOUT_ExpectOUT();

    void SetPinMode_Pin13SetOUT_ExpectOUT();

    void SetPinMode_Pin13SetHigherThan1_ExpectNoChange();

    void SetPinMode_Pin13SetLessThan0_ExpectNoChange();

    void WritePin_Pin0WriteLOW_ExpectLOW();

    void WritePin_Pin7WriteLOW_ExpectLOW();

    void WritePin_Pin8WriteLOW_ExpectLOW();

    void WritePin_Pin13WriteLOW_ExpectLOW();

    void WritePin_Pin0WriteHIGH_ExpectHIGH();

    void WritePin_Pin7WriteHIGH_ExpectHIGH();

    void WritePin_Pin8WriteHIGH_ExpectHIGH();

    void WritePin_Pin13WriteHIGH_ExpectHIGH();

    void WritePin_Pin13WriteHigherThan1_ExpectNoChange();

    void WritePin_Pin13WriteLessThan0_ExpectNoChange();

    void ReadPin_Pin0ReadLOW_ExpectLOW();

    void ReadPin_Pin7ReadLOW_ExpectLOW();

    void ReadPin_Pin8ReadLOW_ExpectLOW();

    void ReadPin_Pin13ReadLOW_ExpectLOW();

    void ReadPin_Pin0ReadHIGH_ExpectHIGH();

    void ReadPin_Pin7ReadHIGH_ExpectHIGH();

    void ReadPin_Pin8ReadHIGH_ExpectHIGH();

    void ReadPin_Pin13ReadHIGH_ExpectHIGH();
};