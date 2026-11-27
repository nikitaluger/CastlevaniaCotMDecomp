/* Spawns a fixed-kind attack/effect sprite: allocates the sprite and state descriptor,
 * copies the animation script and pose, sets the fixed-point position and extra params
 * from the parent, places it on screen from the shared coordinate tables, then marks
 * the parent's current script step consumed and invokes its callback. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
struct P { u8 _0[8]; s32 x; s32 y; s32 f10; s32 f14; u8 _18[4]; s16 kind; u8 _1E[4]; s16 slot; };
struct Arg0 { u8 _0[2]; u16 flags; u8 _4[0x22-4]; s16 stateIndex; u8 _24[0x38-0x24]; u8 *sprite; struct P *state; u8 _40[0x4C-0x40]; s16 x; u8 _4E[6]; s16 y; u8 _56[0x5C-0x56]; u32 f5C; u8 _60[0x6C-0x60]; u32 f6C; };
struct S_02025FF0 { u8 _0[0x18A8]; u8 f18A8; u8 _18A9[0x19]; u16 f18C2; };
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct S_02021E90 gCameraState;
extern u8 gSpriteAnimDataTable[];
extern s16 D_080CEB20[];
extern u32 gScriptStepCallbackTable;

/* Spawns a kind-0x69 attack sprite: allocates the sprite and its 0x48-byte work state, sets kind 0x69 and the parent's fixed-point coordinates, copies the pose and the two extra params, places it from the camera scroll tables, marks the parent ready, then invokes the step callback. */ void spawnAttackSpriteKind69(struct Arg0 *arg0) {
    u8 *sprite;
    struct P *state;
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
        (scratch = (u8 *)state + 0x34, state->kind = 0x69,
         state->x = arg0->x << 16,
         state->y = arg0->y << 16,
         slot = findKindIndex(0x69), state->slot = slot, ((s32)(slot << 16) < 0))) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    initSpriteGraphics(sprite, scratch, (s32)gSpriteAnimDataTable + state->kind * 0xC);
    poseIndex = *(s16 *)((u8 *)arg0 + 0x7C);
    setAnimationFrame(sprite, scratch, D_080CEB20[poseIndex], 1);

    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.f18C2;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    state->f10 = arg0->f5C;
    state->f14 = arg0->f6C;
    coordBase = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = state->x - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.f18A8 + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = state->y - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.f18A8 + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->stateIndex + 0x19) = 0;
    callback = (s32 *)0x08671BB0;
    _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *callback);
}
