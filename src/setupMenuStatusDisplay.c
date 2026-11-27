struct MenuPanelState {
    u8 _0[0x48];
    u32 _48;
    u8 _4C[0x68 - 0x4C];
    s8 stageIndex; /* 0x68: selects an entry in gMenuGfxIdTable */
};
extern struct MenuPanelState gMenuState;

struct StatusPair { s16 x; s16 y; };
extern u32 gGameStatus[];
extern u16 gMenuGfxIdTable[];

s32 createChildObject(s32, s32);
void sub_0800EB44(s32, s32, s32);
void drawDecimalNumber(s16, s32, s32, s32);
void drawComparisonNumber(s16, s16, s32);
void loadStateGraphicsSet(s32);

/* Set up the pause-menu status panel: spawn the five item-preview objects
 * listed at gMenuState+0x48, load the graphics set for the current stage, and
 * draw the status values held in gGameStatus at their VRAM destinations. */
void setupMenuStatusDisplay(s32 parent) {
    u32 *slotPtr;
    struct StatusPair *statusPairs;
    u32 slotIndex;
    u8 *stateBytes;

    statusPairs = (struct StatusPair *)gGameStatus;
    slotIndex = 0;
    stateBytes = (u8 *)&gMenuState;
    slotPtr = (u32 *)(stateBytes + 0x48);
    do {
        s32 child = createChildObject(parent, MENU_SUB_OBJECT_KIND);
        *slotPtr = child;
        *(u8 *)(child + 0x3C) = 0;
        *(u8 *)(*slotPtr + 0x44) = (u8)slotIndex;
        slotPtr++;
        slotIndex++;
    } while (slotIndex <= 4);

    sub_0800EB44(gMenuGfxIdTable[gMenuState.stageIndex], MENU_SUB_OBJECT_STEP, 0xFC0);

    drawDecimalNumber(statusPairs[0xB1].y, 4, 0x511C, 0x0600696E);
    drawDecimalNumber(statusPairs[0xB3].y, 4, 0x511C, 0x060069AE);
    drawDecimalNumber(statusPairs[0xB5].x, 3, 0x511C, 0x060069EE);
    drawComparisonNumber(statusPairs[0xB8].x, *(s16 *)((u8 *)statusPairs + 0x2DE), 0x0600694E);
    drawComparisonNumber(statusPairs[0xBA].x, *(s16 *)((u8 *)statusPairs + 0x2E6), 0x0600698E);
    drawComparisonNumber(statusPairs[0xBC].x, *(s16 *)((u8 *)statusPairs + 0x2EE), 0x060069CE);
    drawComparisonNumber(statusPairs[0xBE].x, *(s16 *)((u8 *)statusPairs + 0x2F6), 0x06006A0E);
    loadStateGraphicsSet(0x06006A8A);
}
