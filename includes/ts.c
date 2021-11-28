#include <string.h>
#include <stdlib.h>
#include "ts.h"

#define TS_PACKET_BYTES 188

static void readTSPacket(FILE *ts_file, tsPacket_t *ts_packet) {
      fread(ts_packet, 1, TS_PACKET_BYTES, ts_file);
};

static unsigned long fileSize(FILE *ts_file){

    fseek(ts_file, 0, SEEK_END);
    unsigned long fsize = ftell(ts_file);
    fseek(ts_file, 0, SEEK_SET);
    return fsize;
}
static void printTSPacket(tsPacket_t ts) {

    printf("%02x\n", (unsigned int) ts.header.syncbyte);

//     int i = 0;
//     printf("\nThe TS packet looks like this: \n");
//     printf("syncbyte: %02x\n", (unsigned int) ts.header.syncbyte);
//     printf("tei: %01x\n", (unsigned int) ts.header.tei);
//     printf("pusi: %01x\n", (unsigned int) ts.header.pusi);
//     printf("prio: %01x\n", (unsigned int) ts.header.prio);
//     printf("pid: %d\n", ts.header.pid);
//     printf("tsc: %01x\n", (unsigned int) ts.header.tsc);
//     printf("afc: %01x\n", (unsigned int) ts.header.afc);
//     printf("cc: %01x\n", (unsigned int) ts.header.cc);
    
// /*    printf("Payload: ");
//     for(i=0; i<184; i++)
//         printf("02%x", (unsigned int) ts.payload[i]);*/

//     printf("\n");
}

int tsDemux(char *argv[]) {

    char *ts_loc = argv[1];
    FILE *ts_file; 
    

    
    // uint32_t i = 0;

    ts_file = fopen(ts_loc, "rb");
    
    if(ts_file != NULL) {
        
        uint32_t fsize = fileSize(ts_file);
        uint32_t fsizePackets = fsize / TS_PACKET_BYTES;
        uint32_t packetcnt = 0;

        printf("File size = %u bytes, file has %u TS packets\n\n", (unsigned int)fsize, (unsigned int) fsizePackets);
        
        tsPacket_t *ts_packet = (tsPacket_t *) malloc((fsizePackets * sizeof(tsPacket_t)) + 1);
        memset((void *)ts_packet, 0, (fsizePackets * sizeof(tsPacket_t)));

        while( packetcnt < fsizePackets) {
            readTSPacket(ts_file, &ts_packet[packetcnt]);
            printTSPacket(ts_packet[packetcnt]);
            packetcnt++;
        } 
    }
    else {
        printf("\n\nFile %s does not exist\n\n", ts_loc);
        return 0;
    }
    fclose(ts_file);
	return 1;
}