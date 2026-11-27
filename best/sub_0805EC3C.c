extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(void *, s32, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_0805EF90(void);
struct Sprite5EC3C { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; u16 f14; };
struct Ent5EC3C { u8 _0[8]; s32 f8; s32 fC; u8 _10[8]; s32 f18; u8 _1C[8]; s32 f24; struct Sprite5EC3C *f28; };
struct Arg5EC3C { u8 _0[2]; u16 f2; u8 _4[0x10]; u32 *f14; u8 _18[0xA]; s16 f22; s32 f24; u8 _28[0x10]; void *f38; struct Ent5EC3C *f3C; u8 _40[0x6C]; void *fAC; };
struct R8_5EC3C { u8 _0[4]; s16 *f4; };
extern u8 gCameraState[];
extern struct { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; } gMainWorkspace;
extern struct { u8 _0[0x2C]; u16 f2C; } D_080D00EC;
extern vu32 D_040000D4[];
extern u8 D_0865FDF4[];
extern u8 D_0865E2F4[];
extern s32 gMainObjTimerCallbacks[];
void sub_0805EC3C(struct Arg5EC3C *arg0)
{
    u8 *__base_D_0865E2F4;
    void *r8ptr;
    void *obj;
    struct Ent5EC3C *ent;
    s16 *coords;
    struct Sprite5EC3C *spr;
    u32 zero;
    s32 *fp;
    u16 w;
    r8ptr = arg0->fAC;
    obj = allocSpriteObject();
    if (obj == 0) goto fail;
    arg0->f38 = obj;
    allocWorkSlot(arg0, 0, 0x34, 0);
    ent = arg0->f3C;
    if (ent == 0) goto fail;
    ent->f24 = arg0->f24;
    arg0->f24 = (s32)sub_0805EF90;
    ent->f18 = 1;
    coords = ((struct R8_5EC3C *)r8ptr)->f4;
    ent->f8 = (s32)coords[0] << 16;
    ent->fC = (s32)coords[1] << 16;
    spr = allocEffectPart();
    ent->f28 = spr;
    if (spr != 0) goto cont;
fail:
    sub_080C31E0(arg0, arg0->f24);
    return;
cont:
    zero = 0;
    spr->f1 = 4;
    ent->f28->f2 = 0x80;
    ent->f28->f3 = zero;
    ent->f28->f4 = zero;
    ent->f28->f6 = 6;
    ent->f28->f8 = 6;
    ent->f28->fA = zero;
    ent->f28->fC = 0xFFF8;
    ent->f28->fE = zero;
    ent->f28->f10 = (u32)obj;
    ent->f28->f14 = zero;
    *(u16 *)obj |= gMainWorkspace.f18C2;
    *(u32 *)((u8 *)obj + 0x1C) = 0x80000007;
    {
        u8 *base = (u8 *)&gCameraState;
        u32 k = 0x1278;
        *(u32 *)((u8 *)obj + 0x14) = ent->f8 - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    do { {
        u8 *base = (u8 *)&gCameraState;
        u32 k = 0x127C;
        *(u32 *)((u8 *)obj + 0x18) = ent->fC - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    } } while (0);
    do { {
        vu32 *dma = D_040000D4;
        u32 v = D_080D00EC.f2C << 3;
        u8 *t = D_0865FDF4 + v;
        __base_D_0865E2F4 = D_0865E2F4;
        w = *(u16 *)(t + 4);
        dma[0] = (u32)(__base_D_0865E2F4 + ((w & 0xFFF) << 5));
        dma[1] = 0x06017C00;
        dma[2] = 0x80000040;
        (void)dma[2];
    } } while (0);
    *(u32 *)((u8 *)obj + 0x24) = (u32)0x080D00E4;
    *(u16 *)((u8 *)obj + 0x28) = zero;
    *(u16 *)obj |= (u16)(w & 0xF000);
    arg0->f2 |= 0x1000;
    *(u8 *)((u8 *)arg0 + arg0->f22 * 2 + 0x19) = zero;
    fp = gMainObjTimerCallbacks;
    __base_D_0865E2F4 = (u8 *)arg0 + 0x18;
    sub_080C31E4(__base_D_0865E2F4, &arg0->f22, *fp);
    *(u8 *)((u8 *)arg0 + arg0->f22 * 2 + 0x19) += 1;
    __base_D_0865E2F4 += arg0->f22 * 2;
    sub_080C31E0(arg0, arg0->f14[*__base_D_0865E2F4]);
}
