#include <string.h>
#include <stdio.h>

#include <switch.h>

int main(int argc, char **argv)
{
    gfxInitDefault();
    consoleInit(NULL);

    printf("\x1b[1;1HHello World!");

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