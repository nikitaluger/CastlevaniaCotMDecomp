extern void sub_080C31E4(void *, void *, s32);
void sub_0808FA90(void *arg0) {
    u8 *b = *(u8 **)((u8 *)arg0 + 0x3C);
    if (*(u8 *)(b + 0x18) & 2) {
        void **pp;
        *(u8 *)(*(u8 **)(b + 4) + 1) = 0;
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        pp = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
    }
}

s32 sub_0808EA0C(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x30);
    if (p != NULL) {
        do {
            if (*(s16 *)p == 0x20E) return 1;
            p = *(u8 **)(p + 0x2C);
        } while (p != NULL);
    }
    return 0;
}

extern void *sub_08001480(s32, s32);
void *sub_0808E9EC(s32 arg0, s32 arg1) {
    void *r = sub_08001480(arg0, 0x20E);
    if (r != NULL) {
        *(s32 *)((u8 *)r + 0x3C) = arg1;
        return r;
    }
    return NULL;
}

struct S_02025FF0_1874 { u8 _0x000[0x1874]; s32 v; };
extern struct S_02025FF0_1874 D_02025FF0;
extern void *sub_0805FAEC(s32, s32);
void *sub_0808E9AC(s32 arg0, s32 arg1, u16 arg2) {
    void *r = sub_0805FAEC(D_02025FF0.v, 0x20D);
    if (r != NULL) {
        *(s32 *)((u8 *)r + 0x4C) = arg0;
        *(s32 *)((u8 *)r + 0x5C) = arg1;
        *(u16 *)((u8 *)r + 0x6C) = arg2;
        return r;
    }
    return NULL;
}
