/** ls1.c -


*/

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

int do_ls(char *);

int main(int argc, char **argv){
    if(argc == 1) do_ls(".");
    else{
        while(--argc){
            printf("%s:\n", *++argv);
            do_ls(*argv);
        }
    }

}

int do_ls(char *dirName){
    DIR *dir_ptr;
    struct dirent *direntp;  // each entry
    if((dir_ptr = opendir(dirName)) == NULL) fprintf(stderr,"ls1: cannot open %s\n",dirName);
    else{
        while((direntp = readdir(dir_ptr)) != NULL)printf("%s\n",direntp->d_name);
        close(dir_ptr);
    }
}
