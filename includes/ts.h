#include <stdio.h>
#include <stdint.h>

typedef struct {
    tsHeader_t header;
    uint8_t payload[184]; //TODO: Support adaptation field
} tsPacket_t;

typedef union {
    uint32_t value;
    struct {
        uint32_t syncbyte   : 8;
        uint32_t tei        : 1;
        uint32_t pusi       : 1;
        uint32_t prio       : 1;
        uint32_t pid        : 13;
        uint32_t tsc        : 2;
        uint32_t afc        : 2;
        uint32_t cc         : 4;
    };
} tsHeader_t;

int tsDemux(char *argv[]);
