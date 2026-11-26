struct S_02025FF0 { u8 _0[0x18C2]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
struct P {
    u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u8 _18[4]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct E *f28; u8 _2C[8]; u16 a34; u16 a36; u16 a38; u16 a3A;
};
struct Sarg {
    u16 f0; u16 f2; u8 _4[0x14-0x4]; void *f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A];
    s16 f22; void *f24; u8 _28[0x38-0x28]; void *f38; void * volatile f3C;
    u8 _40[0x4C-0x40]; u32 f4C; u8 _50[0xC]; u32 f5C; u8 _60[0xC]; s32 f6C;
    u8 _70[0x94-0x70]; u16 f94; u8 _96[0x9C-0x96]; u8 f9C;
};
struct CB { u16 f0; u8 _2[2]; u16 f4; u8 _6[0xE]; };
extern struct CB gSpriteKindTable[];
extern u16 D_081020F4[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_08097DC8(void);

void sub_080A8BD8(struct Sarg *arg0) {
    s32 a;
    struct P *p;
    u8 *r7a;
    u16 *t;
    u32 r;
    u32 val;
    s32 idx;
    s32 off;
    u8 *table;

    a = (s32)allocSpriteObject();
    if (a == 0) goto fail;
    arg0->f38 = (void *)a;
    allocWorkSlot(arg0, 0, 0x48, 0);
    if (arg0->f3C == NULL) goto fail;
    *(u32 *)(a + 0x1C) = 0x32 - *(u8 *)((u8 *)arg0 + 0x4C);
    p = (struct P *)arg0->f3C;
    r7a = ((u8 *)p) + 0x34;
    installUpdateHandler(arg0, (u8 *)p, sub_08097DC8);
    p->f1C = 0x5F;
    r = findKindIndex();
    p->f22 = r;
    if ((s16)r < 0) goto fail;
    r = p->f22;
    r = r << 6;
    r = r + 0x200;
    r &= 0xFC0;
    *((u16 *)a) = r;
    *((u16 *)a) |= gMainWorkspace.w;
    idx = p->f1C;
    off = idx * 3;
    table = (u8 *)0x080CD400 + (off * 4);
    initSpriteGraphics((void *)a, r7a, (s32)table);
    setAnimationFrame((void *)a, r7a, 0, 0);
    t = D_081020F4;
    p->f28 = allocEffectPart();
    if (p->f28 == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(arg0, arg0->f24);
    return;
ok:
    p->f28->f1 = 1;
    p->f28->f2 = 8;
    p->f28->f3 = 1;
    p->f28->f4 = gSpriteKindTable[p->f1C].f0;
    p->f28->f6 = t[0];
    p->f28->f8 = t[1];
    p->f28->fA = t[2];
    p->f28->fC = t[3];
    p->f28->fE = gSpriteKindTable[p->f1C].f4;
    p->f28->f10 = (u32)a;
    val = *(u16 *)(a + 4);
    arg0->f94 = val;
    arg0->f9C = 0;
    arg0->f2 |= 0x1000;
    arg0->f2 |= 0x0800;
    *(u32 *)((u8 *)arg0 + 0x14) = 0x080A8D25;
    arg0->f22 = 1;
    sub_080C31E0(arg0, (void *)0x080A8D25);
}
