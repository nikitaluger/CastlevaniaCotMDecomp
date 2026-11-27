/* Spawn the kind-0x2F attack sprite: allocate the sprite and a 0x48-byte state
 * block, copy in the parent's pose, fixed-point position and extra parameters,
 * place it in camera space, then consume the parent's script step and call its
 * completion callback. Any allocation or kind-lookup failure runs the parent's
 * cleanup callback instead. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
struct Kind2FAttackState {
    u8 _0[8];
    s32 worldX;
    s32 worldY;
    s32 paramX;
    s32 paramY;
    u8 _18[4];
    s16 kind;
    u8 _1E[4];
    s16 slot;
};
struct Kind2FAttackParent {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 stepIndex;
    u8 _24[0x38-0x24];
    u8 *sprite;
    struct Kind2FAttackState *state;
    u8 _40[0x4C-0x40];
    s16 spawnX;
    u8 _4E[6];
    s16 spawnY;
    u8 _56[0x5C-0x56];
    u32 f5C;
    u8 _60[0x6C-0x60];
    u32 f6C;
    u8 _70[0x7C-0x70];
    u32 paramX;
    u8 _80[0x8C-0x80];
    u32 paramY;
};
struct Kind2FWorkspace { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 attrs; };
extern struct Kind2FWorkspace gMainWorkspace;
struct Kind2FCameraState { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct Kind2FCameraState gCameraState;
extern u8 gSpriteAnimDataTable[];
extern s16 gKind2FPoseFrameTable[];
extern u32 gMainObjTimerCallbacks;

void spawnKind2FAttackSprite(struct Kind2FAttackParent *arg0) {
    u8 *sprite;
    struct Kind2FAttackState *state;
    u8 *scratch;
    s32 slot;
    u32 attrs;
    u8 *coordBase;
    s32 *callback;
    s16 poseIndex;

    sprite = allocSpriteObject();
    state = NULL;
    scratch = NULL;
    slot = 0;
    if ((sprite == NULL) ||
        (arg0->sprite = sprite, allocWorkSlot((u8 *)arg0, 0, 0x48, 0), state = arg0->state, state == NULL) ||
        (scratch = (u8 *)state + 0x34, state->kind = 0x2F,
         state->worldX = arg0->spawnX << 16, state->worldY = arg0->spawnY << 16,
         slot = findKindIndex(0x2F), state->slot = slot, ((s32)(slot << 16) < 0))) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    initSpriteGraphics(sprite, scratch, (s32)gSpriteAnimDataTable + state->kind * 0xC);
    poseIndex = *(s16 *)((u8 *)arg0 + 0x74);
    setAnimationFrame(sprite, scratch, gKind2FPoseFrameTable[poseIndex], 0);

    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.attrs;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    state->paramX = arg0->paramX;
    state->paramY = arg0->paramY;
    coordBase = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->stepIndex + 0x19) = 0;
    callback = (s32 *)&gMainObjTimerCallbacks;
    _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callback);
}
