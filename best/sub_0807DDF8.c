struct Arg0 { u8 _00[0x14]; u32 f14; u8 _18[0x0A]; s16 f22; u32 f24; u8 _28[0x10]; u32 f38; u8 _3C[0x30]; u32 f6C; };
struct R2 { u8 _00; u8 f01,f02,f03; u16 f04,f06,f08,f0A,f0C,f0E; u32 f10; u8 _14[0x02]; u16 f16,f18; };
struct R6 { u8 _00[0x04]; u32 f04; u8 _08[8]; u32 f10; u8 _14[4]; u32 f18; u8 _1C[0x10]; struct R2 *f2C; u32 f30,f34,f38,f3C; u32 f40; u8 _44[8]; u32 f4C; };
struct R8 { u8 _00[0x04]; u32 f04; u8 _08[0x40]; u8 f48,f49; u8 _4A[0xA]; u8 f54; };
struct R5 { u8 _00[0x04]; u16 f04,f06,f08; u8 _0A[0x1A]; u32 f24; };
extern u8 D_02025368[];
extern u8 D_02025FF0[];
extern u8 D_00001510[];
extern u8 D_00001728[];
extern u32 D_0202771C;
void sub_08003A6C(u32, u32, u32);
void *sub_08016190(void);
void sub_0806D2D0(void *);
u16 sub_0806D62C(u16, u32);
void sub_080722E0(u32, u8);
void sub_080C31E0(u32, u32);
void sub_080C31E4(u32, u32, u32);
extern void sub_0808449C(void);

void sub_0807DDF8(struct Arg0 *arg0) {
    struct R8 *r8 = (struct R8 *)arg0->f6C;
    struct R6 *r6 = (struct R6 *)((u8 *)r8 + 4);
    struct R5 *r5 = (struct R5 *)arg0->f38;
    struct R2 *r2;
    u32 zero;
    u8 *base = D_02025368;
    u8 *r4;
    u32 *g;

    r2 = (struct R2 *)sub_08016190();
    r6->f2C = r2;
    if (r2 == 0) { sub_0806D2D0(arg0); return; }
    zero = 0;
    r6->f30 = zero; r6->f34 = zero; r6->f38 = zero; r6->f3C = zero;
    {
        u32 addr = (u32)D_02025FF0;
        addr += (u32)D_00001510;
        r2->f01 = 1 & *(u8 *)addr;
    }
    r6->f2C->f02 = 2;
    r6->f2C->f03 = 8;
    r6->f2C->f04 = *(u8 *)(base + (0xC1 << 2));
    r6->f2C->f06 = 0x10;
    r6->f2C->f08 = 0x10;
    r6->f2C->f0A = zero;
    r6->f2C->f0C = zero;
    r6->f2C->f0E = sub_0806D62C(*(u16 *)(base + 0x2E2), 0x64);
    r6->f2C->f16 = 0x1E;
    r6->f2C->f18 = 0x64;
    r6->f2C->f10 = (u32)r5;
    r6->f18 = arg0->f24;
    arg0->f24 = (u32)&sub_0808449C;
    r5->f24 = 0x084E7578;
    sub_08003A6C((u32)((u8 *)r8 + 0x20), 0, 0x084E7618);
    {
        u32 addr = (u32)D_02025FF0;
        addr += (u32)D_00001728;
        r8->f04 = *(u32 *)addr;
    }
    r6->f04 = D_0202771C + 0xFF800000;
    r6->f10 = zero;
    r6->f40 = 0x4000;
    r8->f48 = 0x40;
    r8->f49 = 4;
    sub_080722E0((u32)r6, r8->f48);
    r6->f4C = zero;
    r8->f54 = zero;
    *(u8 *)((u8 *)arg0 + (s16)arg0->f22 * 2 + 0x19) = zero;
    g = (u32 *)0x08671BB0;
    r4 = (u8 *)arg0 + 0x18;
    sub_080C31E4((u32)r4, (u32)((u8 *)arg0 + 0x22), *g);
    { u8 *p = (u8 *)((s16)arg0->f22 * 2 + (u32)arg0) + 0x19; *p = *p + 1; }
    r4 += (s16)arg0->f22 * 2;
    sub_080C31E0((u32)arg0, *(u32 *)((u32)arg0->f14 + *(u8 *)r4 * 4));
}
