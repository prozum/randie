#include "core/io.h"

#include <stdlib.h>
#include <string.h>

#define DIGITAL_PINS 13
#define DIGITAL_BUFFER_SIZE 5
#define SERIAL_PINS 1
#define SERIAL_BUFFER_SIZE 5

pin_mode_t pin_mode[DIGITAL_PINS];
void set_pin_mode(dpin_t pin, pin_mode_t pm) {
    pin_mode[pin] = pm;
}

pin_mode_t get_pin_mode(dpin_t pin) {
    return pin_mode[pin];
}

//A two dimensional array for storing dvals (i.e. a buffer of some size for each pin)
dval_t digital_buffer[DIGITAL_PINS][DIGITAL_BUFFER_SIZE];
uint8_t dig_buf_cnt [DIGITAL_PINS];

/**
 * Get the latest value written to the specified pin
 * @param pin to read from
 * @return HIGH or LOW depending on what it was set to.
 */
dval_t digital_read(dpin_t pin)
{
    dval_t value = digital_buffer[pin][dig_buf_cnt[pin]];
    dig_buf_cnt[pin] = (dig_buf_cnt[pin] - 1) % DIGITAL_BUFFER_SIZE;

    return value;
}

char uart_val;

char uart_getchar() {
    return uart_val;
}

//A buffer for storing the desired pulses
uint16_t pulse_buffer[DIGITAL_PINS];
/**
 * Set the pulse to return from pulse_in on the specifyied pin
 * @param pin to set pulse for
 * @param pulse
 */
void set_pulse(dpin_t pin, uint16_t pulse) {
    pulse_buffer[pin] = pulse;
}

/**
 * Reads a pulse of state on a given pin
 * @param pin to read from
 * @param state to wait for
 * @param timeout max time in ms to wait
 * @return the length of the pulse
 */
uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout) {
    if(pulse_buffer[pin] > timeout)
        return 0;

    return pulse_buffer[pin];
}

/**
 * Write a specified value to the specified digital pin
 * @param pin to write to
 * @param ps value to write (HIGH or LOW)
 */
void digital_write(dpin_t pin, dval_t ps) {
    //Increments the counter and makes sure it does not exceed buffer size
    dig_buf_cnt[pin] = (dig_buf_cnt[pin] + 1) % DIGITAL_BUFFER_SIZE;
    //Set the value of the digital write buffer to the value specified.
    digital_buffer[pin][dig_buf_cnt[pin]] = ps;
}

/**
 * Get the latest value from a specified pin
 * @param pin the pin to read from
 * @return HIGH or LOW depending on what the pin was set to. Returns -1 is the pin is invalid.
 */
dval_t get_digital_buffer(dpin_t pin) {
    uint8_t prev = (dig_buf_cnt[pin] - 1) % DIGITAL_PINS;

    //Checks that the pin is valid
    if (pin < DIGITAL_PINS && pin >= 0) {
        return digital_buffer[pin][prev];
    }

    return -1;
}

void uart_init() { }

void uart_putchar(char c) { }

//A two-dimensional array for storing char-pointers (i.e. strings)
char *serial_buffer[SERIAL_PINS][SERIAL_BUFFER_SIZE];
uint8_t serial_buf_cnt[SERIAL_BUFFER_SIZE];
/**
 * Write a string to the specified pin
 * @param pin to write to
 * @param out the string to write
 */
void serial_write_string(tx_t pin, char *out) {
    //Increment buffer counter for the given pin
    serial_buf_cnt[pin] = (serial_buf_cnt[pin] + 1) % SERIAL_BUFFER_SIZE;
    uint8_t index = serial_buf_cnt[pin];

    //Checks if a string has been allocated on the buffer slot and clears it in that case
    if(write_buffer[pin][index]) {
        free(write_buffer[pin][index]);
    }

    //Allocates place for a new string and copies it to the buffer
    write_buffer[pin][index] = malloc(strlen(out) * sizeof(char));
    strcpy(write_buffer, out);
}

/**
 * Get the latest string written to the specified pin
 * @param pin to get buffer from
 * @return the latest string written to the pin
 */
char *get_write_buffer(tx_t pin) {
    uint8_t prev;

    //Calculate the index of the latest write
    if(serial_buf_cnt[pin] == 0) {
        prev = SERIAL_BUFFER_SIZE - 1;
    }
    else {
        prev = serial_buf_cnt[pin] - 1;
    }

    return digital_buffer[pin][prev];
}

/**
 * Clears the buffer for a given pin
 * @param pin
 */
void clear_write_buffer(tx_t pin) {
    //Run through the whole buffer
    for (int i = 0; i < SERIAL_BUFFER_SIZE; ++i) {
        //Clear deallocate the string if it was allocated.
        if(serial_buffer[pin][i]) {
            free(serial_buffer[pin][i]);
        }
    }
}

/**
 * read a specified number of bytes from the given pin. This function presents no checks for whether the
 * buffer has been filled or not.
 * @param pin to read from (the buffer is filled by serial_write(rx_t pin)
 * @param len number of bytes to read
 * @return a string from what was filled in the buffer
 */
char* serial_read_string(tx_t pin, int len ) {
    char serial_string_val = malloc(len * sizeof(char));

    //declare integers for index of 2nd and 3rd dimension of the array
    uint8_t index = 0;
    uint8_t it_index = 0;

    //Emulate a continous buffer by copying from the things that have been written via serial
    for (int i = 0; i < len; ++i) {
        //if the char at hand is the string terminator (\0) move on to the next string in the buffer.
        if(serial_buffer[pin][index][it_index] == '\0') {
            index = (index + 1) % SERIAL_BUFFER_SIZE;
            it_index = 0;
        }
        //Copy from the calulated string
        serial_string_val[i] = serial_buffer[pin][index][it_index];
        it_index++;
    }

    return serial_string_val;
}

void uart_putchar(char c/*, FILE *stream*/) {
    loop_until_bit_is_set(UCSR0A, UDRE0); // wait while register is free
    UDR0 = c;
}

char uart_getchar(/*FILE *stream*/) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void serial_write_string(tx_t pin, char *out){
    int i;
    for(i = 0; i < strlen(out)-1;i++) {
        uart_putchar(out[i]);
    }

}

char* serial_read_string(tx_t pin, int len ) {
    char* str = malloc(sizeof(char)*(len+1));

    int i;
    for(i=0;i<len;i++){
        str[i] = uart_getchar();
    }
    str[i+1] = '\0';
    return str;
}

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout)
{
    uint8_t pin_ = dpins[pin];
    uint8_t port_ = dports[pin];
    uint8_t state_ = (state ? pin_ : 0);
    uint16_t width = 0;

    uint16_t loop_count = 0;
    uint16_t loop_max = MS_TO_CLOCK_CYCLES(timeout) / 16; // maybe bitshift with 4 instead

    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    while (((volatile uint8_t)port_to_input[port_]) & pin_ != state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }

        width++;
    }

    return CLOCK_CYCLES_TO_MS(width * 21 + 16);
}

void analog_write(apin_t pin, aval_t out)
{

}

aval_t analog_read(apin_t pin)
{

}