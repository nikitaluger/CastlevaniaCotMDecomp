extern u16 gAttackEffectAffineParams[];
/* Spawns the fixed-kind (0x4F) attack effect from the thread's position reference:
 * allocates the sprite and work state, configures the render descriptor and
 * animation from the kind tables, places it in screen space, then advances the
 * thread's script state. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern void sub_080530FC(void);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);

extern struct ScriptedEffectWorkspace gMainWorkspace;
extern struct ScriptedEffectScroll gCameraState;
extern struct AttackEffectKindEntry gSpriteKindTable[];
extern u8 gSpriteAnimDataTable[];

void spawnKind4FAttackEffect(struct AttackEffectThread *thread) {
    u8 *sprite;
    struct AttackEffectWork *work;
    u8 *gfxInit;
    u8 *spriteDefPtr;
    s32 slot;
    u32 attrs;
    u32 zero;
    u8 *camera;
    u8 *kindTable;
    s32 *callbackPtr;
    struct EffectPositionHolder *refHolder;
    s32 kindIndex;
    u8 *cmdPtr;

    refHolder = thread->refHolder;
    sprite = allocSpriteObject();
    work = NULL;
    spriteDefPtr = NULL;
    slot = 0;
    if ((sprite == NULL) ||
        (thread->sprite = sprite, allocWorkSlot((u8 *)thread, 0, 0x4C, 0), work = thread->state, work == NULL) ||
        (gfxInit = (u8 *)work + 0x34, work->updateFn = *(u32 *)((u8 *)thread + 0x24), *(u32 *)((u8 *)thread + 0x24) = (u32)sub_080530FC,
         work->kind = SPRITE_KIND_ATTACK_EFFECT,
         kindTable = (u8 *)gSpriteKindTable,
         kindIndex = work->kind, work->param = ((struct AttackEffectKindEntry *)kindTable)[kindIndex].param,
         work->x = refHolder->position->x << 16, work->y = refHolder->position->y << 16,
         slot = findKindIndex(SPRITE_KIND_ATTACK_EFFECT), work->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + work->kind * 0xC), spriteDefPtr = allocEffectPart(), work->spriteDef = (struct AttackEffectSpriteDef *)spriteDefPtr, spriteDefPtr == NULL)) {
        _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
        return;
    }
    zero = 0;
    work->spriteDef->active = 0;
    work->spriteDef->param2 = 8;
    work->spriteDef->param3 = 1;
    work->spriteDef->gfxA = ((struct AttackEffectKindEntry *)kindTable)[work->kind].gfxA;
    work->spriteDef->affine0 = gAttackEffectAffineParams[0];
    work->spriteDef->affine1 = gAttackEffectAffineParams[1];
    work->spriteDef->affine2 = gAttackEffectAffineParams[2];
    work->spriteDef->affine3 = gAttackEffectAffineParams[3];
    work->spriteDef->gfxB = ((struct AttackEffectKindEntry *)kindTable)[work->kind].gfxB;
    work->spriteDef->sprite = (u32)sprite;
    work->spriteDef->timer = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = ATTACK_EFFECT_GFX_ID;
    camera = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(camera + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)((u8 *)work + 0x48) = zero;
    setAnimationFrame(sprite, gfxInit, 0, 1);
    registerScriptObject((u8 *)thread, 0);
    thread->flags |= THREAD_FLAG_WAIT_SPRITE;
    *(u8 *)((u8 *)thread + 2 * thread->stateIndex + 0x19) = 0;
    callbackPtr = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    cmdPtr = (u8 *)thread + 0x18;
    _call_via_r2(cmdPtr, (u8 *)thread + 0x22, *callbackPtr);
    {
        u32 idx2 = 2 * (u32)thread->stateIndex;
        u8 *stateBytePtr;
        idx2 += (u32)thread;
        stateBytePtr = (u8 *)idx2;
        *(u8 *)(stateBytePtr + 0x19) = *(u8 *)(stateBytePtr + 0x19) + 1;
    }
    {
        cmdPtr += thread->stateIndex * 2;
        _call_via_r1((u8 *)thread, *(s32 *)(*(u8 **)((u8 *)thread + 0x14) + *cmdPtr * 4));
    }
}
