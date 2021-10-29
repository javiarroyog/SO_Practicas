/*
ejercicio2.c
*/
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>     /* Primitive system data types for abstraction\
            of implementation-dependent data types.
            POSIX Standard: 2.6 Primitive System Data Types
            <sys/types.h>
         */
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>


int main(int argc, char *argv[]){
   int fd_original, fd_nuevo;
   int tam_archivo, tam_nuevo;
   int num_bloques = 0;
   const int TAMANIO_BLOQUES = 80;
   char buf1[TAMANIO_BLOQUES];
   
   if ((fd_original = open((argv[1]),S_IRUSR))<0){
      printf("\nError %d en open",errno);
      perror("\nError en open");
      exit(EXIT_FAILURE);
   }
   printf("Valor de fd-->%d ",fd_original);
   
   tam_archivo = lseek(fd_original,0,SEEK_END);
   printf("Tamanio del archivo-> %d ",tam_archivo);
   lseek(fd_original,SEEK_END,0);
   
   tam_nuevo = tam_archivo;
   
   printf("Tamanio del archivo-> %d ",tam_nuevo);
   while (tam_nuevo > 0){
      num_bloques++;
      tam_nuevo -= TAMANIO_BLOQUES;
   }
   
   printf("Num bloques-> %d ",num_bloques);
   
   if((fd_nuevo = open("salida.txt",O_CREAT|O_TRUNC|O_WRONLY,S_IWUSR))<0) {
      printf("\nError %d en open",errno);
      perror("\nError en open");
      exit(EXIT_FAILURE);
   }
   printf("Valor de fd-->%d ",fd_nuevo);
   
   for (int i = 0; i < num_bloques - 1; i++){
   
      if ((read (fd_original,buf1,TAMANIO_BLOQUES)) != TAMANIO_BLOQUES){
         printf("\nError %d en read",errno);
         printf("\nError %d en read",i);
         perror("\nError en read");
         exit(EXIT_FAILURE);
      }
   
      if((write(fd_nuevo,buf1,TAMANIO_BLOQUES)) != TAMANIO_BLOQUES) {
         perror("\nError en primer write");
         exit(EXIT_FAILURE);
      }
   }
   
   // Para los bytes restantes
   
   int restante = tam_archivo - ((num_bloques-1)* TAMANIO_BLOQUES);
   printf("Restante-->%d ",restante);
   lseek (fd_original, (num_bloques-1)* TAMANIO_BLOQUES, SEEK_SET);
   
   if ((read (fd_original,buf1,restante)) != restante){
      printf("\nError %d en read",errno);
      perror("\nError en read");
      exit(EXIT_FAILURE);
   }
           
   if((write(fd_nuevo,buf1,restante)) != restante) {
      perror("\nError en primer write");
      exit(EXIT_FAILURE);
   }
       

}
           
