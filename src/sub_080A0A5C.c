extern void sub_08098338(s32, void *);
extern void sub_080C31E0(void *, s32);

extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Advances the entity's script step, dispatches that step's handler, then
 * updates its camera-relative screen position. */
void sub_080A0A5C(void *entity)
{
    void *parent;
    u8 *component;
    u8 *stepPtr;
    u8 *scriptPtr;
    u8 *pt;
    u8 *pb;
    u8 stepByte;
    s32 stepOffset;

    parent = *(void **)((u8 *)entity + 0x38);
    component = *(u8 **)((u8 *)entity + 0x3C);

    *(u16 *)((u8 *)parent + 0) = (*(u16 *)((u8 *)parent + 0) & 0xFFF) | ((*(u16 *)((u8 *)component + 0x22) + 8) << 12);
    *(u32 *)((u8 *)entity + 0x14) = 0x0866FE18;
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) + 1;
    stepPtr = (u8 *)((s16)(*(u16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;

    stepOffset = (s16)(*(u16 *)((u8 *)entity + 0x22)) * 2;
    scriptPtr = (u8 *)entity;
    scriptPtr += 0x18;
    scriptPtr += stepOffset;
    stepByte = *scriptPtr;
    sub_080C31E0(entity, *(s32 *)((u8 *)(stepByte * 4) + *(u32 *)((u8 *)entity + 0x14)));
    *(u16 *)((u8 *)entity + 0x22) = *(u16 *)((u8 *)entity + 0x22) - 1;
    sub_08098338(1, parent);

    pt = D_02021E90;
    pb = D_02025FF0;
    pb += 0x18A8;
    {
        u32 idx;
        u8 *base1;
        u8 *base2;

        idx = ((u32)*pb + 1) * 0x40;
        base1 = pt + 0x1278;
        *(u32 *)((u8 *)parent + 0x14) = *(u32 *)((u8 *)component + 8) - ((*(u32 *)(base1 + idx) + 0x8000) & 0xFFFF0000);

        idx = ((u32)*pb + 1) * 0x40;
        base2 = pt + 0x127C;
        *(u32 *)((u8 *)parent + 0x18) = *(u32 *)((u8 *)component + 0xC) - ((*(u32 *)(base2 + idx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
