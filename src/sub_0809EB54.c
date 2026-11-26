struct GlobalState { u8 _0[0x18C2]; u16 gfxFlags; };
extern struct GlobalState gMainWorkspace;
struct SubObject { u8 _0; u8 flag; u8 type; u8 subType; u16 gfxA; u16 p0; u16 p1; u16 p2; u16 p3; u16 gfxB; u32 sprite; };
struct HostObject {
    u8 _0[8]; s32 x; s32 y; u32 f10; u32 f14; u8 _18[4]; s16 kind; u8 _1E[4]; s16 slot; u8 _24[4];
    struct SubObject *spriteDef;
};
struct ActorContext {
    u16 flags0; u16 flags; u8 _4[0x14-0x4]; void *commandTable; u8 stepBytes[0x22-0x18];
    s16 stepIndex; void *updateFn; u8 _28[0x38-0x28]; void *sprite; void * volatile state;
    u8 _40[0x4C-0x40]; u32 f4C;
};
struct SpawnParams { u8 _0[4]; u16 gfxA; u16 gfxB; u16 p0; u16 p1; u8 _C[0x1C]; };
extern struct SpawnParams gEffectGfxTable[];
extern u8 gSpriteAnimDataTable[];
extern u16 D_081019FC[];
extern u32 gMainObjTimerCallback;
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

/* Allocates and initialises a projectile/throwable entity: grabs a sprite,
 * installs a cleanup callback on its state object, picks a kind/slot, sets the
 * animation and graphics, fills the sprite definition, then installs the
 * script callback; on any allocation failure it falls back to the actor's
 * stored update callback. */
void sub_0809EB54(struct ActorContext *actor) {
    s32 sprite;
    struct HostObject *state;
    u8 *animState;
    u16 *defaultParams;
    u32 slot;
    u8 *scriptData;
    void **scriptTable;
    u8 *commandPtr;
    u8 zero;

    sprite = (s32)allocSpriteObject();
    if (sprite == 0) goto fail;
    actor->sprite = (void *)sprite;
    allocWorkSlot(actor, 0, 0x48, 0);
    if (actor->state == NULL) goto fail;
    *((u32 *)(sprite + 0x1C)) = 0x8000000A;
    state = (struct HostObject *)actor->state;
    animState = ((u8 *)state) + 0x34;
    installUpdateHandler(actor, (u8 *)state, sub_08097DC8);
    zero = 0;
    state->kind = 0x4C;
    slot = findKindIndex();
    state->slot = slot;
    if ((s16)slot < 0) goto fail;
    slot = state->slot;
    slot = slot << 6;
    slot = slot + 0x200;
    slot &= 0xFC0;
    *((u16 *)sprite) = slot;
    *((u16 *)sprite) |= gMainWorkspace.gfxFlags;
    initSpriteGraphics((void *)sprite, animState, (s32)(gSpriteAnimDataTable + state->kind * 12));
    setAnimationFrame((void *)sprite, animState, 5, 0);
    *((u8 *)sprite + 0x2A) &= 0xBF;
    defaultParams = D_081019FC;
    state->spriteDef = allocEffectPart();
    if (state->spriteDef == NULL) goto fail;
    goto ok;
fail:
    sub_080C31E0(actor, actor->updateFn);
    return;
ok:
    state->spriteDef->flag = zero;
    state->spriteDef->type = 8;
    state->spriteDef->subType = 1;
    state->spriteDef->gfxA = gEffectGfxTable[state->kind].gfxA;
    state->spriteDef->p0 = defaultParams[0];
    state->spriteDef->p1 = defaultParams[1];
    state->spriteDef->p2 = defaultParams[2];
    state->spriteDef->p3 = defaultParams[3];
    state->spriteDef->gfxB = gEffectGfxTable[state->kind].gfxB;
    state->spriteDef->sprite = (void *)sprite;
    actor->flags |= 0x1000;
    {
        s16 stepIndex = actor->stepIndex;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) = zero;
    }
    scriptTable = &gMainObjTimerCallback;
    scriptData = ((u8 *)actor) + 0x18;
    sub_080C31E4(scriptData, ((u8 *)actor) + 0x22, (s32)(*scriptTable));
    {
        s16 stepIndex = actor->stepIndex;
        *((u8 *)(((u32)stepIndex * 2) + (u32)actor + 0x19)) += 1;
        stepIndex = actor->stepIndex;
        commandPtr = scriptData + ((u32)stepIndex * 2);
        sub_080C31E0(actor, *((void **)(actor->commandTable + ((*commandPtr) * 4))));
    }
}
