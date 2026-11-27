extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *, s32);
extern void registerScriptObject(u8 *, s32);
extern void randomizePatrolTarget(void *);
extern void updateSpawnedSprite(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern u32 gMainObjTimerCallbacks[];

struct SpriteDef { u8 _0; u8 kind; u8 subkind; u8 state; u16 tile; u16 attr0; u16 attr1; u16 attr2; u16 attr3; u16 mode; u32 sprite; u16 zero; };
struct SpawnedObject { u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u32 frameIndex; s16 kind; u8 _1E[4]; s16 kindIndex; u32 callback; struct SpriteDef *spriteDef; };
struct ScriptRef { s16 x; s16 y; s16 type; };
struct ScriptRefHolder { u8 _0[4]; struct ScriptRef *ref; };
struct ScriptThread { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 menuIndex; u8 _24[0x38-0x24]; u8 *menuItems; struct SpawnedObject *work; u8 _40[0x4C-0x40]; s16 f4C; u8 _4E[6]; s16 f54; u8 _56[0xAC-0x56]; struct ScriptRefHolder *refHolder; };
struct MainWorkspace { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct MainWorkspace gMainWorkspace;
struct CameraState { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct CameraState gCameraState;
struct KindTable { u16 tile; s16 frame; u16 mode; u8 _6[0x14-6]; };
extern struct KindTable gSpriteKindTable[];
extern u16 gSpriteDefaultAttrs4[];
extern u8 gSpriteAnimDataTable[];

/* Spawn-sprite script command: create a sprite and work slot from the thread's
 * script reference, configure it from the kind/animation tables with a jittered
 * patrol target, then make the thread wait and advance to the next command. */
void scriptCmdSpawnSprite4(struct ScriptThread *thread)
{
    u8 *sprite;
    struct SpawnedObject *spawned;
    struct SpawnedObject *newSpawned;
    u8 *animState;
    u8 *spriteDefPtr;
    s32 kindIndex;
    u32 attr;
    u32 zero;
    u8 *cameraBase;
    u8 *kindTable;
    s32 *callbackEntry;
    struct ScriptRefHolder *refHolder;
    s16 refType;
    s32 direction;

    refHolder = thread->refHolder;
    sprite = allocSpriteObject();
    spawned = NULL;
    spriteDefPtr = NULL;
    kindIndex = 0;
    if ((sprite == NULL) ||
        (thread->menuItems = sprite, allocWorkSlot((u8 *)thread, 0, 0x90, 0), newSpawned = thread->work, newSpawned == NULL) ||
        (spawned = newSpawned, animState = (u8 *)spawned + 0x34, spawned->callback = *(u32 *)((u8 *)thread + 0x24), *(u32 *)((u8 *)thread + 0x24) = (u32)updateSpawnedSprite,
         refType = refHolder->ref->type,
         ({ s16 kind; switch (refType) { case SCRIPT_CMD4_REF_A: kind = SCRIPT_CMD4_KIND_A; break; case SCRIPT_CMD4_REF_B: kind = SCRIPT_CMD4_KIND_B; break; default: goto _skip_kind; } spawned->kind = kind; _skip_kind: 0; }),
         kindTable = (u8 *)gSpriteKindTable,
         spawned->frameIndex = ((struct KindTable *)kindTable)[spawned->kind].frame,
         spawned->x = refHolder->ref->x << 16, spawned->y = refHolder->ref->y << 16,
         kindIndex = findKindIndex(spawned->kind), zero = 0, spawned->kindIndex = kindIndex, ((s32)(kindIndex << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + spawned->kind * 0xC), spriteDefPtr = allocEffectPart(), spawned->spriteDef = (struct SpriteDef *)spriteDefPtr, spriteDefPtr == NULL))
    {
        sub_080C31E0(thread, *(u32 *)((u8 *)thread + 0x24));
        return;
    }
    spawned->spriteDef->kind = 0;
    spawned->spriteDef->subkind = 8;
    spawned->spriteDef->state = 1;
    spawned->spriteDef->tile = ((struct KindTable *)kindTable)[spawned->kind].tile;
    spawned->spriteDef->attr0 = gSpriteDefaultAttrs4[0];
    spawned->spriteDef->attr1 = gSpriteDefaultAttrs4[1];
    spawned->spriteDef->attr2 = gSpriteDefaultAttrs4[2];
    spawned->spriteDef->attr3 = gSpriteDefaultAttrs4[3];
    spawned->spriteDef->mode = ((struct KindTable *)kindTable)[spawned->kind].mode;
    spawned->spriteDef->sprite = (u32)sprite;
    spawned->spriteDef->zero = zero;
    attr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)spawned + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)spawned + 0x22) + 8) << 12));
    *(u16 *)sprite = attr;
    *(u16 *)sprite = attr | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    cameraBase = (u8 *)&gCameraState;
    { u32 camOffset = 0x1278; *(u32 *)(sprite + 0x14) = spawned->x - ((*(u32 *)(cameraBase + camOffset + ((gMainWorkspace.mapIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 camOffset = 0x127C; *(u32 *)(sprite + 0x18) = spawned->y - ((*(u32 *)(cameraBase + camOffset + ((gMainWorkspace.mapIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    {
        u8 *anim14 = animState + 0x14;
        u8 *anim30;
        *(u32 *)anim14 = spawned->x;
        *(u32 *)(anim14 + 4) = spawned->y;
        *(u16 *)(anim14 + 0x10) = 0;
        *(u32 *)(anim14 + 0x18) = 0;
        randomizePatrolTarget(thread);
        anim30 = animState + 0x30;
        *(u32 *)anim30 = 0;
        direction = (*(s16 *)(anim14 + 0x10) == 1) ? 0x8000 : 0;
        *(u32 *)(anim30 + 4) = direction;
        *(u32 *)(anim30 + 8) = 0;
        *(u32 *)(anim30 + 0xC) = 0x14000;
        *(u32 *)(anim30 + 0x10) = 0x1000;
        *(u32 *)(anim30 + 0x14) = 0x1000;
    }
    setSpriteFlip(sprite, direction);
    setAnimationFrame(sprite, animState, 0, 1);
    registerScriptObject((u8 *)thread, 0);
    thread->flags |= THREAD_FLAG_WAIT_SPRITE;
    *(u8 *)((u8 *)thread + 2 * thread->menuIndex + 0x19) = 0;
    callbackEntry = (s32 *)gMainObjTimerCallbacks;
    sub_080C31E4((u8 *)thread + 0x18, (u8 *)thread + 0x22, *callbackEntry);
    {
        u32 stateAddr = 2 * (u32)thread->menuIndex;
        u8 *stateByte;
        stateAddr += (u32)thread;
        stateByte = (u8 *)stateAddr;
        *(u8 *)(stateByte + 0x19) = *(u8 *)(stateByte + 0x19) + 1;
    }
    {
        u8 *cmdByte = (u8 *)thread + 0x18;
        cmdByte += thread->menuIndex * 2;
        sub_080C31E0(thread, *(u32 *)(*(u8 **)((u8 *)thread + 0x14) + *cmdByte * 4));
    }
}
