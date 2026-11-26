extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void initSpriteGraphics(void *, void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern u32 findKindIndex(void);
extern void installUpdateHandler(void *, void *, void *);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08014290(void);

struct Arg0 {
    u8 _0[2];
    u16 f02;
    u8 _4[0x10];
    u32 f14;
    u8 _18[0xA];
    s16 f22;
    u32 f24;
    u8 _28[0x10];
    u32 f38;
    u32 f3C;
    u8 _40[0xC];
    u32 f4C;
    u8 _50[0xC];
    u32 f5C;
    u8 _60[0xC];
    u8 f6C;
    u8 _6D[3];
    u8 f70;
};
struct A4 {
    u16 f00;
    u16 f02;
    u8 _04[0x10];
    u32 f14;
    u32 f18;
    u32 f1C;
};
struct P28 {
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
struct P4 {
    u8 _0[8];
    u32 f08;
    u32 f0C;
    u8 _10[0xC];
    s16 f1C;
    u8 _20[4];
    s16 f22;
    u32 f24;
    struct P28 *f28;
};
struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 f18A8;
    u8 _1[0x19];
    u16 f18C2;
};
struct AnimTable { u8 _0[4]; u16 baseTile; u16 extra; u8 _8[0x28-8]; };
extern struct AnimTable gEffectGfxTable[];
extern u16 D_080CEF30[];
extern u8 gCameraState[];
extern struct S_02025FF0 gMainWorkspace;
extern u32 gMainObjTimerCallback;

/* Initialises a newly spawned object: allocates its sprite, configures the
 * sub-object's animation, palette and particle entry, places it relative to
 * the camera, then starts the object's action script. */
void sub_0803657C(struct Arg0 *arg0)
{
    struct A4 *sprite;
    struct P4 *sub;
    u8 *entry;
    u8 *anim;
    u32 v;
    u32 flags;
    u32 *tablePtr;
    u8 *step1;
    u8 *step2;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        sub_080C31E0(arg0, (void *)arg0->f24);
        return;
    }
    arg0->f38 = (u32)sprite;
    allocWorkSlot(arg0, 0, 0x64, 0);
    if (arg0->f3C == 0) {
        sub_080C31E0(arg0, (void *)arg0->f24);
        return;
    }
    sprite->f1C = 0x80000009;
    sub = (struct P4 *)(*(void *volatile *)((u8 *)arg0 + 0x3C));
    anim = (u8 *)sub + 0x34;
    installUpdateHandler(arg0, sub, (void *)sub_08014290);
    sub->f1C = 0x1A;
    v = findKindIndex();
    sub->f22 = (u16)v;
    if ((s32)((u16)v << 16) < 0) {
        sub_080C31E0(arg0, (void *)arg0->f24);
        return;
    }
    flags = ((u32)((s32)sub->f22 << 6)) + 0x200;
    flags |= (v + 8) << 12;
    sprite->f00 = (u16)flags;
    sprite->f00 |= gMainWorkspace.f18C2;
    sub->f08 = arg0->f4C;
    sub->f0C = arg0->f5C;
    if (arg0->f6C)
        sprite->f02 |= 0x10;
    else
        sprite->f02 &= 0xFFEF;
    initSpriteGraphics(sprite, anim, (void *)0x080CD538);
    if (arg0->f70)
        setAnimationFrame(sprite, anim, 0x12, 0);
    else
        setAnimationFrame(sprite, anim, 0x0D, 0);
    {
        u16 *palette = D_080CEF30;
        entry = allocEffectPart();
        sub->f28 = (struct P28 *)entry;
        if (entry == NULL) {
            sub_080C31E0(arg0, (void *)arg0->f24);
            return;
        }
        ((struct P28 *)entry)->f1 = 1;
        sub->f28->f2 = 8;
        sub->f28->f3 = 1;
        sub->f28->f4 = gEffectGfxTable[sub->f1C].baseTile;
        sub->f28->f6 = palette[0];
        sub->f28->f8 = palette[1];
        sub->f28->fA = palette[2];
        sub->f28->fC = palette[3];
        sub->f28->fE = gEffectGfxTable[sub->f1C].extra;
        sub->f28->f10 = (u32)sprite;
    }
    {
        u8 *cam = gCameraState;
        u32 off;
        off = 0x1278;
        sprite->f14 = sub->f08 - ((*(u32 *)(cam + off + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000);
        off = 0x127C;
        sprite->f18 = sub->f0C - ((*(u32 *)(cam + off + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000);
    }
    arg0->f02 |= 0x1000;
    step1 = (u8 *)(((u32)arg0->f22 * 2) + (u32)arg0);
    step1[0x19] = 0;
    tablePtr = &gMainObjTimerCallback;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)(*tablePtr));
    step2 = (u8 *)(((u32)arg0->f22 * 2) + (u32)arg0);
    step2[0x19] = step2[0x19] + 1;
    {
        u8 *script = (u8 *)arg0 + 0x18;
        s32 stepOffset = arg0->f22 * 2;
        u8 command = *(script + stepOffset);
        sub_080C31E0(arg0, *((void **)((u8 *)arg0->f14 + (command * 4))));
    }
}
