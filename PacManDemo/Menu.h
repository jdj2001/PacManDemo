#ifndef MENU_H
#define MENU_H

extern bool gameStarted;  

void initMenu();          
void renderMenu();        
void handleMenuMouse(int button, int state, int x, int y);  
//void displayGameIfStarted();
#endif