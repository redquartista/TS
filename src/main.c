#include <stdio.h>
#include <stdlib.h>

#define TS_FILE_PATH "/home/pi/TS/watermarking_test_task.ts"

static void printUsage(void) {

    printf("The ts_demux app requires 3 arguments:\n1. Input file location\n2. Output video file location\n3. Output audio file location\n\n");
    printf("The correct usage is: ./ts_demux <input_file> <output_video_file> <output_audio_file>\n\n");
    printf("e.g. ./ts_demux /tmp/watermarking_test_task.ts /tmp/video.mp4 /tmp/audio.wav\n\n");
}

static void printArguments(char *argv[]) {

    printf("1. Input file : %s\n2. Output video file location : %s\n3. Output audio file location : %s\n", argv[1], argv[2], argv[3]);
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
    
    }

  /*  FILE *ts, *ts_out;
    ts = fopen(TS_FILE_PATH, "rb");
    ts_out =  fopen("output.txt", "w+");
    if(ts!=NULL){
        printf("\n\nSOF\n\n");
        char ch = 0;
        while (ch != EOF){

            ch = fgetc(ts);
	    if(ch==0x47)
	    {
            	fprintf(ts_out, "\n%x", ch);
	    }
	    else
	    {
	        fprintf(ts_out, "%x", ch);
	    }
	    
        }
        printf("\n\nEOF");
    }
    fclose(ts);*/
    return 0;
}
