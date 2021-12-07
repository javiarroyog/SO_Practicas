#include <sys/types.h>
#include <dirent.h>
#include<unistd.h>		//POSIX Standard: 2.10 Symbolic Constants         <unistd.h>
#include<sys/stat.h>
#include<fcntl.h>		//Needed for open
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){
    DIR* dir;
    struct dirent direc;
    int num_octal;
    
    if ((dir= opendir(argv[1]) == NULL)){
        printf ("\nError %d en open de directorio ", errno);
        perror ("\nError en open");
        exit (EXIT_FAILURE);
    }
    
    num_octal = strtol(argv[2]);
    
    while((direc = readdir(dir)) != NULL){
        int fd;
        if (fd = open(direc.d_name, S_IRGRP) < 0){
            perror ("\nError en open");
            exit (EXIT_FAILURE);
        }
        chmod(direc.d_name,num_octal);
        close(fd);
    }

}
