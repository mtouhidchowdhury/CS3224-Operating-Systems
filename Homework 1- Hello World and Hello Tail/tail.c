#include "types.h"
#include "stat.h"
#include "user.h"

char store[512];

void tail(int linesToPrint, int filedes, char* fname) {
   int numberOfLines;
   int lineStop;
   int i = 0;
   int n = 0;
   int skipCheck = 0;
   numberOfLines = 0;
   lineStop = 0;
   while((n = read(filedes, store, sizeof(store))) > 0) {
      for(i = 0; i < n; i++) {
         if(store[i] == '\n') {
            numberOfLines++;
         }
      }
   }
   if(n < 0){
      printf(1, "error reading file\n");
      exit();
   }
   close(filedes);
   int beginRead = numberOfLines - linesToPrint;
   if((filedes = open(fname, 0)) < 0){
      printf(1, "error cannot open file\n");
      exit();
   }
   while((n = read(filedes, store, sizeof(store))) > 0) {
      for(i = 0; i < n; i++) {
         if(lineStop >= beginRead) {
		     	if(store[i] == '\n' && skipCheck == 0) {
		     		skipCheck = 1;
		     		printf(1,"%c",store[i]);
		     	}
		     	else if(store[i] != '\n' && skipCheck == 1) {
		      	skipCheck = 0;
		        printf(1,"%c",store[i]);
	                }
		        else if(store[i] != '\n' && skipCheck == 0) {
		        	printf(1,"%c",store[i]);
		        }
         }
         else {
         	if(store[i] == '\n') {
            	lineStop++;
         	}
         }
      }
   }   
}

int main(int argc, char* argv[]) {
   int filedes, i, linesToPrint;
   char* num;
   
   if(argc <= 2 || argc%2 == 0) {
      filedes = open(argv[1],0);
      tail(10,filedes,argv[1]);
      exit();
   }

   for(i = 1; i < argc; i+=2){
      if((filedes = open(argv[i+1], 0)) < 0){
         printf(1, "error unable to open file\n");
         exit();
      }
      num = argv[i];
      if(num[0] != '-') {
      	linesToPrint = 10;
      }
      else {
      	num++;
      	linesToPrint = atoi(num);
      }
      tail(linesToPrint, filedes, argv[i+1]);
      close(filedes);
   }
   exit();
}



























