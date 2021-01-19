/* more02.c  -  version 0.2 of more
 * read and print 24 lines then pause for a few special commands
 * feature of version 0.2: reads from /dev/tty for commands
 */

#include <stdio.h>
#define PAGELEN 24
#define LINELEN 512

void do_more(FILE *);
int see_more(FILE *);
int main(int argc, char *argv[]){
    FILE *fp;
    if(argc == 1)
        do_more(stdin);
    else 
        while(--argc)
            if((fp = fopen(*++argv,"r")) != NULL){
                do_more(fp);
                fclose(fp);
            }
            else
                exit(1);
            //endif
    return 0;
}

void do_more(FILE *fp)
/*
 * read PAGELEN lines, then call see_more() for further instructions
 */
{
    char line[LINELEN];          
    int num_of_lines = 0;
    int see_more(FILE *),reply;
    FILE *fp_tty;
    fp_tty = fopen("/dev/tty","r");
    if(fp_tty == NULL) exit(1);
    while(fgets(line,LINELEN,fp)){    //more inputs?
        if(num_of_lines == PAGELEN){  //full screen?
            reply = see_more(fp_tty);       //y/n:ask user
            if(reply == 0)break;      //n:done
            num_of_lines -= reply;    //rset count
        }
        if(fputs(line,stdout) == EOF) //show line
            exit(1);                  //or die
        num_of_lines++;               //count it
    }
}

int see_more(FILE *cmd)
/*
 * print message.wait for respone,return # of lines to advance
 * q means no, space means yes, CR means one line 
 * 
 */
{
    int c;
    printf("\033[7m more?\033[m");
    while((c = getc(cmd)) != EOF){  //NEW: read from tty
        if(c == 'q') return 0;
        if(c == ' ') return PAGELEN;
        if(c == '\n') return 1;
    }
    return 0;
}

