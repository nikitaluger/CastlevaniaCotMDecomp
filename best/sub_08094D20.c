struct B8 { u8 _0[4]; void *f4; };
struct T { u16 f0; u8 _2[0x12]; u32 f14; u32 f18; u32 f1C; };
struct U { u8 _0; u8 f1; u16 f2; u16 f4; u16 f6; u16 f8; u16 fA; u32 fC; };
struct S { s16 f0; s16 f2; s32 f4; s16 f8; s16 fA; };
struct Sub { s32 f00; struct U *f04; s32 f08; s32 f0C; s32 f10; s32 f14; s32 f18; u16 f1C; u8 _1E[2]; struct S *f20; };
struct C6 { u8 _0[8]; s32 f08; s32 f0C; s32 f10; u8 _14[4]; u32 f18; u8 _1C[8]; u32 f24; u8 _28[0x20]; struct Sub f48; };
struct A { u8 _0[2]; u16 f2; u8 _4[0x10]; u32 f14; u8 _18[0x0A]; s16 f22; u32 f24; u8 _28[0x10]; u32 f38; u32 f3C; u8 _40[0x6C]; void *fAC; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 gCameraState[];
extern u8 D_081008BC[];
extern s16 D_081008C8[];
extern s32 gMainObjTimerCallback[];
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void*, s32, s32, s32);
extern void initSpriteGraphics(void*, void*, void*);
extern void setAnimationFrame(void*, void*, s16, s32);
extern void *allocMotionTracker(void);
extern s32 getSpawnBehaviorIndex(void);
extern struct S *getMotionData(void *);
extern void releaseLinkedThenUpdate(void);
extern void updateAimAtTrackedTarget(void);
extern void sub_080C31E0(void*, s32);
extern void sub_080C31E4(void*, void*, s32);

void sub_08094D20(struct A *arg0) {
    struct B8 *r8;
    void *obj;
    struct C6 *ent;
    struct Sub *sub;
    struct U *t;
    struct S_02025FF0 *p25;
    s16 *c;
    s16 *tbl;
    u32 idx;
    u8 *r9;
    s32 baseY;
    s32 zero;

    r8 = arg0->fAC;
    obj = allocSpriteObject();
    if (obj == 0)
        goto fail;
    arg0->f38 = (u32)obj;
    allocWorkSlot(arg0, 0, 0x6C, 0);
    ent = (struct C6 *)arg0->f3C;
    if (ent == 0)
        goto fail;
    r9 = (u8 *)ent + 0x34;
    ent->f24 = arg0->f24;
    arg0->f24 = (u32)releaseLinkedThenUpdate;
    c = (s16 *)r8->f4;
    ent->f08 = (s32)c[0] << 16;
    ent->f0C = (s32)c[1] << 16;
    p25 = &gMainWorkspace;
    *(u16 *)obj |= p25->f18C2;
    zero = 0;
    ((struct T *)obj)->f1C = 0x8000000C;
    sub = (struct Sub *)((u8 *)ent + 0x48);
    idx = getSpawnBehaviorIndex();
    sub->f00 = idx;
    if ((s32)idx < 0)
        goto fail;
    initSpriteGraphics(obj, r9, D_081008BC + ((idx * 3) << 2));
    sub->f20 = getMotionData(arg0);
    t = allocMotionTracker();
    sub->f04 = t;
    if (t != 0)
        goto body;
fail:
    sub_080C31E0(arg0, arg0->f24);
    goto end;
body:
    sub->f04->f1 = 1;
    sub->f04->f2 = zero;
    sub->f04->f4 = ((u16 *)r8->f4)[0];
    sub->f04->f6 = ((u16 *)r8->f4)[1] + 1;
    { struct U *tt = sub->f04; s32 v8 = sub->f20->f8; tt->f8 = (s16)((v8 + (s32)((u32)v8 >> 31)) >> 1); }
    { struct U *tt = sub->f04; s32 vA = sub->f20->fA; tt->fA = (s16)((vA + (s32)((u32)vA >> 31)) >> 1); }
    sub->f04->fC = (u32)arg0;
    baseY = ent->f08;
    sub->f08 = baseY;
    sub->f0C = baseY + ((s32)sub->f20->f0 << 16);
    { s32 v = sub->f20->f4; if (v < 0) v = -v; sub->f10 = v; }
    ent->f08 = baseY + ((s32)sub->f20->f2 << 16);
    ent->f10 = sub->f20->f4;
    sub->f14 = ent->f08;
    sub->f18 = ent->f0C;
    sub->f1C = zero;
    *(void **)((u8 *)arg0 + 0x9C) = (void *)updateAimAtTrackedTarget;
    tbl = D_081008C8;
    setAnimationFrame(obj, r9, tbl[sub->f00], 1);
    {
        u8 *base = (u8 *)&gCameraState;
        { u32 k = 0x1278; *(u32 *)((u8 *)obj + 0x14) = ent->f08 - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
        { u32 k = 0x127C; *(u32 *)((u8 *)obj + 0x18) = ent->f0C - ((*(u32 *)(base + k + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    }
    arg0->f2 = (u16)(arg0->f2 | 0x1000);
    *(u8 *)((u8 *)arg0 + 0x19 + 2 * arg0->f22) = 0;
    {
        s32 *fp = gMainObjTimerCallback;
        u8 *q = (u8 *)arg0 + 0x18;
        sub_080C31E4(q, &arg0->f22, fp[0]);
        *(u8 *)((u8 *)arg0 + 0x19 + 2 * arg0->f22) = (u8)(*(u8 *)((u8 *)arg0 + 0x19 + 2 * arg0->f22) + 1);
        q += arg0->f22 * 2;
        sub_080C31E0(arg0, *(u32 *)(arg0->f14 + 4 * (*q)));
    }
end:
    return;
}
