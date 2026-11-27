extern s32 sub_080AD174(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void *gMainObjTimerCallbacks;

/* Advance the timeline timer; at fixed intervals test each part pair and set its
 * progress bit, then invoke the completion callback once all 18 bits are set. */
void updatePartJoinTimeline(u8 *entity) {
    u8 *parent = *(u8 **)(entity + 0x3C);
    u8 *parts = parent + 0x48;
    s32 *callbackPtr;

    /* Advance timer and set progression flags as timeline thresholds are reached. */
    *(u32 *)(entity + 4) = *(u32 *)(entity + 4) + 1;
    if (*(u32 *)(entity + 4) > 0x1E && sub_080AD174(parent + 0xC8, parent + 0xF4) != 0)
        *(s32 *)(parent + 0x23C) |= 1;
    if (*(u32 *)(entity + 4) > 0x33 && sub_080AD174(parts + 0x80, parts + 0x1C4) != 0)
        *(s32 *)(parts + 0x1F4) |= 2;
    if (*(u32 *)(entity + 4) > 0x48 && sub_080AD174(parts + 0x80, parts + 0x188) != 0)
        *(s32 *)(parts + 0x1F4) |= 4;
    if (*(u32 *)(entity + 4) > 0x5D && sub_080AD174(parts + 0x80, parts + 0x174) != 0)
        *(s32 *)(parts + 0x1F4) |= 8;
    if (*(u32 *)(entity + 4) > 0x72 && sub_080AD174(parts + 0x80, parts + 0x1B0) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x10;
    if (*(u32 *)(entity + 4) > 0x87 && sub_080AD174(parts + 0x80, parts + 0xFC) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x20;
    if (*(u32 *)(entity + 4) > 0x9C && sub_080AD174(parts + 0x80, parts + 0x160) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x40;
    if (*(u32 *)(entity + 4) > 0xB1 && sub_080AD174(parts + 0x80, parts + 0x14C) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x80;
    if (*(u32 *)(entity + 4) > 0xC6 && sub_080AD174(parts + 0x80, parts + 0xE8) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x100;
    if (*(u32 *)(entity + 4) > 0xDB && sub_080AD174(parts + 0x80, parts + 0x19C) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x200;
    if (*(u32 *)(entity + 4) > 0xF0 && sub_080AD174(parts + 0x80, parts + 0xD4) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x400;
    if (*(u32 *)(entity + 4) > 0x105) {
        if (sub_080AD174(parts + 0x80, parts + 0x138) != 0)
            *(s32 *)(parts + 0x1F4) |= 0x800;
        if (*(u32 *)(entity + 4) > 0x105 && sub_080AD174(parts + 0x80, parts + 0xC0) != 0)
            *(s32 *)(parts + 0x1F4) |= 0x1000;
    }
    if (*(u32 *)(entity + 4) > 0x11A && sub_080AD174(parts + 0x80, parts + 0x124) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x2000;
    if (*(u32 *)(entity + 4) > 0x12C) {
        if (sub_080AD174(parts + 0x80, parts + 0x98) != 0)
            *(s32 *)(parts + 0x1F4) |= 0x4000;
        if (*(u32 *)(entity + 4) > 0x12C && sub_080AD174(parts + 0x80, parts + 0x110) != 0)
            *(s32 *)(parts + 0x1F4) |= 0x8000;
    }
    if (*(u32 *)(entity + 4) > 0x14A && sub_080AD174(parts + 0x80, parts + 0x84) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x10000;
    if (*(u32 *)(entity + 4) > 0x168 && sub_080AD174(parts + 0x80, parts + 0x1D8) != 0)
        *(s32 *)(parts + 0x1F4) |= 0x20000;
    if (*(s32 *)(parts + 0x1F4) == 0x3FFFF) {
        u8 *stateByte = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        stateByte[0x19] = 0;
        callbackPtr = &gMainObjTimerCallbacks;
        sub_080C31E4(entity + 0x18, entity + 0x22, *callbackPtr);
    }
}
