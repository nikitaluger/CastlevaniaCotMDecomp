/* Initializes the status HUD: sets up graphics state, loads tiles and palettes by DMA,
 * builds the sprite objects, draws four game-state values, then advances the given
 * entity's animation state. */
extern u8 gGameStatus[];
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern vu16 D_03000830;
extern vu32 D_040000D4[];
extern u8 D_06000104[];
extern u8 D_06000144[];
extern u8 D_06000184[];
extern u8 D_060001C4[];
extern u8 D_06000204[];
extern u8 D_06000244[];
extern u8 D_06000284[];
extern u8 D_060002C4[];
extern u8 D_06000304[];
extern u8 D_06000344[];
extern u8 D_06000384[];
extern u8 D_060003C4[];
extern u32 gScriptStepCallbackTable;

void sub_080C2E68(u16 *dst, u32 src, s32 size);
void clearActorPool(void);
void postDisplaySprite(s32 a, u8 *src, u8 *dst, s32 c, s32 d);
void resetMapRender(void);
void setLayerTilemap(s32 a, s32 b);
void setMapLayerParams(s32 a, s32 b, s32 c);
void setScreenTransition(s32 a);
void sub_0805FEC8(s32 a);
void drawHudValue(u8 a, u8 b);
void sub_080C31E4(u8 *a, u8 *b, u32 c);
void sub_080C31E0(void *a, u32 b);

void initStatusHud(void *entity)
{
    u8 *gfxState;
    void *hudEntity;
    u8 *gameStatus;
    s8 zero;
    s16 dmaFillWord;
    vu32 *dmaRegs;
    s32 tileOffset;
    u8 *tileAddr;
    u8 *tileSource;
    s16 stateIndex;
    u8 *scriptStatePtr;
    u8 animByte;
    u32 *handlerTable;
    u32 *handlerTablePtr;

    hudEntity = entity;
    gameStatus = gGameStatus;
    gfxState = gCameraState;

    *(u32 *)(gfxState + 0x125C) = 0;

    zero = 0;
    D_03000830 = (D_03000830 & 0xF0FF) | zero;

    tileOffset = 0x93 << 5;
    sub_080C2E68((u16 *)(gfxState + tileOffset), 0x080CAF48, 0x40);

    tileOffset = 0x99 << 5;
    tileAddr = gfxState + tileOffset;
    *(u16 *)tileAddr = 0;
    tileAddr -= 0x40;
    *(u16 *)tileAddr = 0;
    gfxState += 0x95 << 5;
    *(u16 *)gfxState = 0;

    clearActorPool();

    dmaFillWord = 0;
    dmaRegs = (vu32 *)0x040000D4;
    dmaRegs[0] = (u32)&dmaFillWord;
    dmaRegs[1] = 0x06000000;
    dmaRegs[2] = 0x8100C000;
    (void)dmaRegs[2];
    dmaRegs[0] = 0x080CABC8;
    dmaRegs[1] = 0x05000000;
    dmaRegs[2] = 0x80000100;
    (void)dmaRegs[2];

    tileSource = (u8 *)0x080CADC8;
    postDisplaySprite(1, tileSource + 0x00, D_06000104, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0x20, D_06000144, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0x40, D_06000184, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0x60, D_060001C4, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0x80, D_06000204, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0xA0, D_06000244, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0xC0, D_06000284, 0x20, 0x10);
    postDisplaySprite(1, tileSource + 0xE0, D_060002C4, 0x20, 0x10);
    postDisplaySprite(1, tileSource + (0x80 << 1), D_06000304, 0x20, 0x10);
    postDisplaySprite(1, tileSource + (0x90 << 1), D_06000344, 0x20, 0x10);
    postDisplaySprite(1, tileSource + (0xA0 << 1), D_06000384, 0x20, 0x10);
    postDisplaySprite(1, tileSource + (0xB0 << 1), D_060003C4, 0x20, 0x10);

    resetMapRender();
    setLayerTilemap(0, 1);
    setMapLayerParams(0, 3, 2);
    setScreenTransition(0);
    sub_0805FEC8(0x19);
    setLayerTilemap(0, 0x21);
    sub_0805FEC8(0x1A);
    setLayerTilemap(0, 0x41);
    sub_0805FEC8(0x1B);
    setLayerTilemap(0, 0x61);
    sub_0805FEC8(0x1C);

    drawHudValue(gameStatus[0x94], 0x13);
    drawHudValue(gameStatus[0x95], 0x33);
    drawHudValue(gMainWorkspace[0], 0x53);
    drawHudValue(gameStatus[0x8C], 0x73);

    stateIndex = *(s16 *)((u8 *)hudEntity + 0x22);
    *(u8 *)((u8 *)hudEntity + stateIndex * 2 + 0x19) = zero;

    handlerTablePtr = &gScriptStepCallbackTable;
    scriptStatePtr = (u8 *)hudEntity + 0x18;
    sub_080C31E4(scriptStatePtr, (u8 *)hudEntity + 0x22, *handlerTablePtr);

    stateIndex = *(s16 *)((u8 *)hudEntity + 0x22);
    *(u8 *)((u8 *)hudEntity + stateIndex * 2 + 0x19) += 1;

    stateIndex = *(s16 *)((u8 *)hudEntity + 0x22);
    scriptStatePtr += stateIndex * 2;
    animByte = *scriptStatePtr;
    handlerTable = *(u32 **)((u8 *)hudEntity + 0x14);

    sub_080C31E0(hudEntity, handlerTable[animByte]);
}
