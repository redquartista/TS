#include <string.h>
#include <stdlib.h>
#include "ts.h"

static uint32_t getAudioPID() {

    /*TODO: Find how to get audio PID*/
    uint32_t pid = AUDIO_PID;
    return pid;
}

static uint32_t getVideoPID() {

    /*TODO: Find how to get audio PID*/
    uint32_t pid = VIDEO_PID;

    return pid;
}

static status_e proecssTSPacket(FILE *ts_file, tsPacket_t *ts_packet, char *video_loc, char* audio_loc, uint32_t videoPID, uint32_t audioPID) {
    
    fread(ts_packet, TS_PACKET_BYTES, 1, ts_file);
    
    //Return error of syncbyte is not found
    if(ts_packet->header.syncbyte != 0x47)  {
        printf("\n\nERROR: Packet out of sync. Sync byte != 0x47\n\n");
        return error_e;
    }

    FILE *f_pid;

    //identify the type of packet based on the PID and open the respective output file in append mode
    if(ts_packet->header.pid == audioPID){
        f_pid = fopen(audio_loc, "a");
    }
    else if(ts_packet->header.pid == videoPID){
        f_pid  = fopen(video_loc, "a");
    }
    else
    {
        //TODO: Identify and read tables.
        return success_e;
    }

    //TODO: Identify and remove adaptation field
    //write the payload to the appropriate file
    fwrite(ts_packet->payload, TS_PACKET_PAYLOAD_BYTES, 1, f_pid);
    fclose(f_pid);
    return success_e;
};

static unsigned long fileSize(FILE *ts_file){
    fseek(ts_file, 0, SEEK_END);
    unsigned long fsize = ftell(ts_file);
    fseek(ts_file, 0, SEEK_SET);
    return fsize;
}

#ifdef PRINT_PACKETS

static void printTSPacket(tsPacket_t ts) {
    printf("syncbyte: %02x\n", (unsigned int) ts.header.syncbyte);
    printf("tei: %01x\n", (unsigned int) ts.header.tei);
    printf("pusi: %01x\n", (unsigned int) ts.header.pusi);
    printf("prio: %01x\n", (unsigned int) ts.header.prio);
    printf("pid: %d\n", ts.header.pid);
    printf("tsc: %01x\n", (unsigned int) ts.header.tsc);
    printf("afc: %01x\n", (unsigned int) ts.header.afc);
    printf("cc: %01x\n", (unsigned int) ts.header.cc);
    
    printf("Payload: ");

    for(int i=0; i<184; i++)
        printf("02%x", (unsigned int) ts.payload[i]);

    printf("\n");
}
#endif

status_e tsDemux(char *argv[]) {

    char *ts_loc = argv[1], *video_loc = argv[2], *audio_loc = argv[3];
    
    //Open the transport stream file in binary read mode
    FILE *ts_file = fopen(ts_loc, "rb");
    
    if(ts_file != NULL) {
            
        FILE *loc_file; 

        /*Open destination files. Overwrite if already exists.*/    
        loc_file  = fopen(video_loc, "w");
        if(loc_file == NULL) {
            printf("Error opening %s", video_loc);
            return error_e;
        }
        fclose(loc_file);

        loc_file  = fopen(audio_loc, "w");
        if(loc_file == NULL) {
            printf("Error opening %s", audio_loc);
            return error_e;
        }

        fclose(loc_file);

        //Calculate how many TS packets are contained in the .ts file
        uint32_t fsize = fileSize(ts_file);
        uint32_t fsizePackets = fsize / TS_PACKET_BYTES;

        printf("File size = %u bytes, file has %u TS packets\n\n", (unsigned int)fsize, (unsigned int) fsizePackets);
        
        //Declare and initialze a .ts packet to 0
        tsPacket_t ts_packet;
        memset((void *)&ts_packet, 0, sizeof(tsPacket_t));

        uint32_t packetcnt = 0;
        uint32_t audioPID = getAudioPID();
        uint32_t videoPID = getVideoPID();
        
        //Process packet by packet and group into audio and video packet
        while(packetcnt<fsizePackets) {
            if(!proecssTSPacket(ts_file, &ts_packet, video_loc, audio_loc, videoPID, audioPID)) {
                fclose(ts_file);
                return error_e;
            }

#ifdef PRINT_PACKETS
            printf("\n\npacket #%u\n", packetcnt);
            printTSPacket(ts_packet);
#endif
            packetcnt++;
        } 

        int eof = getc(ts_file);
        if( eof != EOF) {
            printf("\n\nERROR: EOF could not be detected\n\n");
            fclose(ts_file);
            return error_e;
        }
        else {
            printf("\n\nEnd of File\n\n");
        }
    }
    else {
        printf("\n\nFile %s does not exist\n\n", ts_loc);
        fclose(ts_file);
        return error_e;
    }

    fclose(ts_file);
    return success_e;
}