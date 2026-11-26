/* Global gfx flags mixed into every sprite's base attribute. */
struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
/* Extra object linked to an actor (its state bytes and sprite pointer). */
struct SubObject { u8 _0; u8 f1; u8 f2; u8 f3; u16 f4; u16 f6; u16 f8; u16 fA; u16 fC; u16 fE; u32 f10; };
/* Actor's work buffer: animation index at f1C, kind at f22, sub-object at f28. */
struct HostObject {
    u8 _0[8]; u32 f8; u32 fC; u32 f10; u32 f14; u8 _18[4]; s16 f1C; u8 _1E[4]; s16 f22; u8 _24[4];
    struct SubObject *f28; u8 _2C[8]; u16 a34; u16 a36; u16 a38; u16 a3A;
};
struct ActorContext {
    u16 f0; u16 f2; u8 _4[0x14-0x4]; void *f14; u8 f18; u8 f19; u8 _1A[0x22-0x1A];
    s16 f22; void *f24; u8 _28[0x38-0x28]; void *f38; void * volatile f3C;
    u8 _40[0x4C-0x40]; u32 f4C; u8 _50[0xC]; u32 f5C; u8 _60[0xC]; s32 f6C;
};
/* Per-kind parameter table indexed by the work object's animation index. */
struct SpawnParams { u8 _0[4]; u16 f4; u16 f6; u16 f8; u16 fA; u8 _C[0x1C]; };
extern struct SpawnParams gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];       /* 12-byte animation-data records */
extern u16 D_081019F4[];       /* default values copied into the sub-object */
extern u32 gMainObjTimerCallback;        /* script callback table */
extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern void installUpdateHandler(void *, void *, void *);
extern s32 findKindIndex(void);
extern void initSpriteGraphics(void *, void *, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void *allocEffectPart(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_08097DC8(void);

/* Spawns the sprite and attached sub-object for an actor: reads the actor's
 * kind, builds its sprite attributes and animation from the parameter tables,
 * copies defaults into the sub-object, then advances the actor's script step. */
void sub_0809E57C(struct ActorContext *actor) {
    s32 sprite;
    struct HostObject *work;
    u8 *anim;
    u16 *defaults;
    u32 kind;
    u8 *stepData;
    void **scriptCb;
    u8 *stepEntry;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->f38 = (void *)sprite;
    allocWorkSlot(actor, 0, 0x48, 0);
    if (actor->f3C == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = 0x80000009;
    work = (struct HostObject *)actor->f3C;
    anim = ((u8 *)work) + 0x34;
    installUpdateHandler(actor, (u8 *)work, sub_08097DC8);
    work->f1C = 0x4C;
    kind = findKindIndex();
    work->f22 = kind;
    if ((s16)kind < 0) goto fail;
    kind = work->f22;
    kind = kind << 6;
    kind = kind + 0x200;
    kind &= 0xFC0;
    *((u16 *)sprite) = kind;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    *((u16 *)(sprite + 2)) |= 0x400;
    initSpriteGraphics((void *)sprite, anim, (s32)(gSpriteAnimDataTable + work->f1C * 12));
    setAnimationFrame((void *)sprite, anim, 0, 0);
    defaults = D_081019F4;
    work->f28 = allocEffectPart();
    if (work->f28 == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->f24);
    return;
ok:
    work->f28->f1 = 4;
    work->f28->f2 = 8;
    work->f28->f3 = 1;
    work->f28->f4 = gEffectGfxTable[work->f1C].f4;
    work->f28->f6 = defaults[0];
    work->f28->f8 = defaults[1];
    work->f28->fA = defaults[2];
    work->f28->fC = defaults[3];
    work->f28->fE = gEffectGfxTable[work->f1C].f6;
    work->f28->f10 = (void *)sprite;
    actor->f2 |= 0x1000;
    {
        s16 stepIndex = actor->f22;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) = 0;
    }
    scriptCb = &gMainObjTimerCallback;
    stepData = ((u8 *)actor) + 0x18;
    sub_080C31E4(stepData, ((u8 *)actor) + 0x22, (s32)(*scriptCb));
    {
        s16 stepIndex = actor->f22;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) += 1;
        stepIndex = actor->f22;
        stepEntry = stepData + ((u32)stepIndex * 2);
        sub_080C31E0(actor, *((void **)(actor->f14 + ((*stepEntry) * 4))));
    }
}
