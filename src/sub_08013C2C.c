struct S_02025FF0_1870 {
    u8 _0x000[0x1870];
    void *v;
};
extern struct S_02025FF0_1870 D_02025FF0;

void sub_08014460(void *arg0) {
    void *r3 = arg0;
    void *r0 = *(void **)((u8 *)r3 + 0x28);
    void *r2 = *(void **)((u8 *)r0 + 0x30);
    while (r2 != 0) {
        void *r1 = *(void **)((u8 *)r2 + 0x2C);
        if (r1 == r3) {
            *(void **)((u8 *)r2 + 0x2C) = *(void **)((u8 *)r3 + 0x2C);
            break;
        }
        if (r2 == r3) {
            *(void **)((u8 *)*(void **)((u8 *)r3 + 0x28) + 0x30) = r1;
            break;
        }
        r2 = r1;
    }
    {
        void *g = D_02025FF0.v;
        *(void **)((u8 *)r3 + 0x28) = g;
        *(void **)((u8 *)r3 + 0x2C) = *(void **)((u8 *)g + 0x30);
        *(void **)((u8 *)g + 0x30) = r3;
    }
}

extern void sub_08015974(void);

void sub_08013FAC(void *arg0) {
    u16 t = *(u16 *)((u8 *)arg0 + 0x1E);
    t--;
    *(u16 *)((u8 *)arg0 + 0x1E) = t;
    if ((s16)t <= 0) {
        if (*(void **)((u8 *)arg0 + 0x2C) != 0) {
            sub_08015974();
            *(void **)((u8 *)arg0 + 0x2C) = 0;
        }
        *(u16 *)((u8 *)arg0 + 0) &= 0xFFFB;
    }
}

extern u8 D_02025368[];
extern u8 D_080CB2B8[];

void sub_08013EEC(void *arg0) {
    s32 *dest = (s32 *)(D_02025368 + 0x300);
    s16 idx = *(s16 *)((u8 *)arg0 + 0x1C);
    s32 val = *dest + *(s32 *)(D_080CB2B8 + 8 + idx * 20);
    *dest = val;
    if (val > 0x05F5E0FF) {
        *dest = 0x05F5E0FF;
    }
}

s32 sub_08013C2C(s16 arg0) {
    s16 *p = (s16 *)0x020279F0;
    s32 i;
    for (i = 0; i < 4; i++) {
        if (p[i] == arg0) {
            return i;
        }
    }
    return -1;
}
