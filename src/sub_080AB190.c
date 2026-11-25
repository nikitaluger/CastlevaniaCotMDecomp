extern void sub_08098338(void *, void *);
extern s32 sub_080C31E0(s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_081021D8[];
extern u8 D_08670108[];

/* Advance one actor script step: update the sprite's attributes from its
 * target, dispatch the step handler, redraw its tiles and apply the scroll
 * offset to the target's screen position. */
void sub_080AB190(u8 *arg0) {
    u8 *gfx;
    u8 *target;
    u8 *p2;
    u32 idx;
    u32 v1;
    u32 v2v;
    u8 *pt;
    u8 *pb;
    u8 *pt1;
    u8 *pt2;
    u32 layerOff;
    u8 b;

    gfx = *(u8 **)(arg0 + 0x38);
    target = *(u8 **)(arg0 + 0x3C);

    *(u16 *)(gfx + 0x00) = (*(u16 *)(gfx + 0x00) & 0x0FFF) | (((*(u16 *)(target + 0x22)) + 8) << 12);
    *(u32 *)(arg0 + 0x14) = (u32)D_08670108;
    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) + 1;
    p2 = (u8 *)((s32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
    *(u8 *)(p2 + 0x19) = *(u8 *)(p2 + 0x19) + 1;

    {
        s32 idx2 = *(s16 *)(arg0 + 0x22) * 2;
        u8 *base18 = arg0 + 0x18;
        u8 b2 = *(u8 *)((u32)base18 + (u32)idx2);
        sub_080C31E0((s32)arg0, *(u32 *)(*(u32 *)(arg0 + 0x14) + b2 * 4));
    }

    *(u16 *)(arg0 + 0x22) = *(u16 *)(arg0 + 0x22) - 1;
    {
        u32 *tp = (u32 *)D_081021D8;
        b = *(u8 *)(target + 0x244);
        sub_08098338((void *)tp[b], gfx);
    }

    pt = D_02021E90;
    layerOff = 0x18A8;
    pb = D_02025FF0 + layerOff;
    idx = ((u32)*pb + 1) * 0x40;
    pt1 = pt + 0x1278;
    v1 = *(u32 *)(pt1 + idx);
    *(u32 *)(gfx + 0x14) = *(u32 *)(target + 0x08) - ((v1 + 0x8000) & 0xFFFF0000);

    idx = ((u32)*pb + 1) * 0x40;
    pt2 = pt + 0x127C;
    v2v = *(u32 *)(pt2 + idx);
    *(u32 *)(gfx + 0x18) = *(u32 *)(target + 0x0C) - ((v2v + 0xFFFF8000) & 0xFFFF0000);
}
