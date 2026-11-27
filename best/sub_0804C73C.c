extern void sub_0804CB80(void);
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *);
extern void setPolarOffset(u8 *, s32, s32);
extern void sub_0804CC18(u8 *, u8 *);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct E { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct P { u8 _0[8]; s32 f8; s32 fC; u32 f10; u32 f14; u32 f18; s16 f1C; u8 _1E[4]; s16 f22; u32 f24; struct E *f28; u8 _2C[0x48-0x2C]; u32 f48; };
struct Arg0 { u8 _0[0x7E]; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 gCameraState;
struct TBL { u8 _0[4]; u16 f4; u16 f6; u8 _8[0x28-8]; };
extern struct TBL gEffectGfxTable[];
extern u16 D_080CF9A8[];
extern u8 gSpriteAnimDataTable[];

void sub_0804C73C(struct Arg0 *arg0) {
    u8 *obj;
    struct P *r5;
    u8 *r9;
    u8 *s;
    s32 r0_3;
    u32 tmp;
    u32 zero;
    u8 *base;
    s32 *fp;

    obj = allocSpriteObject();
    r5 = NULL;
    r9 = NULL;
    r0_3 = 0;
    if ((obj == NULL) ||
        (*(u8 **)((u8 *)arg0 + 0x38) = obj, allocWorkSlot((u8 *)arg0, 0, 0x4C, 0), r5 = *(struct P **)((u8 *)arg0 + 0x3C), r5 == NULL) ||
        (r9 = (u8 *)r5 + 0x34, r5->f24 = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0804CB80,
         r5->f1C = *(u16 *)((u8 *)arg0 + 0x7C), r5->f18 = 1,
         r5->f8 = *(s16 *)((u8 *)arg0 + 0x4C) << 16, r5->fC = *(s16 *)((u8 *)arg0 + 0x54) << 16,
         r0_3 = findKindIndex(r5->f1C), r5->f22 = r0_3, ((s32)(r0_3 << 16) < 0)) ||
        (initSpriteGraphics(obj, r9, (s32)gSpriteAnimDataTable + r5->f1C * 0xC), s = allocEffectPart(), r5->f28 = (struct E *)s, s == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    zero = 0;
    r5->f28->f1 = zero;
    r5->f28->f2 = 8;
    r5->f28->f3 = 1;
    r5->f28->f4 = gEffectGfxTable[r5->f1C].f4;
    r5->f28->f6 = D_080CF9A8[0];
    r5->f28->f8 = D_080CF9A8[1];
    r5->f28->fA = D_080CF9A8[2];
    r5->f28->fC = D_080CF9A8[3];
    r5->f28->fE = gEffectGfxTable[r5->f1C].f6;
    r5->f28->f10 = (u32)obj;
    r5->f28->f14 = zero;
    tmp = (*(u16 *)obj & 0xC00) |
          (((*(s16 *)((u8 *)r5 + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)r5 + 0x22) + 8) << 12));
    *(u16 *)obj = tmp;
    *(u16 *)obj = tmp | gMainWorkspace.f18C2;
    *(u32 *)(obj + 0x1C) = 0x8000000A;
    base = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(obj + 0x14) = r5->f8 - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(obj + 0x18) = r5->fC - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    r5->f48 = *(u16 *)((u8 *)arg0 + 0x5C);
    setSpriteFlip(obj);
    setAnimationFrame(obj, r9, 0x0C, 0x00);
    setPolarOffset((u8 *)r5, r5->f48, *(u32 *)((u8 *)arg0 + 0x6C));
    sub_0804CC18((u8 *)arg0, obj);
    *(u16 *)((u8 *)arg0 + 0x02) |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * *(s16 *)((u8 *)arg0 + 0x22) + 0x19) = zero;
    fp = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *fp);
}
