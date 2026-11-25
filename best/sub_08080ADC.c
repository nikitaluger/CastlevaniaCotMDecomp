void sub_08003A6C(s32, s32, s32);
void *sub_08016190(void *);
void sub_0806D2D0(void *);
s16 sub_0806D62C(u16, u16);
void sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

struct R7 {
    u8 _0[0x18];
    u32 f18;
    u8 _1C[0x10];
    void *f2C;
    u32 f30, f34, f38, f3C;
    u8 _40[0x14];
    u32 f54, f58;
};
struct R3 {
    u8 _0;
    u8 f01, f02, f03;
    u16 f04, f06, f08, f0A, f0C, f0E;
    u8 *f10;
    u8 _14[2];
    u16 f16, f18;
};
struct R4 {
    u8 _0[4];
    u16 f04;
    u8 _06[2];
    u32 f08, f0C;
    u8 f10;
    u8 _11[7];
    u16 f18;
};
struct R5 {
    u8 _0[4];
    u16 f04, f06, f08;
    u8 _0A[0xA];
    u32 f14, f18;
    u8 _1C[8];
    u32 f24;
};
struct S_02025FF0 { u8 _0[0x1510]; u8 f1510; };
extern struct S_02025FF0 D_02025FF0;
struct S_02025368 { u8 _0[0x2E2]; u16 f2E2; u8 _2E4[0x20]; u8 f304; };
extern struct S_02025368 D_02025368;
extern u8 D_080E596C[];
extern u8 D_080E598C[];

void sub_08080ADC(u8 *arg0) {
    u8 *r9;
    struct R7 *r7;
    struct R5 *r5;
    struct R4 *r4;
    u8 *base68;

    r9 = *(u8 **)(arg0 + 0x6C);
    r7 = (struct R7 *)(r9 + 4);
    r5 = (struct R5 *)(*(u8 **)(arg0 + 0x38));
    r7->f2C = sub_08016190(r9);
    if (r7->f2C == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    r7->f30 = 0;
    r7->f34 = 0;
    r7->f38 = 0;
    r7->f3C = 0;
    base68 = (u8 *)&D_02025368;
    {
        u8 idx = *(u8 *)(D_080E596C + *(u32 *)(arg0 + 0x9C));
        r4 = (struct R4 *)(D_080E598C + idx * 28);
    }
    ((struct R3 *)r7->f2C)->f01 = D_02025FF0.f1510 & 1;
    ((struct R3 *)r7->f2C)->f02 = 2;
    ((struct R3 *)r7->f2C)->f03 = 8;
    ((struct R3 *)r7->f2C)->f04 = *(u8 *)(base68 + 0x304);
    ((struct R3 *)r7->f2C)->f06 = 1;
    ((struct R3 *)r7->f2C)->f08 = 1;
    ((struct R3 *)r7->f2C)->f0A = 0;
    ((struct R3 *)r7->f2C)->f0C = 0;
    ((struct R3 *)r7->f2C)->f0E = sub_0806D62C(D_02025368.f2E2, r4->f04);
    ((struct R3 *)r7->f2C)->f16 = 5;
    ((struct R3 *)r7->f2C)->f18 = r4->f18;
    ((struct R3 *)r7->f2C)->f10 = (u8 *)r5;
    r7->f18 = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = 0x0808449D;
    r5->f04 = 0x800;
    r5->f06 = 0x800;
    r5->f08 = 0;
    r5->f24 = r4->f08;
    sub_08003A6C((s32)r9 + 0x20, 0, (s32)r4->f0C);
    r5->f14 = 0x780000;
    r5->f18 = 0x500000;
    r7->f54 = 0;
    r7->f58 = r4->f10;
    {
        u8 *b;
        b = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(b + 0x19) = 0;
    }
    {
        u8 *b;
        b = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *(u32 *)0x08671BB0);
        *(u8 *)(b + 0x19) = *(u8 *)(b + 0x19) + 1;
    }
    {
        s32 i = (s32)(s16)(*(s16 *)(arg0 + 0x22)) * 2;
        u8 *b = arg0 + 0x18 + i;
        u8 byte = *b;
        s32 funcptr = *(s32 *)((u32)(byte * 4) + *(u32 *)(arg0 + 0x14));
        sub_080C31E0((s32)arg0, funcptr);
    }
}
