#include<iostream>
#include<fstream>
#include<string>
#include<vector>

extern "C"{
    #include<stdio.h> 
    #include<stdlib.h>
    #include"pageFaulte.c"
}

using namespace std;

class Base_Abstract
{
    public:
        virtual void defineEntries() = 0;

};

class Derived : public Base_Abstract
{
    public:
        template <class T>
        static void defineEntries(T arr[])
        {
            for(int i=0; i<256; i++)
                arr[i] = -1;
        }
};
  
int main() 
{   
    string fileName = "addresses.txt";
    ifstream fin;
    fin.open(fileName);

    try
    {
        ifstream fin;
        fin.open(fileName);
        
        if(!fin)
            throw "FILE NOT FOUND";
    }
    catch(char *exep)
    {
        cout<<exep<<endl;
        return 0;
    }

    int logicalAddress;
    int pageFaultStat = 0, TLBstat = 0;
    int totalAccess = 0;

    Derived::defineEntries(pageTable);

    while(fin >> logicalAddress)
    { 
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
                cout<<"Virtual Address: "<<logicalAddress<<" and Physical Address: "<<physicalAddress<<" with value: "<<valueOfAdd<<endl;
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
            cout<<"Virtual Address: "<<logicalAddress<<" and Physical Address: "<<physicalAddress<<" with value: "<<valueOfAdd<<endl;
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
    
    cout<<"\n\nPage-fault rate is : "<<(1.0*pageFaultStat) / (1.0 * totalAccess) * 100.0<<endl;
    cout<<"TLB-hit rate is : "<<(1.0*TLBstat) / (1.0 * totalAccess) * 100.0<<endl;
    
    fin.close();
    
    return 0; 
} 