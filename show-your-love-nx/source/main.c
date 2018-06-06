#include <string.h>
#include <stdio.h>

#include <switch.h>

void printNx(char *input, int r, int c){
    printf("\x1b[%d;%dH%s",r,c,input);
}

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(NULL);

    //From this I learned the console for this switch via libNX is 80 characters long
    //printNx("1-3-5-7-9-11-14-17-20-23-26-29-32-35-38-41-44-47-50-53-56-59-62-65-68-71-74-77-80",9,1);
    
    //Using this info, I updated my original code, which was just starting on the left-most column, to center itself around column 40

    for(u32 i = 7; i < 22; i++){
        if(i == 7 || i == 21){
            printNx("o",i,25);
            printNx("o",i,55);
        } else {
            printNx("|",i,25);
            printNx("|",i,55);
        }
    }

    for(u32 i = 26; i < 55; i++){
        printNx("-",7,i);
        printNx("-",21,i);
    }

    printNx(",d88b.d88b,",10,35);
    printNx("88888888888",11,35);
    printNx("`Y8888888Y'",12,35);
    printNx("  `Y888Y'  ",13,35);
    printNx("    `Y'",14,35);
    printNx("To my lovely boyfriend...",16,28);
    printNx("Kat <3",18,37);


    while(appletMainLoop()){
        hidScanInput();

        u64 keyDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if(keyDown & KEY_PLUS) break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();

    }

    gfxExit();
    return 0;
}
