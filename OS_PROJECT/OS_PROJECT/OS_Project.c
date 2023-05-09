#include<stdio.h> 
#include <stdlib.h>

#define true 1

int TLB[16][2];
int TLBsize = 0;
        
int pageTable[256];

int memoryFull = 0;
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
  
int main() 
{
    if(true) 
    { 
        char *fileName = "addresses.txt";
        FILE *fp = fopen(fileName, "r"); 
        
        if (fp == NULL) 
        { 
            printf("Couldn't open the file! \n"); 
            return -1;
        } 

        int logicalAddress;
        int pageFaultStat = 0, TLBstat = 0;
        int totalAccess = 0;

        for(int i=0; i<256; i++){
            pageTable[i] = -1;
        }

        while(fscanf(fp, "%d", &logicalAddress ) != EOF){ 
            totalAccess++;

            int pageNumMask = 0, offsetMask = 0;
            for(int i=0; i<8; i++){
                offsetMask |= 1 << i;
                pageNumMask |= 1 << (i+8);
            }

            int pageNum = pageNumMask & logicalAddress;
            pageNum = pageNum >> 8;
            int offset = offsetMask & logicalAddress;

            int TLBhit = 0;

            for(int i=0; i<TLBsize; i++){
                if(TLB[i][0] == pageNum){
                    TLBhit = 1;
                    int valueOfAdd = memory[TLB[i][1]][offset];
                    int physicalAddress = TLB[i][1]*256 + offset;
                    printf("Virtual Address : %d and Physical Address : %d with Value : %d\n", logicalAddress, physicalAddress, valueOfAdd);
                    TLBstat++;
                    break;
                }
            }

            if (TLBhit == 0){
                if(pageTable[pageNum] == -1){
                    pageFault(pageNum);
                    pageFaultStat++;
                }
                int valueOfAdd = memory[pageTable[pageNum]][offset];
                int physicalAddress = pageTable[pageNum]*256 + offset;
                printf("Virtual Address : %d and Physical Address : %d with Value : %d \n", logicalAddress, physicalAddress, valueOfAdd);

                if(TLBsize != 16){
                    TLB[TLBsize][0] = pageNum;
                    TLB[TLBsize][1] = pageTable[pageNum];
                    TLBsize++;
                }
                else{
                    for(int i=0; i<15; i++){
                        TLB[i][0] = TLB[i+1][0];
                        TLB[i][1] = TLB[i+1][1];
                    }
                    TLB[15][0] = pageNum;
                    TLB[15][1] = pageTable[pageNum];
                }
            }
        }
        
        printf("\n\nPage-fault rate is : %.2f %%\n", (1.0*pageFaultStat) / (1.0 * totalAccess) * 100.0);
        printf("TLB-hit rate is : %.2f %%\n", (1.0*TLBstat) / (1.0 * totalAccess) * 100.0);
        
        fclose(fp); 
    } 
    return 0; 
} 