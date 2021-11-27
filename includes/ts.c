#include "ts.h"


int tsDemux(char *argv[]) {

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
	return 1;
}