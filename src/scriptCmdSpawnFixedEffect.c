/* Script command: spawn the fixed-kind effect at the thread's position reference,
 * configure its sprite, movement data and animation from the kind tables, then
 * advance the thread's command state. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern s32 signOf(s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

/* Effect descriptor (0x34 bytes) allocated by allocEffectPart. */
struct SpriteDef {
    u8 mode;       /* 0x00: playback mode */
    u8 active;     /* 0x01: 0 while spawning */
    u8 param2;     /* 0x02: 8 */
    u8 param3;     /* 0x03: 1 */
    u16 gfxA;      /* 0x04: tile id from the kind table */
    u16 affine0;   /* 0x06: affine/OAM params */
    u16 affine1;   /* 0x08 */
    u16 affine2;   /* 0x0A */
    u16 affine3;   /* 0x0C */
    u16 gfxB;      /* 0x0E: second tile id */
    u32 sprite;    /* 0x10: owner sprite */
    u16 timer;     /* 0x14 */
};

/* Per-effect state held at the thread's +0x3C field. */
struct SpawnState {
    u8 _0[8];
    s32 x;         /* 0x08: world X, 16.16, from the position reference */
    s32 y;         /* 0x0C: world Y, 16.16 */
    u32 f10;
    u32 f14;
    u32 param;     /* 0x18: from the kind table */
    s16 kind;      /* 0x1C: SPRITE_KIND_FIXED_EFFECT here */
    u8 _1E[4];
    s16 slot;      /* 0x22: active-effect slot index */
    u32 updateFn;  /* 0x24: previous update handler, saved here */
    struct SpriteDef *effect; /* 0x28 */
};

struct Ref { s16 x; s16 y; };
struct RefHolder { u8 _0[4]; struct Ref *position; };

struct ScriptThread {
    u8 _0[2];
    u16 flags;     /* 0x02 */
    u8 _4[0x22 - 4];
    s16 stateIndex;/* 0x22 */
    u8 _24[0x38 - 0x24];
    u8 *sprite;    /* 0x38 */
    struct SpawnState *state; /* 0x3C */
    u8 _40[0x4C - 0x40];
    s16 f4C;
    u8 _4E[6];
    s16 f54;
    u8 _56[0xAC - 0x56];
    struct RefHolder *refHolder; /* 0xAC */
};

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 frameCounter; /* 0x18A8: video-frame counter */
    u8 _18A9[0x19];
    u16 gfxFlags;    /* 0x18C2: sprite priority/blend bits */
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 {
    u8 _0[0x1278];
    u32 scrollX;     /* 0x1278: per-frame BG scroll rows */
    u32 scrollY;     /* 0x127C */
};
extern struct S_02021E90 gCameraState;

/* 20-byte per-kind effect table: gfxA, param, gfxB. */
struct EffectDef { u16 gfxA; s16 param; u16 gfxB; u8 _6[0x14 - 6]; };
extern struct EffectDef gSpriteKindTable[];
extern u16 gEffectAffineParams[];
extern u8 gSpriteAnimDataTable[];

/* Extra effect data at state+0x48. */
struct EffectData {
    u32 x, y;       /* 0x00,0x04: spawn position in 16.16 */
    u8 _08[8];
    u16 dirX, dirY; /* 0x10: direction from signOf(x), 0x12: 0 */
    u8 _14[0xC];
    u32 f20;
    u16 f24, f26;
    u16 speed0, speed1, speed2, speed3; /* 0x28..0x2E: fixed movement params */
};

void scriptCmdSpawnFixedEffect(struct ScriptThread *thread) {
    u8 *sprite;
    struct SpawnState *work;
    u32 zero;
    u8 *gfxInit;
    u8 *effectPtr;
    s32 slot;
    u32 attrs;
    u8 *camera;
    u8 *kindTable;
    s32 *callbackPtr;
    struct RefHolder *refHolder;
    s32 kindIndex;
    u8 *effectData;

    refHolder = thread->refHolder;
    sprite = allocSpriteObject();
    work = NULL;
    effectPtr = NULL;
    slot = 0;
    if ((sprite == NULL) ||
        (thread->sprite = sprite, allocWorkSlot((u8 *)thread, 0, 0xC8, 0), work = thread->state, work == NULL) ||
        (gfxInit = (u8 *)work + 0x34, work->updateFn = *(u32 *)((u8 *)thread + 0x24), *(u32 *)((u8 *)thread + 0x24) = 0x080183A5,
         work->kind = SPRITE_KIND_FIXED_EFFECT,
         kindTable = (u8 *)gSpriteKindTable,
         kindIndex = work->kind, work->param = ((struct EffectDef *)kindTable)[kindIndex].param,
         work->x = refHolder->position->x << 16, work->y = refHolder->position->y << 16,
         slot = findKindIndex(SPRITE_KIND_FIXED_EFFECT), work->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + work->kind * 0xC), effectPtr = allocEffectPart(), work->effect = (struct SpriteDef *)effectPtr, effectPtr == NULL)) {
        _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
        return;
    }
    zero = 0;
    work->effect->active = 0;
    work->effect->param2 = 8;
    work->effect->param3 = 1;
    work->effect->gfxA = ((struct EffectDef *)kindTable)[work->kind].gfxA;
    work->effect->affine0 = gEffectAffineParams[0];
    work->effect->affine1 = gEffectAffineParams[1];
    work->effect->affine2 = gEffectAffineParams[2];
    work->effect->affine3 = gEffectAffineParams[3];
    work->effect->gfxB = ((struct EffectDef *)kindTable)[work->kind].gfxB;
    work->effect->sprite = (u32)sprite;
    work->effect->timer = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    effectData = (u8 *)work + 0x48;
    *(u32 *)effectData = work->x;
    ((struct EffectData *)effectData)->y = work->y;
    ((struct EffectData *)effectData)->dirX = signOf(work->x);
    ((struct EffectData *)effectData)->dirY = zero;
    ((struct EffectData *)effectData)->f20 = zero;
    ((struct EffectData *)effectData)->f24 = zero;
    ((struct EffectData *)effectData)->f26 = zero;
    ((struct EffectData *)effectData)->speed0 = 0x1388;
    ((struct EffectData *)effectData)->speed1 = 0x1B58;
    ((struct EffectData *)effectData)->speed2 = 0x1770;
    ((struct EffectData *)effectData)->speed3 = 0x1388;
    setAnimationFrame(sprite, gfxInit, 0, 1);
    registerScriptObject((u8 *)thread, 0);
    thread->flags |= THREAD_FLAG_WAIT_SPRITE;
    *(u8 *)((u8 *)thread + 2 * thread->stateIndex + 0x19) = 0;
    callbackPtr = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    effectData = (u8 *)thread + 0x18;
    _call_via_r2(effectData, (u8 *)thread + 0x22, *callbackPtr);
    {
        u32 idx2 = 2 * (u32)thread->stateIndex;
        u8 *stateBytePtr;
        idx2 += (u32)thread;
        stateBytePtr = (u8 *)idx2;
        *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
    }
    {
        effectData += thread->stateIndex * 2;
        _call_via_r1((u8 *)thread, *(s32 *)(*(u8 **)((u8 *)thread + 0x14) + *effectData * 4));
    }
}
