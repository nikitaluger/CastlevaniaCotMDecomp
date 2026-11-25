/* Dispatch the entity's current script step, then refresh its sprite's
 * graphics and camera-relative position. */
extern void sub_08098338(s32, void *);
extern void sub_080C31E0(void *, s32);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];

void sub_080A348C(void *arg0)
{
    void *self;
    void *sprite;
    u8 *scriptState;
    u8 *scriptExtra;
    u8 *stepPtr;
    u8 *opcodePtr;
    u8 *coordTable;
    u8 *animIndexPtr;
    u8 opcode;
    s32 stepOffset;

    self = arg0;
    sprite = *(void **)((u8 *)self + 0x38);
    scriptState = *(u8 **)((u8 *)self + 0x3C);
    scriptExtra = scriptState + 0x48;

    *(u16 *)((u8 *)sprite + 0) = (*(u16 *)((u8 *)sprite + 0) & 0xFFF) | ((*(u16 *)(scriptState + 0x22) + 8) << 12);
    *(u32 *)((u8 *)self + 0x14) = 0x0866FED4;
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
    stepPtr = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
    *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;

    stepOffset = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
    opcodePtr = (u8 *)self;
    opcodePtr += 0x18;
    opcodePtr += stepOffset;
    opcode = *opcodePtr;
    sub_080C31E0(self, *(s32 *)((u8 *)(opcode * 4) + *(u32 *)((u8 *)self + 0x14)));
    *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
    sub_08098338(*(s32 *)(scriptExtra + 0x60), sprite);

    coordTable = D_02021E90;
    animIndexPtr = D_02025FF0;
    animIndexPtr += 0x18A8;
    {
        u32 coordIdx;
        u8 *xBase;
        u8 *yBase;

        coordIdx = ((u32)*animIndexPtr + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)(scriptState + 8) - ((*(u32 *)(xBase + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*animIndexPtr + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)(scriptState + 0xC) - ((*(u32 *)(yBase + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
