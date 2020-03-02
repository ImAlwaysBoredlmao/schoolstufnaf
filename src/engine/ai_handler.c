#include "types.h"
#include "time.h"
#include "math.h"
#include "game.h"

#include <stdio.h>

void AI_CheckMovement(anima_t Anima) {
    // Get gametime to compare with update time
    float GameTime = Game_GetTime();

    if (GameTime == Anima.UpdateTime) {
        u16_t Calculation = Math_SeedRandom(420, 20);

        // Move if the die said we could
        if (Calculation <= Anima.AiLevel) {
            Anima.OnMove();
        }
    }
        
    return;
}