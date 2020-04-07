// (c) 2020 MotoLegacy
// This code is licensed under MIT license (see LICENSE for details)

#include "input.h"
#include "game.h"
#include "graphics.h"

#include <stdio.h>

keydata_t KeyFunctions[MAX_KEYFUNCTIONS];
int Current_Key;

// Handle game input registration
void Input_RegisterKey(sfKeyCode key, void (*func)) {
    KeyFunctions[Current_Key].key = key;
    KeyFunctions[Current_Key].func = func;

    Current_Key++;
}

// Check game-defined key presses
void Input_CheckKeyboard() {
    // Escape is a global, non-controllable key.. always quit.
    if (sfKeyboard_isKeyPressed(sfKeyEscape)) {
        Game_Running = FALSE;
    }

    // Check our game-defined keys
    for (int i = 0; i < Current_Key; ++i) {
        if (sfKeyboard_isKeyPressed(KeyFunctions[i].key) && KeyFunctions[i].pressed == FALSE) {
            KeyFunctions[i].func();
            KeyFunctions[i].pressed = TRUE;
        } else if (!sfKeyboard_isKeyPressed(KeyFunctions[i].key)) {
            // Key lifted, ready to press again!
            KeyFunctions[i].pressed = FALSE;
        }      
    }
}

// Mouse-Related functions
void Input_CheckMouse() {
    sfVector2i mouse = sfMouse_getPositionRenderWindow(GameWindow);

    // Scroll Stuff
    switch (Scroll_Method) {
        case SCROLL_AUTOMATIC:
            Game_AutoScroll();
            break;
        case SCROLL_MANUAL:
            Game_ManualScroll(mouse);
            break;
        default:
            break;
    }   

    // Check UI Elements
    int MinX;
    int MaxX;
    int MinY;
    int MaxY;
    for (int i = 0; i < Current_Element; ++i) {
        // Set Up Boundaries
        MinX = sfSprite_getPosition(UIElements[i].Sprite).x;
        MaxX = MinX + sfTexture_getSize(UIElements[i].Texture).x;
        MinY = sfSprite_getPosition(UIElements[i].Sprite).y;
        MaxY = MinY + sfTexture_getSize(UIElements[i].Texture).y;
        // Our Cursor is on the X Pos
        if (mouse.x >= MinX && mouse.x <= MaxX) {
            // Our Cursor is on the Y Pos
            if (mouse.y >= MinY &&  mouse.y <= MaxY) {
                // Remove Spam
                if (UIElements[i].Activated)
                    return;
                
                // Check for Click if needbe
                if (UIElements[i].Need_Clicked) {
                    if (sfMouse_isButtonPressed(sfMouseLeft)) {
                        UIElements[i].func();
                        UIElements[i].Activated = TRUE;
                    }
                } else {
                    UIElements[i].func();
                    UIElements[i].Activated = TRUE;
                }
            } else {
                UIElements[i].Activated = FALSE;
            }
        } else {
            UIElements[i].Activated = FALSE;
        }
    }
}

void Input_CheckButtons() {
    Input_CheckKeyboard();
    Input_CheckMouse();
}