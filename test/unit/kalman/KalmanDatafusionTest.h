#pragma once

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "kalman/kalman-datafusion.h"
#include "laser/laser.h"
#include "sonar/sonar.h"
}

class KalmanDatafusionTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(KalmanDatafusionTest);
    CPPUNIT_TEST(KalmanDFInit_NullStateValidParams_StateMallocedAndInitialized);
    CPPUNIT_TEST(KalmanDFInit_ValidStateValidParams_StateInitialized);
    CPPUNIT_TEST(KalmanDFInit_ValidStateCNull_StateInitializedWithCzero);
    CPPUNIT_TEST(KalmanDFInit_ValidStateRNull_StateInitializedWithRone);
    CPPUNIT_TEST(KalmanDFCalibrate_ValidStateLaser0EQSonar0_xkCloseToBoth);
    /*CPPUNIT_TEST(KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar);
    CPPUNIT_TEST(KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser);
    CPPUNIT_TEST(KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax);*/
    CPPUNIT_TEST(KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev);
    CPPUNIT_TEST(KalmanDFFilter_SonarxEQLaserxGTxprev_xkHigherThanxprev);
    CPPUNIT_TEST_SUITE_END();

  private:
    matrix_t *R, *C;
    void assert(kalman_state_matrix *state, const fix16_t a, const fix16_t b, const fix16_t p_0);

  public:
    void setUp();
    void tearDown();

    void KalmanDFInit_NullStateValidParams_StateMallocedAndInitialized();

    void KalmanDFInit_ValidStateValidParams_StateInitialized();

    void KalmanDFInit_ValidStateCNull_StateInitializedWithCzero();

    void KalmanDFInit_ValidStateRNull_StateInitializedWithRone();

    void KalmanDFCalibrate_ValidStateLaser0EQSonar0_xkCloseToBoth();

    /*void
    KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar();
    void KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser();
    void KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax();*/

    void KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev();

    void KalmanDFFilter_SonarxEQLaserxGTxprev_xkHigherThanxprev();
};
