#ifndef RAND_SINGLE_KALMAN_H
#define RAND_SINGLE_KALMAN_H

#include <stdint.h>
#include <stdlib.h>
#include "log/log.h"

typedef struct kalman_state_t {
    log_sender source_components;

    double a; //How much we assume the next measurement differs from the previous one
    double r; //variance of sensor, i.e. how much a measurement tends to differ from the actual

    double z_k; //Current observation
    double g_k; //kalman gain variable
    double p_k; //prediction error variable

    double x_k; //State variable

} kalman_state;

void kalman_init (kalman_state *state, double _a, double _r, log_sender component);
double kalman_run(kalman_state *state, double z_k);
void kalman_calibrate(kalman_state *initial_state, double z_0);

#endif //RAND_SINGLE_KALMAN_H
