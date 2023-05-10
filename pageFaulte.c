#include<stdio.h> 
#include<stdlib.h>

int TLB[16][2];
int TLBsize = 0;
int memoryFull = 0;
int pageTable[256];
int memory[256][256];


void pageFault(int pageNum){
    FILE *ptr = fopen("BACKING_STORE.bin","rb");

    if (ptr == NULL){
        printf("Couldn't open the file! \n"); 
        return;
    }

    if (fseek(ptr, 256*pageNum, SEEK_SET) != 0){
        printf("Page not found!\n");
        return;
    }

    unsigned char buffer[256];
    fread(buffer,sizeof(buffer),1,ptr); // read 10 bytes to our buffer

    for(int i=0; i<256; i++){
        memory[memoryFull][i] = buffer[i];
    }

    pageTable[pageNum] = memoryFull;
    memoryFull++;

    fclose(ptr);

}