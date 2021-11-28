#include "ts.h"

#define TS_PACKET_BYTES 188

static void readTSPacket(FILE *ts_file, tsPacket_t *ts_packet) {
      fread(ts_packet, 1, TS_PACKET_BYTES, ts_file);
};

static void printTSPacket(tsPacket_t ts) {

    int i = 0;
    printf("\nThe TS packet looks like this: \n");
    printf("syncbyte: %02x\n", (unsigned int) ts.header.syncbyte);
    printf("tei: %01x\n", (unsigned int) ts.header.tei);
    printf("pusi: %01x\n", (unsigned int) ts.header.pusi);
    printf("prio: %01x\n", (unsigned int) ts.header.prio);
    printf("pid: %d\n", ts.header.pid);
    printf("tsc: %01x\n", (unsigned int) ts.header.tsc);
    printf("afc: %01x\n", (unsigned int) ts.header.afc);
    printf("cc: %01x\n", (unsigned int) ts.header.cc);
    printf("Payload: ");

    for(i=0; i<184; i++)
        printf("02%x", (unsigned int) ts.payload[i]);
}

int tsDemux(char *argv[]) {

    char *ts_loc = argv[1];
    FILE *ts_file; 
    tsPacket_t ts_packet;
    
    ts_file = fopen(ts_loc, "rb");
    
    if(ts_file != NULL) {
        readTSPacket(ts_file, &ts_packet);
        printTSPacket(ts_packet);
    }
    else {
        printf("\n\nFile %s does not exist\n\n", ts_loc);
        return 0;
    }
    fclose(ts_file);
	return 1;
}