#include <sys/types.h>
#include <dirent.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *arv[]){
    struct dirent direc;
    int num_octal;
    
    if (direc = opendir(argv[1]) == null){
        printf ("\nError %d en open de directorio ", errno);
        perror ("\nError en open");
        exit (EXIT_FAILURE);
    }
    
    num_octal = argv[2].strol;
    
    for (int i = 0; direc.readdir() != null; i++){
        int fd;
        if (fd = open(direc.d_name) < 0){
            perror ("\nError en open");
            exit (EXIT_FAILURE);
        }
        chmod(direc.d_name,num_octal);
    }

}