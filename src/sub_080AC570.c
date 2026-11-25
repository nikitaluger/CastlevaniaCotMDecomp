extern s32 sub_080AD174(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void *D_08671BB0;

void sub_080AC570(u8 *entity) {
    u8 *base = *(u8 **)(entity + 0x3C);
    u8 *part = base + 0x48;
    s32 *table;

    /* Advance timer and set progression flags as timeline thresholds are reached. */
    *(u32 *)(entity + 4) = *(u32 *)(entity + 4) + 1;
    if (*(u32 *)(entity + 4) > 0x1E && sub_080AD174(base + 0xC8, base + 0xF4) != 0)
        *(s32 *)(base + 0x23C) |= 1;
    if (*(u32 *)(entity + 4) > 0x33 && sub_080AD174(part + 0x80, part + 0x1C4) != 0)
        *(s32 *)(part + 0x1F4) |= 2;
    if (*(u32 *)(entity + 4) > 0x48 && sub_080AD174(part + 0x80, part + 0x188) != 0)
        *(s32 *)(part + 0x1F4) |= 4;
    if (*(u32 *)(entity + 4) > 0x5D && sub_080AD174(part + 0x80, part + 0x174) != 0)
        *(s32 *)(part + 0x1F4) |= 8;
    if (*(u32 *)(entity + 4) > 0x72 && sub_080AD174(part + 0x80, part + 0x1B0) != 0)
        *(s32 *)(part + 0x1F4) |= 0x10;
    if (*(u32 *)(entity + 4) > 0x87 && sub_080AD174(part + 0x80, part + 0xFC) != 0)
        *(s32 *)(part + 0x1F4) |= 0x20;
    if (*(u32 *)(entity + 4) > 0x9C && sub_080AD174(part + 0x80, part + 0x160) != 0)
        *(s32 *)(part + 0x1F4) |= 0x40;
    if (*(u32 *)(entity + 4) > 0xB1 && sub_080AD174(part + 0x80, part + 0x14C) != 0)
        *(s32 *)(part + 0x1F4) |= 0x80;
    if (*(u32 *)(entity + 4) > 0xC6 && sub_080AD174(part + 0x80, part + 0xE8) != 0)
        *(s32 *)(part + 0x1F4) |= 0x100;
    if (*(u32 *)(entity + 4) > 0xDB && sub_080AD174(part + 0x80, part + 0x19C) != 0)
        *(s32 *)(part + 0x1F4) |= 0x200;
    if (*(u32 *)(entity + 4) > 0xF0 && sub_080AD174(part + 0x80, part + 0xD4) != 0)
        *(s32 *)(part + 0x1F4) |= 0x400;
    if (*(u32 *)(entity + 4) > 0x105) {
        if (sub_080AD174(part + 0x80, part + 0x138) != 0)
            *(s32 *)(part + 0x1F4) |= 0x800;
        if (*(u32 *)(entity + 4) > 0x105 && sub_080AD174(part + 0x80, part + 0xC0) != 0)
            *(s32 *)(part + 0x1F4) |= 0x1000;
    }
    if (*(u32 *)(entity + 4) > 0x11A && sub_080AD174(part + 0x80, part + 0x124) != 0)
        *(s32 *)(part + 0x1F4) |= 0x2000;
    if (*(u32 *)(entity + 4) > 0x12C) {
        if (sub_080AD174(part + 0x80, part + 0x98) != 0)
            *(s32 *)(part + 0x1F4) |= 0x4000;
        if (*(u32 *)(entity + 4) > 0x12C && sub_080AD174(part + 0x80, part + 0x110) != 0)
            *(s32 *)(part + 0x1F4) |= 0x8000;
    }
    if (*(u32 *)(entity + 4) > 0x14A && sub_080AD174(part + 0x80, part + 0x84) != 0)
        *(s32 *)(part + 0x1F4) |= 0x10000;
    if (*(u32 *)(entity + 4) > 0x168 && sub_080AD174(part + 0x80, part + 0x1D8) != 0)
        *(s32 *)(part + 0x1F4) |= 0x20000;
    if (*(s32 *)(part + 0x1F4) == 0x3FFFF) {
        u8 *slot = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        slot[0x19] = 0;
        table = &D_08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *table);
    }
}
