void sub_080C31E4(void *, void *, s32);
void *sub_0805FAEC(s32, s32);

struct S_02025FF0 { u8 _p[0x1870]; u32 v; };
extern struct S_02025FF0 D_02025FF0;

void sub_0801E12A(void *arg0) {
    u8 *p = *(u8 **)((u8 *)arg0 + 0x3C) + 0x48;
    s32 zero = 0;
    void **pp;
    *(u16 *)(p + 8) = 0xA;
    *(u16 *)(p + 0x28) = 6;
    ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
    pp = (void **)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*pp);
}

struct R_1DAB4 {
    u8 _p0[0x4C];
    u16 f4C;
    u8 _p1[0x54 - 0x4E];
    u16 f54;
    u16 f5C;
    u8 _p2[0x6C - 0x5E];
    u32 f6C;
};

void *sub_0801DAB4(s16 a0, s16 a1, s16 a2, s32 a3) {
    struct R_1DAB4 *r1;
    void *result;
    r1 = (struct R_1DAB4 *)sub_0805FAEC(D_02025FF0.v, 0x93);
    if (r1 != NULL) {
        u16 *p = &r1->f4C;
        *p = a0;
        p += 4;
        *p = a1;
        p += 4;
        *p = a2;
        r1->f6C = a3;
        result = r1;
    } else {
        result = NULL;
    }
    return result;
}

void *sub_0801D618(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *r2;
    s32 v0, v1;
    r2 = sub_0805FAEC(D_02025FF0.v, 0x92);
    if (r2 == NULL) return NULL;
    v0 = arg0;
    if (v0 < 0) v0 += 0xFFFF;
    *(s16 *)((u8 *)r2 + 0x4C) = (s16)(v0 >> 16);
    v1 = arg1;
    if (v1 < 0) v1 += 0xFFFF;
    *(s16 *)((u8 *)r2 + 0x54) = (s16)(v1 >> 16);
    *(u32 *)((u8 *)r2 + 0x5C) = arg2;
    *(u32 *)((u8 *)r2 + 0x6C) = arg3;
    return r2;
}

s32 sub_0801D616(s32 arg0) { return arg0; }
