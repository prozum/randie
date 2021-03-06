#include "KalmanDatafusionTest.h"

CPPUNIT_TEST_SUITE_REGISTRATION(KalmanDatafusionTest);

void KalmanDatafusionTest::assert(kalman_state_matrix *state, const fix16_t a, const fix16_t b, const fix16_t p_0) {
    CPPUNIT_ASSERT_MESSAGE("The state was not initialized", state != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("a-value not set in state", a, state->a);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("b-value not set in state", b, state->b);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("p_0-value not set in state", p_0, state->p_k);
    for (int i = 0; i < 2; ++i) {
        CPPUNIT_ASSERT_EQUAL_MESSAGE("A C-value was not set correctly", matrix_get(C, i, 0),
                                     matrix_get(state->C, i, 0));
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            CPPUNIT_ASSERT_EQUAL_MESSAGE("A R-value was not set correctly", matrix_get(R, i, j),
                                         matrix_get(state->R, i, j));
        }
    }
}

void KalmanDatafusionTest::KalmanDFInit_NullStateValidParams_StateMallocedAndInitialized() {
    kalman_state_matrix *state = NULL;

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);
    const fix16_t p_0 = fix16_from_int(10);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);

    assert(state, a, b, p_0);
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateValidParams_StateInitialized() {
    kalman_state_matrix *state;

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);
    const fix16_t p_0 = fix16_from_int(10);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);

    assert(state, a, b, p_0);
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateCNull_StateInitializedWithCzero() {
    kalman_state_matrix *state;

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);
    const fix16_t p_0 = fix16_from_int(10);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, NULL, R);

    assert(state, a, b, p_0);
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateRNull_StateInitializedWithRone() {
    kalman_state_matrix *state;

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);
    const fix16_t p_0 = fix16_from_int(10);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, NULL);

    assert(state, a, b, p_0);
}

void sensor_setup(kalman_state_matrix *state, laser_t *z_0_laser, sonar_t *z_0_sonar, uint8_t sonar_valid,
                  uint16_t laser_reading, uint16_t sonar_reading) {

    z_0_laser->val_front = laser_reading;

    z_0_sonar->value = sonar_reading;
    z_0_sonar->valid = sonar_valid;
    kalman_datafusion_calibrate(state, z_0_laser->val_front, z_0_sonar->value);
}

void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0EQSonar0_xkCloseToBoth() {
    kalman_state_matrix *state;
    laser_t z_0_laser;
    sonar_t z_0_sonar;
    laser_init(&z_0_laser, USB_TX);
    sonar_init(&z_0_sonar, P2, P1);

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);
    const fix16_t r_avg = fix16_from_int(1);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);

    sensor_setup(state, &z_0_laser, &z_0_sonar, 1, fix16_from_int(300), fix16_from_int(300));
    state->x_k = fix16_from_int(60);
    kalman_datafusion_calibrate(state, z_0_laser.val_front, z_0_sonar.value);
    float diff = abs(state->x_k - z_0_laser.val_front);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}

/*void
KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar(){
    kalman_state_matrix *state;

    const float a = 1;
    const float b = 0.6;
    const float r_avg = 1;

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);
    laser_t *z_0_laser = laser_init(USB_TX);
    sonar_t *z_0_sonar = sonar_init(P0, P1);

    sensor_setup(state, z_0_laser, z_0_sonar, 1, 1, 300, 40);

    float diff = abs(state->x_k - z_0_sonar->value);

    std::string msg = "diff = " + std::to_string(diff) + ", r_avg" +
std::to_string(r_avg);
    CPPUNIT_ASSERT_MESSAGE(msg, diff <= r_avg);
}
void
KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser(){
    kalman_state_matrix *state;

    const float a = 1;
    const float b = 0.6;
    const float r_avg = 1;

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);
    laser_t *z_0_laser = laser_init(USB_TX);
    sonar_t *z_0_sonar = sonar_init(P0, P1);

    sensor_setup(state, z_0_laser, z_0_sonar, 1, 0, 300, 480);

    float diff = abs(state->x_k - z_0_laser->front_value);

    std::string msg = "diff = " + std::to_string(diff) + ", r_avg = " +
std::to_string(r_avg);
    CPPUNIT_ASSERT_MESSAGE(msg, diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax(){
    kalman_state_matrix *state;

    const float a = 1;
    const float b = 0.6;

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);
    laser_t *z_0_laser = laser_init(USB_TX);
    sonar_t *z_0_sonar = sonar_init(P0, P1);

    sensor_setup(state, z_0_laser, z_0_sonar, 0, 0, 1000, 1000);
    kalman_datafusion_calibrate(state, z_0_laser->front_value,
z_0_sonar->value);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Filter was not calibrated correctly.",
1000.0f, state->x_k);
}*/

void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev() {
    kalman_state_matrix *state;

    laser_t z_laser;
    sonar_t z_sonar;
    laser_init(&z_laser, USB_TX);
    sonar_init(&z_sonar, P0, P1);

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);

    const fix16_t x_prev = fix16_from_int(370);
    state->x_k = x_prev;
    z_laser.val_front = (uint16_t)fix16_from_int(120);
    z_sonar.value = (uint16_t)fix16_from_int(120);
    z_sonar.valid = (uint8_t)fix16_from_int(1);
    kalman_datafusion_filter(state, z_laser.val_front, z_sonar.value);

    std::string msg = "x_k = " + std::to_string(state->x_k) + ", x_prev = " + std::to_string(x_prev);
    CPPUNIT_ASSERT_MESSAGE(msg, x_prev > state->x_k);
}
void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxGTxprev_xkHigherThanxprev() {
    kalman_state_matrix *state;

    laser_t z_laser;
    sonar_t z_sonar;
    laser_init(&z_laser, USB_TX);
    sonar_init(&z_sonar, P0, P1);

    const fix16_t a = fix16_from_int(1);
    const fix16_t b = fix16_from_float(0.6f);

    state = kalman_datafusion_init(a, b, SENDER_BOARD, C, R);

    const fix16_t x_prev = fix16_from_int(120);
    state->x_k = x_prev;
    z_laser.val_front = 300;
    z_sonar.value = 300;
    kalman_datafusion_filter(state, fix16_from_int(z_laser.val_front), fix16_from_int(z_sonar.value));

    std::string msg = "x_k was supposed to increase, x_k = " + std::to_string(fix16_to_float(state->x_k)) +
                      ", x_prev = " + std::to_string(fix16_to_float(x_prev));
    CPPUNIT_ASSERT_MESSAGE(msg, state->x_k > x_prev);
}

void KalmanDatafusionTest::setUp() {
    R = matrix_constructor(DATAFUSION_UNITS, DATAFUSION_UNITS);

    matrix_set(R, 0, 0, fix16_from_int(1));
    matrix_set(R, 0, 1, fix16_from_int(0));
    matrix_set(R, 1, 0, fix16_from_int(0));
    matrix_set(R, 1, 1, fix16_from_int(1));

    C = matrix_constructor(2, 1);
    matrix_set(C, 0, 0, fix16_from_int(1));
    matrix_set(C, 1, 0, fix16_from_int(1));
}

void KalmanDatafusionTest::tearDown() {
    matrix_destructor(R);
    matrix_destructor(C);
}
