/* Script command: spawn a sprite/effect from the thread's script ref at a
 * slightly jittered position, configure its animation and sprite attributes
 * from the kind tables, then idle the thread and advance the command state. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern s32 sub_0800583C(s32);
extern s32 sub_08005820(s32);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

struct SpriteDef {
    u8 _0; u8 kind; u8 subkind; u8 state;
    u16 tile; u16 f6; u16 f8; u16 fA; u16 fC; u16 mode;
    u32 sprite; u16 zero;
};
struct SpawnedObject {
    u8 _0[8];
    s32 x; s32 y;
    u32 f10; u32 f14; u32 frameIndex;
    s16 kind;
    u8 _1E[4];
    s16 kindIndex;
    u32 callback;
    struct SpriteDef *spriteDef;
};
struct ScriptRef { s16 value0; s16 value1; };
struct ScriptRefHolder { u8 _0[4]; struct ScriptRef *ref; };
struct ScriptThread {
    u8 _0[2]; u16 flags;
    u8 _4[0x22-4];
    s16 stateIndex;
    u8 _24[0x38-0x24];
    u8 *sprite;
    struct SpawnedObject *state;
    u8 _40[0x4C-0x40];
    s16 f4C;
    u8 _4E[6];
    s16 f54;
    u8 _56[0xAC-0x56];
    struct ScriptRefHolder *refHolder;
};
struct S_02025FF0 { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct S_02021E90 gCameraState;
struct KindTable { u16 tile; s16 frame; u16 mode; u8 _6[0x14-6]; };
extern struct KindTable gSpriteKindTable[];
extern u16 D_080CFE34[];
extern u8 gSpriteAnimDataTable[];
extern s32 gMainObjTimerCallback;

void scriptCmdSpawnJitteredSprite(struct ScriptThread *thread) {
    u8 *sprite;
    struct SpawnedObject *work;
    u8 *anim;
    struct SpriteDef *spriteDefPtr;
    s32 kindIndex;
    u32 attrs;
    u8 *gfxBase;
    u8 *extra;
    u8 *kindTable;
    s32 kind;
    u32 zero;
    struct ScriptRefHolder *refHolder;
    u8 **extraSlot;

    refHolder = thread->refHolder;
    sprite = allocSpriteObject();
    if (sprite == NULL) goto fail0;
    goto ok0;
fail0:
    _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
    return;
ok0:
    thread->sprite = sprite;
    allocWorkSlot((u8 *)thread, 0, 0x84, 0);
    work = thread->state;
    if (work == NULL) goto fail;
    anim = (u8 *)work + 0x34;
    work->callback = *(u32 *)((u8 *)thread + 0x24);
    *(u32 *)((u8 *)thread + 0x24) = 0x0805C2F5;
    zero = 0;
    work->kind = SPRITE_KIND_JITTERED_SPAWN;
    kindTable = (u8 *)gSpriteKindTable;
    kind = work->kind;
    work->frameIndex = ((struct KindTable *)kindTable)[kind].frame;
    work->x = refHolder->ref->value0 << 16;
    work->y = refHolder->ref->value1 << 16;
    kindIndex = findKindIndex(SPRITE_KIND_JITTERED_SPAWN);
    work->kindIndex = kindIndex;
    if ((s32)(kindIndex << 16) < 0) goto fail;
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    spriteDefPtr = (struct SpriteDef *)allocEffectPart();
    work->spriteDef = spriteDefPtr;
    if (spriteDefPtr == NULL) goto fail;
    goto fields;
fail:
    _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
    return;
fields:
    work->spriteDef->kind = 0;
    work->spriteDef->subkind = 8;
    work->spriteDef->state = 1;
    work->spriteDef->tile = ((struct KindTable *)kindTable)[work->kind].tile;
    work->spriteDef->f6 = D_080CFE34[0];
    work->spriteDef->f8 = D_080CFE34[1];
    work->spriteDef->fA = D_080CFE34[2];
    work->spriteDef->fC = D_080CFE34[3];
    work->spriteDef->mode = ((struct KindTable *)kindTable)[work->kind].mode;
    work->spriteDef->sprite = (u32)sprite;
    work->spriteDef->zero = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    gfxBase = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(gfxBase + k + ((gMainWorkspace.mapIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(gfxBase + k + ((gMainWorkspace.mapIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    extra = (u8 *)work + 0x48;
    *(u32 *)extra = work->x;
    ((u32 *)extra)[1] = work->y;
    extraSlot = &extra;
    ((u32 *)(*extraSlot))[2] = ((u32 *)extra)[0] + sub_0800583C(0x200000);
    ((u32 *)extra)[3] = ((u32 *)extra)[1] + sub_0800583C(0x200000);
    extra += 0x10;
    *(u32 *)((u8 *)work + 0x58) = zero;
    ((u32 *)extra)[1] = sub_08005820(0x10000);
    ((u32 *)extra)[2] = zero;
    ((u32 *)extra)[3] = 0x4000;
    ((u32 *)extra)[4] = 0x80;
    ((u32 *)extra)[5] = 0x80;
    setAnimationFrame(sprite, anim, 0, 1);
    registerScriptObject((u8 *)thread, 0);
    thread->flags |= THREAD_FLAG_WAIT_SPRITE;
    *(u8 *)((u8 *)thread + 2 * thread->stateIndex + 0x19) = 0;
    {
        s32 *lit = (s32 *)0x08671BB0;
        extra = (u8 *)thread + 0x18;
        _call_via_r2(extra, (u8 *)thread + 0x22, *lit);
    }
    {
        u32 idx2 = 2 * (u32)thread->stateIndex;
        u8 *stateBytePtr;
        idx2 += (u32)thread;
        stateBytePtr = (u8 *)idx2;
        *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
    }
    extra += thread->stateIndex * 2;
    _call_via_r1((u8 *)thread, *(s32 *)(*(u8 **)((u8 *)thread + 0x14) + *(u8 *)extra * 4));
}
