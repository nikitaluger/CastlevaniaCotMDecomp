void sub_080C31E8(void *, void *, s32, s32);

extern u8 gCameraState[];
extern u16 gCrossfadeGfxState[];

/* Entity script action: unless game-state flag 8 is set, bail out if the
 * current step's action byte is not 0x88. Otherwise set the global state
 * words, clear a game-state flag bit, reset the step's action byte and run
 * the script step. */
void sub_08005CAC(u8 *entity) {
    u32 flagOffset;
    u8 *gameState;
    s16 stepIndex;

    gameState = gCameraState;
    flagOffset = 0x146C;
    if ((*(u16 *)(gameState + flagOffset) & 8) == 0) {
        stepIndex = *(s16 *)(entity + 0x22);
        if (*(u8 *)(entity + stepIndex * 2 + 0x19) != 0x88) {
            return;
        }
    }

    gCrossfadeGfxState[2] = 0x0241;
    gCrossfadeGfxState[3] = 0x10;
    *(u16 *)(gameState + (0x95 << 5)) &= 0xDFFF;
    stepIndex = *(s16 *)(entity + 0x22);
    *(u8 *)(entity + stepIndex * 2 + 0x19) = 0;
    {
        s32 *lit = (s32 *)0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, 4, *lit);
    }
}
