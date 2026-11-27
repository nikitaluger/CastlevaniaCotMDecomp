extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setSpriteFlipForDirection(u8 *);
extern void sub_08031F04(void);
extern void sub_080C31E0(u8 *, void *);
extern void sub_080C31E4(u8 *, u8 *, void *);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 f8; s32 fC; u32 f10; u32 f14; u32 f18; s16 f1C; u8 _1E[4]; s16 f22; u32 f24; struct E *f28; };
struct Arg0 { u8 _0[2]; u16 f2; u8 _4[0x14-0x4]; u32 f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A]; s16 f22; u32 f24; u8 _28[0x38-0x28]; u8 *f38; struct P *f3C; u8 _40[0x4C-0x40]; s16 f4C; u8 _4E[6]; s16 f54; u8 _56[0x5C-0x56]; u32 f5C; u8 _60[0x6C-0x60]; u32 f6C; u8 _70[0x7C-0x70]; u16 f7C; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 gCameraState;
struct TBL { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x28-8]; };
extern struct TBL gEffectGfxTable[];
extern u16 gStateEffectAffineParams[];
extern u8 gSpriteAnimDataTable[];
extern u32 gScriptStepCallbackTable;

void sub_08031B60(struct Arg0 *arg0) {
    u8 *obj;
    struct P *p;
    u8 *q;
    u8 *s;
    s32 v;
    u32 tmp;
    u32 zero;
    u32 one;
    u8 *base;
    u8 *a18;
    void **fp;
    u32 t5c;

    obj = allocSpriteObject();
    if (obj == 0) goto fail;
    arg0->f38 = obj;
    allocWorkSlot((u8 *)arg0, 0, 0x48, 0);
    p = arg0->f3C;
    if (p == 0) goto fail;
    q = (u8 *)p + 0x34;
    p->f24 = *(u32 *)((u8 *)arg0 + 0x24);
    *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_08031F04;
    p->f1C = (s16)arg0->f7C;
    zero = 0;
    one = 1;
    p->f18 = one;
    p->f8 = arg0->f4C << 16;
    p->fC = arg0->f54 << 16;
    v = findKindIndex(p->f1C);
    p->f22 = v;
    if ((v << 16) < 0) goto fail;
    initSpriteGraphics(obj, q, (s32)gSpriteAnimDataTable + p->f1C * 0xC);
    s = allocEffectPart();
    p->f28 = (struct E *)s;
    if (s == 0) goto fail;
    goto body;
fail:
    sub_080C31E0((u8 *)arg0, *(void **)((u8 *)arg0 + 0x24));
    return;
body:
    p->f28->f1 = zero;
    p->f28->f2 = 8;
    p->f28->f3 = one;
    p->f28->f4 = gEffectGfxTable[p->f1C].f4;
    p->f28->f6 = gStateEffectAffineParams[0];
    p->f28->f8 = gStateEffectAffineParams[1];
    p->f28->fA = gStateEffectAffineParams[2];
    p->f28->fC = gStateEffectAffineParams[3];
    p->f28->fE = gEffectGfxTable[p->f1C].f6;
    p->f28->f10 = (u32)obj;
    p->f28->f14 = zero;
    tmp = (*(u16 *)obj & 0xC00) |
          (((*(s16 *)((u8 *)p + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)p + 0x22) + 8) << 12));
    *(u16 *)obj = tmp;
    *(u16 *)obj = tmp | gMainWorkspace.f18C2;
    *(u32 *)(obj + 0x1C) = 0x8000000A;
    base = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(obj + 0x14) = p->f8 - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(obj + 0x18) = p->fC - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    t5c = arg0->f5C;
    p->f10 = t5c;
    p->f14 = arg0->f6C;
    setSpriteFlipForDirection(obj);
    *(u16 *)(obj + 0x28) = 0x45;
    arg0->f2 |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) = zero;
    fp = (void **)0x08671BB0;
    a18 = (u8 *)arg0 + 0x18;
    sub_080C31E4(a18, (u8 *)arg0 + 0x22, *fp);
    *(u8 *)((u8 *)arg0 + 2 * arg0->f22 + 0x19) += 1;
    {
        s16 idx = arg0->f22;
        a18 += idx * 2;
        {
            u8 b = *a18;
            void *fn = *(void **)((u8 *)arg0->f14 + b * 4);
            sub_080C31E0((u8 *)arg0, fn);
        }
    }
}
