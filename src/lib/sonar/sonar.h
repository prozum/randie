#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <stdlib.h>
#include <stdint.h>

#include "core/io.h"
#include "core/log.h"

#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

#ifndef MOCK
#include <avr/io.h>
#endif

typedef struct sonar_s {
    dpin_t trig;    // trigger pin
    dpin_t echo;    // receive pin
    uint8_t valid;  // flag to check if latest value is valid
    uint16_t value; // latest reading in cm
} sonar_t;

/**
 * Initializes a sonar_t struct with the specified trigger- and echo-pin
 * @param trig - The trigger-pin the sonar is wired to
 * @param echo - The echo-pin the sonar is wired to
 * @return - A pointer to the allocated struct for the sonar
 */
sonar_t *sonar_init(dpin_t trig, dpin_t echo);

/**
 * Checks if the sound-wave had returned to the sonar yet, sets the ->valid field of the struct to 1 if that is the case
 * @param sonar - A pointer to the sonar_t struct for the sonar
 */
void read_sonar(sonar_t *sonar);
/**
 * Pings the sonar with a specified value
 * @param sonar - A pointer to the sonar_t struct for the sonar
 * @param value - The value to write, either HIGH or LOW
 */
void sonar_ping(sonar_t *sonar, dval_t value);

/**
 * Converts the drones reading in milliseconds to centimeters
 * @param millis - The drone's reading in milliseconds
 * @return - The sonar's reading in centimeters
 */
uint16_t sonar_to_centimeters(uint16_t millis);

#if MOCK
/**
 * Pulse the sonar in a LOW-HIGH-LOW pattern
 * @param sonar - The sonar to ping
 */
void pulse_sonar(sonar_t *sonar);
#endif //MOCK

#endif //RAND_SONAR_H


