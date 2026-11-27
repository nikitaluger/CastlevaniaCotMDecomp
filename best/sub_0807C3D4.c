void sub_08003A6C(s32, s32, s32);
void *sub_08016190(void *);
void sub_0806D2D0(void *);
s16 sub_0806D62C(u16, s32);
void sub_080722E0(void *, u8);
void sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

struct R8 {
    u8 _0[4];
    s32 f04;
    u8 _08[0x40];
    u8 f48, f49;
    u8 _4A[0xA];
    u8 f54;
};
struct R7 {
    u8 _0;
    s32 f04;
    u8 _08[8];
    u32 f10;
    u8 _14[4];
    u32 f18;
    u8 _1C[0x10];
    void *f2C;
    u32 f30, f34, f38, f3C;
    u32 f40;
    u8 _44[8];
    u32 f4C;
};
struct R3 {
    u8 _0;
    u8 f01, f02, f03;
    u16 f04, f06, f08, f0A, f0C, f0E;
    u8 *f10;
    u8 _14[2];
    u16 f16, f18;
};
struct R5 {
    u8 _0[4];
    u16 f04, f06, f08;
    u8 _0A[0x1A];
    u32 f24;
    u8 _28[0x20];
    u8 f48, f49;
    u8 _4A[0xA];
    u8 f54;
};
extern u8 D_02025FF0[];
extern u8 D_00001510[];
extern u8 D_00001728[];
extern u32 D_0202771C;
extern u8 D_02025368[];

void sub_0807C3D4(u8 *arg0) {
    struct R8 *r8;
    struct R7 *r7;
    struct R5 *r5;
    u8 *base;
    u32 z;

    r8 = *(struct R8 **)(arg0 + 0x6C);
    r7 = (struct R7 *)((u8 *)r8 + 4);
    r5 = *(struct R5 **)(arg0 + 0x38);
    base = D_02025368;
    r7->f2C = sub_08016190(r8);
    if (r7->f2C == NULL) {
        sub_0806D2D0(arg0);
        return;
    }
    z = 0;
    r7->f30 = z;
    r7->f34 = z;
    r7->f38 = z;
    r7->f3C = z;
    ((struct R3 *)r7->f2C)->f01 = *(u8 *)((u32)D_02025FF0 + (u32)D_00001510) & 1;
    ((struct R3 *)r7->f2C)->f02 = 2;
    ((struct R3 *)r7->f2C)->f03 = 8;
    ((struct R3 *)r7->f2C)->f04 = *(u8 *)(base + 0x304);
    ((struct R3 *)r7->f2C)->f06 = 0xA;
    ((struct R3 *)r7->f2C)->f08 = 0xA;
    ((struct R3 *)r7->f2C)->f0A = z;
    ((struct R3 *)r7->f2C)->f0C = z;
    ((struct R3 *)r7->f2C)->f0E = sub_0806D62C(*(u16 *)(base + 0x2E2), 0x20);
    ((struct R3 *)r7->f2C)->f16 = 5;
    ((struct R3 *)r7->f2C)->f18 = 0x60;
    ((struct R3 *)r7->f2C)->f10 = (u8 *)r5;
    r7->f18 = *(u32 *)(arg0 + 0x24);
    *(u32 *)(arg0 + 0x24) = 0x0808449D;
    r5->f24 = 0x084E3A38;
    sub_08003A6C((s32)((u8 *)r8 + 0x20), 0, 0x084E3AF8);
    r8->f04 = *(u32 *)((u32)D_02025FF0 + (u32)D_00001728);
    z = D_0202771C;
    r7->f04 = z + 0xFF800000;
    z = 0;
    r7->f10 = z;
    r7->f40 = 0x4000;
    { int repair_store_value = 0x40; r8->f48 = repair_store_value; }
    r8->f49 = 4;
    sub_080722E0(r7, r8->f48);
    r7->f4C = z;
    r8->f54 = z;
    *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = z;
    {
        u8 *b18 = arg0 + 0x18;
        sub_080C31E4(b18, arg0 + 0x22, *(u32 *)0x08671BB0);
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
        sub_080C31E0((s32)arg0, *(s32 *)(*(u8 *)(b18 + *(s16 *)(arg0 + 0x22) * 2) * 4 + *(u32 *)(arg0 + 0x14)));
    }
}
