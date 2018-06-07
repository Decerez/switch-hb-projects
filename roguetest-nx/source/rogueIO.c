#include <string.h>
#include <stdio.h>

#include <switch.h>
#include "rogueIO.h"
#include "perlin2d.h"

void printNx(char *input, u32 r, u32 c){
    printf("\x1b[%d;%dH%s",r,c,input);
}

void printNxi(u32 input, u32 r, u32 c){
    printf("\x1b[%d;%dH%d",r,c,input);
}

void drawBox(u32 sr, u32 sc, u32 er, u32 ec){
    for(u32 i = 0; i < er-sr; i++){
        printNx("|",sr+i,sc);
        printNx("|",sr+i,ec);
    }
    for(u32 i = 0; i < ec-sc; i++){
        printNx("-",sr,sc+i);
        printNx("-",er,sc+i);
    }
    printNx("o",sr,sc);
    printNx("o",sr,ec);
    printNx("o",er,sc);
    printNx("o",er,ec);
}

void printMenu(u32 selection){
    
    //Define Menu Options
    char options[3][3] = {
        "ATK", "INV", "GET"
    };
    
    //Print menu border
    drawBox(1,1,3,80);
    printNx("MENU (L/R)", 1, 3);

    //Print Menu Options
    printNx("  ",2,2);
    for(u32 i = 0; i < 3; i++){
        printNx(options[i],2,(i*5)+4);
        printNx("  ",2,(i*5)+7);
    }

    printNx(">",2,(selection*5)+3);
}

void printNotif(char *input){
    drawBox(43,1,45,80);
    printNx("Log",43,3);

    printNx(input,44,3);

}

//Stats in the format of [0] = maxHealth, [1] = health, [2] = maxMana, and [3] = mana
void printStats(u32 stats[]){
    u32 startC = 70;
    u32 startR = 35;
    drawBox(startR,startC,startR + 5,startC + 10);
    printNx("STATS", startR, startC + 3);
    printNx("HP", startR + 1, startC + 2);
    printNxi(stats[1],startR + 2, startC + 4);
    printNx("/",startR + 2, startC + 6);
    printNxi(stats[0],startR + 2, startC + 7);
    printNx("MANA", startR + 3, startC + 2);
    printNxi(stats[3],startR + 4, startC + 4);
    printNx("/",startR + 4, startC + 6);
    printNxi(stats[2],startR + 4, startC + 7);

}

//inv in the format [0] = hp potions, [1] = mana potions, etc. (maybe make inventory reference file?)
void printInventory(u32 inventory[], char *itemNames[], u32 invSize){
    u32 printRow = 2;
    u32 startC = 70;
    u32 startR = 6;
    drawBox(startR,startC,startR + 20,startC + 10);
    printNx("INV", startR, startC + 4);
    for(u32 i = 0; i < invSize; i++){
        if(inventory[i] > 0){
            printNx(itemNames[i],startR + printRow, startC + 2);
            printRow += 1;
            printNx("x",startR + printRow, startC + 6);
            printNxi(inventory[i], startR + printRow, startC + 7);
            printRow += 1;
        }
    }
}

void printGameBorder(){
    drawBox(6,3,45-5,80-13);
    printNx("GAME WINDOW", 6,5);

}

//32 Rows, 62 Columns
void printGameMap(){
    u32 rs = 7, cs = 4;
    u32 r, c;
    float grad;
    for(r = 0; r <= 32; r++){
        for(c = 0; c <= 62; c++){
            grad = perlin2d(c,r,0.2,4);
            if(grad < 0.5){
                printNx(CONSOLE_ESC(34;1m) "~",r+rs,c+cs);
            } else  if(grad > 0.85){
                printNx(CONSOLE_ESC(37;1m) "^",r+rs,c+cs);
            } else  if(grad > 0.75){
                printNx(CONSOLE_ESC(30;1m) "^",r+rs,c+cs);
            /*} else if(grad < 0.55){
                printNx(CONSOLE_ESC(33;1m) ",",r+rs,c+cs);*/
            } else {
                printNx(CONSOLE_ESC(32;1m) ".",r+rs,c+cs);
            }
        }
    }
}

void printCharacter(u32 oldLocation[], u32 newLocation[]){
    printNx(" ",oldLocation[0],oldLocation[1]);
    printNx("@",newLocation[0],newLocation[1]);
}

