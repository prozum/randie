# our own library
generate_avr_library(matrix
        MOCK
        BOARD uno
        SRCS matrix.c
        LIBS core libfixmath)