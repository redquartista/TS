#include <string.h>
#include <stdlib.h>
#include "ts.h"

#define TS_PACKET_BYTES 188
#define TS_PACKET_PAYLOAD_BYTES 184

static int readTSPacket(FILE *ts_file, tsPacket_t *ts_packet) {
    fread(ts_packet, TS_PACKET_BYTES, 1, ts_file);
    if(ts_packet->header.syncbyte != 0x47)  {
        printf("\n\nERROR: Packet out of sync. Sync byte != 0x47\n\n");
        return 0;
    }
    char fileName[20]; //TODO: Make it dynamic
    sprintf(fileName, "/tmp/%04x.mp4", (unsigned int) ts_packet->header.pid);
    FILE *f_pid  = fopen(fileName, "a");
    fwrite(ts_packet->payload, TS_PACKET_PAYLOAD_BYTES, 1, f_pid);
    fclose(f_pid);
    return 1;
};

static unsigned long fileSize(FILE *ts_file){
    fseek(ts_file, 0, SEEK_END);
    unsigned long fsize = ftell(ts_file);
    fseek(ts_file, 0, SEEK_SET);
    return fsize;
}

static void printTSPacket(tsPacket_t ts) {
    printf("syncbyte: %02x\n", (unsigned int) ts.header.syncbyte);
    printf("tei: %01x\n", (unsigned int) ts.header.tei);
    printf("pusi: %01x\n", (unsigned int) ts.header.pusi);
    printf("prio: %01x\n", (unsigned int) ts.header.prio);
    printf("pid: %d\n", ts.header.pid);
    printf("tsc: %01x\n", (unsigned int) ts.header.tsc);
    printf("afc: %01x\n", (unsigned int) ts.header.afc);
    printf("cc: %01x\n", (unsigned int) ts.header.cc);
    
    // int i = 0;
    // printf("Payload: ");
    // for(i=0; i<184; i++)
    // printf("02%x", (unsigned int) ts.payload[i]);

    printf("\n");
}

int tsDemux(char *argv[]) {

    char *ts_loc = argv[1];
    FILE *ts_file; 

    ts_file = fopen(ts_loc, "rb");
    
    if(ts_file != NULL) {
        
        uint32_t fsize = fileSize(ts_file);
        uint32_t fsizePackets = fsize / TS_PACKET_BYTES;

        printf("File size = %u bytes, file has %u TS packets\n\n", (unsigned int)fsize, (unsigned int) fsizePackets);
        
        tsPacket_t ts_packet;// = (tsPacket_t *) malloc((fsizePackets * sizeof(tsPacket_t)) + 1);
        memset((void *)&ts_packet, 0, sizeof(tsPacket_t));

        // fread(ts_packet, TS_PACKET_BYTES, fsizePackets, ts_file);

        uint32_t packetcnt = 0;
        while(packetcnt<fsizePackets) {
            if(!readTSPacket(ts_file, &ts_packet)) {
                //free(ts_packet);
                fclose(ts_file);
                return 0;
            }
            printf("\n\npacket #%u\n", packetcnt);
            printTSPacket(ts_packet);
            packetcnt++;
        } 

        int eof = getc(ts_file);
        if( eof != EOF) {
            printf("\n\nERROR: EOF could not be detected\n\n");
            //free(ts_packet);
            fclose(ts_file);
            return 0;
        }
        else {
            printf("\n\nEnd of File\n\n");
            //free(ts_packet);
        }
    }
    else {
        printf("\n\nFile %s does not exist\n\n", ts_loc);
        fclose(ts_file);
        return 0;
    }

    fclose(ts_file);
    return 1;
}