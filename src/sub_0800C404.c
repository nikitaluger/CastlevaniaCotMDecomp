/* Initializes the status HUD: sets up graphics state, loads tiles and palettes by DMA,
 * builds the sprite objects, draws four game-state values, then advances the given
 * entity's animation state. */
extern u8 D_02025368[];
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
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
extern u32 D_08671BB0;

void sub_080C2E68(u16 *dst, u32 src, s32 size);
void sub_080035E4(void);
void sub_08000E98(s32 a, u8 *src, u8 *dst, s32 c, s32 d);
void sub_0805FDF0(void);
void sub_0805FE28(s32 a, s32 b);
void sub_0805FE8C(s32 a, s32 b, s32 c);
void sub_0805FEB4(s32 a);
void sub_0805FEC8(s32 a);
void sub_0800C804(u8 a, u8 b);
void sub_080C31E4(u8 *a, u8 *b, u32 c);
void sub_080C31E0(void *a, u32 b);

void sub_0800C404(void *entity)
{
    u8 *gfx;
    void *obj;
    u8 *stats;
    s8 zero;
    s16 dmaZero;
    vu32 *dmaRegs;
    s32 offset;
    u8 *tileAddr;
    u8 *tileData;
    s16 stateIndex;
    u8 *statePtr;
    u8 animByte;
    u32 *animTable;
    u32 *animData;

    obj = entity;
    stats = D_02025368;
    gfx = D_02021E90;

    *(u32 *)(gfx + 0x125C) = 0;

    zero = 0;
    D_03000830 = (D_03000830 & 0xF0FF) | zero;

    offset = 0x93 << 5;
    sub_080C2E68((u16 *)(gfx + offset), 0x080CAF48, 0x40);

    offset = 0x99 << 5;
    tileAddr = gfx + offset;
    *(u16 *)tileAddr = 0;
    tileAddr -= 0x40;
    *(u16 *)tileAddr = 0;
    gfx += 0x95 << 5;
    *(u16 *)gfx = 0;

    sub_080035E4();

    dmaZero = 0;
    dmaRegs = (vu32 *)0x040000D4;
    dmaRegs[0] = (u32)&dmaZero;
    dmaRegs[1] = 0x06000000;
    dmaRegs[2] = 0x8100C000;
    (void)dmaRegs[2];
    dmaRegs[0] = 0x080CABC8;
    dmaRegs[1] = 0x05000000;
    dmaRegs[2] = 0x80000100;
    (void)dmaRegs[2];

    tileData = (u8 *)0x080CADC8;
    sub_08000E98(1, tileData + 0x00, D_06000104, 0x20, 0x10);
    sub_08000E98(1, tileData + 0x20, D_06000144, 0x20, 0x10);
    sub_08000E98(1, tileData + 0x40, D_06000184, 0x20, 0x10);
    sub_08000E98(1, tileData + 0x60, D_060001C4, 0x20, 0x10);
    sub_08000E98(1, tileData + 0x80, D_06000204, 0x20, 0x10);
    sub_08000E98(1, tileData + 0xA0, D_06000244, 0x20, 0x10);
    sub_08000E98(1, tileData + 0xC0, D_06000284, 0x20, 0x10);
    sub_08000E98(1, tileData + 0xE0, D_060002C4, 0x20, 0x10);
    sub_08000E98(1, tileData + (0x80 << 1), D_06000304, 0x20, 0x10);
    sub_08000E98(1, tileData + (0x90 << 1), D_06000344, 0x20, 0x10);
    sub_08000E98(1, tileData + (0xA0 << 1), D_06000384, 0x20, 0x10);
    sub_08000E98(1, tileData + (0xB0 << 1), D_060003C4, 0x20, 0x10);

    sub_0805FDF0();
    sub_0805FE28(0, 1);
    sub_0805FE8C(0, 3, 2);
    sub_0805FEB4(0);
    sub_0805FEC8(0x19);
    sub_0805FE28(0, 0x21);
    sub_0805FEC8(0x1A);
    sub_0805FE28(0, 0x41);
    sub_0805FEC8(0x1B);
    sub_0805FE28(0, 0x61);
    sub_0805FEC8(0x1C);

    sub_0800C804(stats[0x94], 0x13);
    sub_0800C804(stats[0x95], 0x33);
    sub_0800C804(D_02025FF0[0], 0x53);
    sub_0800C804(stats[0x8C], 0x73);

    stateIndex = *(s16 *)((u8 *)obj + 0x22);
    *(u8 *)((u8 *)obj + stateIndex * 2 + 0x19) = zero;

    animData = &D_08671BB0;
    statePtr = (u8 *)obj + 0x18;
    sub_080C31E4(statePtr, (u8 *)obj + 0x22, *animData);

    stateIndex = *(s16 *)((u8 *)obj + 0x22);
    *(u8 *)((u8 *)obj + stateIndex * 2 + 0x19) += 1;

    stateIndex = *(s16 *)((u8 *)obj + 0x22);
    statePtr += stateIndex * 2;
    animByte = *statePtr;
    animTable = *(u32 **)((u8 *)obj + 0x14);

    sub_080C31E0(obj, animTable[animByte]);
}
