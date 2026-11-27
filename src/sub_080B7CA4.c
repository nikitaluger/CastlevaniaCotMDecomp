s32 scaleByRandom(u8);
void sub_080C31E8(void *, void *, u16, s32);
extern u8 D_08102DB4[];
extern u16 D_08102DD4[];
extern s32 gMenuScriptCallback;

/* Pick a random value through the range table, record it as a bit in the
 * actor's effect state, then dispatch the next bytecode script command. */
void sub_080B7CA4(void *arg0) {
    u8 *actorBytes = (u8 *)arg0;
    u8 *effectState = *(u8 **)(actorBytes + 0x3C) + 0x48;
    u8 *rangeTable = D_08102DB4;
    s32 zero;
    u8 randomPick;
    s32 *commandIdPtr;

    randomPick = scaleByRandom(rangeTable[effectState[0x0A] * 4]) + 1;
    zero = 0;
    effectState[8] = randomPick;
    effectState[8] = rangeTable[effectState[0x0A] * 4 + effectState[8]];
    effectState[0x0A] = (1 << effectState[8]) | effectState[0x0A];
    if ((u8)effectState[0x0A] == 7) {
        effectState[0x0A] = zero;
    }
    *(u8 *)(actorBytes + *(s16 *)(actorBytes + 0x22) * 2 + 0x17) = zero;
    commandIdPtr = &gMenuScriptCallback;
    sub_080C31E8(actorBytes + 0x18, actorBytes + 0x22, D_08102DD4[effectState[8]], *commandIdPtr);
}
