void *sub_080015E0(s32, s32);
s32 sub_08000A70(s32, s32, s32);
struct S10 { u8 _[0x10]; };

volatile unsigned short sub_08001614(s32 arg0) {
    sub_080015E0(arg0, (*(s32 *)0x02025B7C) - 0xBC);
}

s32 sub_08001626(u16 *arg0, s32 arg1) {
    s32 v = arg1;
    s16 *pv = (s16 *)&v;
    s32 mask = *arg0 & 0x3FFF;
    s32 r = 0;
    if (pv[0] <= mask && mask <= pv[1]) r = 1;
    return r;
}

void *sub_080015E0(s32 arg0, s32 arg1) {
    u32 p = (u32)(arg1 + 0xBC);
    u32 end = *(u32 *)0x02025B74;
    if (p >= end) return 0;
    do {
        if ((*(s16 *)p & arg0) != 0) return (void *)p;
        p += 0xBC;
    } while (p < end);
    return 0;
}

void sub_08001664(u8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    *(u16 *)(arg0 + 0x34) = (u16)((1 << arg3) | *(u16 *)(arg0 + 0x34));
    *(u32 *)((struct S10 *)(arg0 + 0x3C) + arg3) = sub_08000A70(arg1, arg2, 4);
}
