#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "ts.h"

static void printUsage(void) {

    printf("The ts_demux app requires 3 arguments:\n1. Input file location\n2. Output video file location\n3. Output audio file location\n\n");
    printf("The correct usage is: ./ts_demux <input_file> <output_video_file> <output_audio_file>\n\n");
    printf("e.g. ./ts_demux /tmp/watermarking_test_task.ts /tmp/video.mp4 /tmp/audio.wav\n\n");
}

static void printArguments(char *argv[]) {

    printf("Verify the arguments. Press CTRL+C to terminate if any of them is incorrect:\n1. Input file : %s\n2. Output video file location : %s\n3. Output audio file location : %s\n\n", argv[1], argv[2], argv[3]);
    //sleep(5);
    printf("Proceeding\n\n");
}

int main( int argc, char *argv[] )  {

   printf("\n");
   if( argc < 4 ) {
      printf("Too few arguments supplied\n\n");
      printUsage();
      exit(0);
   }
   else if( argc > 4 ) {
      printf("Too many arguments supplied.\n\n");
      printUsage();
      exit(0);
   }
   else {
      printArguments(argv);
      printf("Demultiplexing %s\n\n", argv[1]);
      if(tsDemux(argv)) {
          printf("\n\nSuccesss!\n\nFind the video file at: %s and\naudio file at: %s\n\n", argv[2], argv[3]);
          return 1;
      }
      else {
          printf("FAILURE!\n\n");
          return 0;
      }
    }
}
