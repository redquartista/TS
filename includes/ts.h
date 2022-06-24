#include <stdio.h>
#include <stdint.h>

#define TS_PACKET_BYTES                 (uint32_t) 188ul
#define TS_PACKET_PAYLOAD_BYTES         (uint32_t) 184ul

#define VIDEO_PID                       (uint32_t) 0x424ul
#define AUDIO_PID                       (uint32_t) 0x428ul

/**
 * @brief An enum to codify error and success states
 * 
 */
typedef enum {
    error_e = 0,
    success_e
} status_e;

/**
 * @brief A structure to contain the header of a transport packet
 * 
 */
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

/**
 * @brief A structure to capture transport stream packet
 * 
 */
typedef struct {
    tsHeader_t header;
    uint8_t payload[184]; //TODO: Support adaptation field
} tsPacket_t;

/**
 * @brief The function demultiplexes a transport stream and generates separate audio and video file
 * 
 * @param argv arguments passed on command line to indicate <path to input .ts file> <path to output .mp4 file> <path to .wav file>
 * @return status_e return success or error
 */
status_e tsDemux(char *argv[]);
