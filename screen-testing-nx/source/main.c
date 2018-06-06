#include <string.h>
#include <stdio.h>

#include <switch.h>

int main(int argc, char **argv)
{

    gfxInitDefault();
    consoleInit(NULL);

    for(u32 i = 1; i < 80; i++){
        printf("\x1b[%d;1H%d",i,i);
    }

    while(appletMainLoop()){
        hidScanInput();

        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if(kDown & KEY_PLUS) break;

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    gfxExit();
    return 0;

}

