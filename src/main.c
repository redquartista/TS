#include <stdio.h>
#include "temp.h"

int main(void) {

	printSomething();
	return 0;

}

/*
#include <stdio.h>

int main(void){

    FILE *ts, *ts_out;
    ts = fopen("/home/pi/mpeg_ts_assignment/watermarking_test_task.ts", "rb");
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
    fclose(ts);
    return 0;
}

*/