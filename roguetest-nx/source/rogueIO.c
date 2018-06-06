#include <string.h>
#include <stdio.h>

#include <switch.h>
#include "rogueIO.h"

void printNx(char *input, u32 r, u32 c){
    printf("\x1b[%d;%dH%s",r,c,input);
}

void printMenu(u32 selection){
    
    //Define Menu Options
    char options[3][3] = {
        "ATK", "INV", "GET"
    };
    
    //Set Max Width and Height (Shouldn't need to change)
    u32 maxW = 80;
    u32 maxH = 3;
    
    //Print menu border
    printNx("o",1,1);
    printNx("o",1,maxW);
    printNx("o",maxH,1);
    printNx("o",maxH,maxW);
    for(u32 i = 2; i < maxW; i++){
        printNx("-",1,i);
        printNx("-",maxH,i);
    }
    for(u32 i = 2; i <maxH; i++){
        printNx("|",i,1);
        printNx("|",i,maxW);
    }

    //Print Menu Options
    printNx("  ",2,2);
    for(u32 i = 0; i < 3; i++){
        printNx(options[i],2,(i*5)+4);
        printNx("  ",2,(i*5)+7);
    }

    printNx(">",2,(selection*5)+3);
}

void printNotif(char *input){

}

void printStats(u32 stats[]){

}

void printInventory(u32 inventory[]){

}

void printBorder(){

}

void printCharacter(u32 oldLocation[], u32 newLocation[]){
    printNx(" ",oldLocation[0],oldLocation[1]);
    printNx("@",newLocation[0],newLocation[1]);
}
