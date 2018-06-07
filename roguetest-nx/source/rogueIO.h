#ifndef ROGUEIO_H_
#define ROGUEIO_H_

void printNx(char *input, u32 r, u32 c);
void printMenu(u32 selection);
void printNotif(char *input);
void printStats(u32 stats[]);
void printInventory(u32 inventory[], char *itemNames[], u32 invSize);
void printGameBorder();
void printCharacter(u32 oldLocation[], u32 newLocation[]);
//char* parseAction();

#endif