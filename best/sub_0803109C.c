extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *, void *, u8 *);
extern void *allocEffectPart(void);
extern void *allocMotionTracker(void);
extern void sub_08023BDC(u8 *, u8 *);
extern void sub_080C31E0(u8 *, u32);
extern void sub_080C31E4(u8 *, u8 *, u32);
extern void destroyObject(void);
extern u8 gSpriteAnimDataTable[];
extern u16 gSpriteKindTable[];
extern u16 D_080CEBA0[];
extern u32 gMainObjTimerCallbacks;

struct GlobalStateA { u8 _0[0x18A8]; u8 cameraIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GlobalStateA gMainWorkspace;
struct GlobalStateB { u8 _0[0x1278]; u32 coordX; u32 coordY; };
extern struct GlobalStateB gCameraState;

struct P3109C {
    u8 f0;
    u8 f1;
    u8 f2;
    u8 f3;
    u16 f4;
    u16 f6;
    u16 f8;
    u16 fA;
    u16 fC;
    u16 fE;
    u32 f10;
    u16 f14;
};
struct W3109C {
    u8 _0[4];
    u16 f4;
    u8 _6[2];
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    u32 f18;
    s16 f1C;
    u8 _1E[4];
    s16 f22;
    u32 f24;
    struct P3109C *f28;
    u8 _2C[0x1C];
    u32 f48;
};
struct T3109C { u8 _0; u8 f1; u16 f2; u8 _4[2]; u16 f6; u16 f8; u16 fA; u32 fC; };

#define DEF ((s16 *)(*(u32 *)(ctx + 4)))
#define FLAGS (((u16 *)DEF)[3])

void sub_0803109C(u8 *obj) {
    u8 *ctx;
    u8 *sprite;
    struct W3109C *work;
    u8 *gfxInit;
    s32 kindIndex;
    u32 zero;
    u16 *kindTable;
    u32 attrs;
    u8 *cameraBase;

    ctx = *(u8 **)(obj + 0xAC);
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail;
    *(u8 **)(obj + 0x38) = sprite;
    allocWorkSlot(obj, 0, 0x54, 0);
    work = *(struct W3109C **)(obj + 0x3C);
    if (work == NULL) goto fail;
    gfxInit = (u8 *)work + 0x34;
    work->f24 = *(u32 *)(obj + 0x24);
    *(u32 *)(obj + 0x24) = (u32)destroyObject;
    switch (DEF[2]) {
    case 0xD9: work->f1C = 0x0D; break;
    case 0xDA: work->f1C = 0x3F; break;
    case 0xDB: work->f1C = 0x77; break;
    }
    kindTable = gSpriteKindTable;
    work->f18 = kindTable[work->f1C * 10 + 1];
    work->f8 = (u32)DEF[0] << 16;
    work->fC = (u32)DEF[1] << 16;
    kindIndex = findKindIndex(work->f1C);
    zero = 0;
    work->f22 = (s16)kindIndex;
    if ((s16)kindIndex < 0) goto fail;
    work->f4 = 0x10;
    initSpriteGraphics(sprite, gfxInit, gSpriteAnimDataTable + work->f1C * 12);
    work->f28 = allocEffectPart();
    if (work->f28 == NULL) goto fail;
    work->f28->f1 = 0;
    work->f28->f2 = 8;
    work->f28->f3 = 1;
    work->f28->f4 = kindTable[work->f1C * 10];
    work->f28->f6 = D_080CEBA0[0];
    work->f28->f8 = D_080CEBA0[1];
    work->f28->fA = D_080CEBA0[2];
    work->f28->fC = D_080CEBA0[3];
    work->f28->fE = kindTable[work->f1C * 10 + 2];
    work->f28->f10 = (u32)sprite;
    work->f28->f14 = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
            (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
             ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    cameraBase = (u8 *)&gCameraState;
    {
        u32 coordOff = 0x1278;
        *(u32 *)(sprite + 0x14) = work->f8 - ((*(u32 *)(cameraBase + coordOff + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 coordOff = 0x127C;
        *(u32 *)(sprite + 0x18) = work->fC - ((*(u32 *)(cameraBase + coordOff + ((gMainWorkspace.cameraIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    if (FLAGS & 2) {
        *(u32 *)((u8 *)gfxInit + 0x14) = zero;
    } else {
        *(u32 *)((u8 *)gfxInit + 0x14) = (u32)allocMotionTracker();
        if (*(u32 *)((u8 *)gfxInit + 0x14) == 0) goto fail;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->f1 = 1;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->f2 = zero;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->f6 = DEF[0];
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->f6 = DEF[1] + 1;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->f8 = 4;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->fA = 0x14;
        ((struct T3109C *)(*(u32 *)((u8 *)gfxInit + 0x14)))->fC = (u32)obj;
        work->f4 = 0x10;
    }
    if (FLAGS & 1) *(u16 *)(sprite + 2) |= 0x10;
    if (*(u16 *)(*(u32 *)(ctx + 0x14) + 6) & 2) *(u16 *)(sprite + 2) |= 0x20;
    *(u16 *)(sprite + 0x12) = (FLAGS & 2) ? 0 : 1;
    *(u16 *)(sprite + 0x28) = zero;
    sub_08023BDC(obj, sprite);
    *(u16 *)sprite |= 0x1000;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    { const u32 *cb = &gMainObjTimerCallbacks; sub_080C31E4(obj + 0x18, obj + 0x22, *cb); }
    *(u16 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x14) += 1;
    {
        u32 scriptIndex = *(u8 *)(obj + 0x18 + *(s16 *)(obj + 0x22) * 2);
        void *callback = ((void **)*(void **)(obj + 0x14))[scriptIndex];
        sub_080C31E0(obj, (u32)callback);
    }
    return;
fail:
    sub_080C31E0(obj, *(u32 *)(obj + 0x24));
}
