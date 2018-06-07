#include <string.h>
#include <stdio.h>

#include <switch.h>
#include "rogueIO.h"

bool isValidMoveKey(u64 kDown){
    if(kDown == KEY_DRIGHT ||kDown == KEY_DLEFT ||kDown == KEY_DUP ||kDown == KEY_DDOWN){
        return true;
    } else {
        return false;
    }
}

bool isMenuKey(u64 kDown){
    if(kDown == KEY_L || kDown == KEY_R){
        return true;
    } else {
        return false;
    }
}

int main(int argc, char **argv)
{



    /*
    char keysNames[32][32] = {
        "KEY_A", "KEY_B", "KEY_X", "KEY_Y",
        "KEY_LSTICK", "KEY_RSTICK", "KEY_L", "KEY_R",
        "KEY_ZL", "KEY_ZR", "KEY_PLUS", "KEY_MINUS",
        "KEY_DLEFT", "KEY_DUP", "KEY_DRIGHT", "KEY_DDOWN",
        "KEY_LSTICK_LEFT", "KEY_LSTICK_UP", "KEY_LSTICK_RIGHT", "KEY_LSTICK_DOWN",
        "KEY_RSTICK_LEFT", "KEY_RSTICK_UP", "KEY_RSTICK_RIGHT", "KEY_RSTICK_DOWN",
        "KEY_SL", "KEY_SR", "KEY_TOUCH", "",
        "", "", "", ""
    };
    */

    //Inventory Data
    int invSize = 2;
    char *items[2];
    items[0] = "HLTH P";
    items[1] = "MANA P";

    u32 inventory[2] = {
        12, 1
    };
    //
    
    u32 playerLocation[2] = {8,5};
    u32 oldPlayerLocation[2] = {playerLocation[0],playerLocation[1]};
    u32 kDownOld = 0;
    u32 menuSelection = 0;
    u32 stats[4] = {10,8,20,18};

    gfxInitDefault();
    consoleInit(NULL);

    printNx("@",playerLocation[0],playerLocation[1]);
    printMenu(menuSelection);
    printNotif("The barbarian strikes you for 12 damage");
    printStats(stats);
    printInventory(inventory, items, invSize);
    printGameBorder();
    printGameMap();

    // Main loop
    while(appletMainLoop())
    {
        
        //Scan all the inputs. This should be done once for each frame
        hidScanInput();

        //hidKeysDown returns information about which buttons have been just pressed (and they weren't in the previous frame)
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);


        if (kDown & KEY_PLUS) break; // break in order to return to hbmenu

        //Do the keys printing only if keys have changed
        if (kDown != kDownOld && isValidMoveKey(kDown))
        {
            //Clear console
            //consoleClear();



            if(kDown & KEY_DRIGHT){
                if(playerLocation[1] != 66){
                    playerLocation[1] += 1;
                }
            }
            if(kDown & KEY_DLEFT){
                if(playerLocation[1] != 4){
                    playerLocation[1] -= 1;
                }
            }
            if(kDown & KEY_DUP){
                if(playerLocation[0] != 7){
                    playerLocation[0] -= 1;
                }
            }
            if(kDown & KEY_DDOWN){
                if(playerLocation[0] != 39){
                    playerLocation[0] += 1;
                }
            }
            printCharacter(oldPlayerLocation,playerLocation);
        }

        if(kDown != kDownOld && isMenuKey(kDown)){
            if(kDown == KEY_L){
                if(menuSelection != 0){
                    menuSelection -= 1;
                }
            }
            if(kDown == KEY_R){
                if(menuSelection != 2){
                    menuSelection += 1;
                }
            }

            printMenu(menuSelection);
        }

        //Set keys old values for the next frame
        kDownOld = kDown;

        if(playerLocation[0] != oldPlayerLocation[0] || playerLocation[1] != oldPlayerLocation[1]){
            oldPlayerLocation[0] = playerLocation[0];
            oldPlayerLocation[1] = playerLocation[1];
        }

        gfxFlushBuffers();
        gfxSwapBuffers();
        gfxWaitForVsync();
    }

    gfxExit();
    return 0;
}