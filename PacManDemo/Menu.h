#ifndef MENU_H
#define MENU_H

extern bool gameStarted;  
extern bool instructionsVisible;

void initMenu();          
void renderMenu();        
void handleMenuMouse(int button, int state, int x, int y); 
void renderInstructions();

#endif