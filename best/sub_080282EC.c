extern s32 getSpriteFacingSign(void *);
extern void *sub_08028938(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;

void sub_080282EC(u8 *obj) {
    u8 *sprite;
    u8 *state;
    s32 x;
    u8 *script;
    s16 idx;
    s32 base1;
    s32 base2;
    s32 sign;
    s32 cnt;
    s32 *lit;
    u16 temp;
    sprite = *(u8 **)(obj + 0x38);
    state = *(u8 **)(obj + 0x3c);
    script = state + 0x48;

    do { temp = *(u16 *)(script + 0x12); } while (0);
    if (temp & 1) goto inc12;
    do { do { idx = *(s16 *)(script + 0x14); } while (0); } while (0);
    x = (idx * 5 << 12); base1 = x + 0x1C000;
    base2 = *(s32 *)(state + 0xc) - 0x40000;
    sign = getSpriteFacingSign(sprite);
    if (sign < 0) {
        do { do { idx = *(s16 *)(script + 0x14); } while (0); } while (0);
        x = *(s32 *)(state + 8) + (0xa0 << 13);
        sub_08028938(x, base2, (u16)(0x3000 - (idx << 11)), -1,
                     base1, 0x100, *(s16 *)(state + 0x1c));
    } else {
s32 __repair_branch_x_1;

        __repair_branch_x_1 = *(s32 *)(state + 8) - (0xa0 << 13);
        sub_08028938(__repair_branch_x_1, base2, (u16)(((idx << 27) + (0xa0 << 23)) >> 16), 1,
                     base1, 0x100, *(s16 *)(state + 0x1c));
    }
    do { do { cnt = *(u16 *)(script + 0x14) + 1; } while (0); } while (0);
    *(u16 *)(script + 0x14) = cnt;
    if ((s16)cnt <= 4) goto inc12;
    *(u16 *)(script + 0x12) = 0x3c;
    {
        s16 slot;
        slot = *(s16 *)(obj + 0x22);
        *(u8 *)(obj + slot * 2 + 0x19) = 0;
        lit = &gMainObjTimerCallbacks;
        sub_080C31E4(obj + 0x18, obj + 0x22, *lit);
    }
    return;
inc12:
    cnt = *(u16 *)(script + 0x12) + 1;
    *(u16 *)(script + 0x12) = cnt;
}
