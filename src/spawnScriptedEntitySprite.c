extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *a, s32 b, s32 c, s32 d);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *a, void *b, s32 c);
extern void setAnimationFrame(void *a, void *b, s32 c, s32 d);
extern void _call_via_r1(void *a, s32 b);
extern void _call_via_r2(void *a, void *b, s32 c);

struct ScriptedSpriteWorkspace {
    u8 _0[0x18A8];
    u8 pageIndex;       /* 0x18A8: active camera-scroll page */
    u8 _18A9[0x19];
    u16 spriteAttrMask; /* 0x18C2: OAM attribute bits ORed into the new sprite */
};
extern struct ScriptedSpriteWorkspace gMainWorkspace;
extern u8 gCameraState[];
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;

/* State block allocated at entity+0x3C. */
struct SpawnedEntityState {
    u8 _0[0x08];
    s32 worldX;       /* 0x08: spawn X, 16.16 */
    s32 worldY;       /* 0x0C: spawn Y, 16.16 */
    u8 _10[0x18-0x10];
    s32 type;         /* 0x18: fixed to 1 here */
    s16 id;           /* 0x1C: entity id / animation selector */
    u8 _1E[4];
    u16 animIndex;    /* 0x22: table index returned by findKindIndex */
};

/* Spawn the sprite and work state for one scripted entity, seed its animation
 * and camera-relative screen position, clear its current script-step action
 * byte, then re-dispatch the script through gMainObjTimerCallbacks. */
void spawnScriptedEntitySprite(u8 *entity) {
    u8 *sprite = allocSpriteObject();
    struct SpawnedEntityState *state;
    u8 *animState;
    u8 *camBase;
    u32 *callbackSlot;

    if (sprite == NULL) goto fail;
    *(u32 *)(entity + 0x38) = (u32)sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    state = (struct SpawnedEntityState *)*(u32 *)(entity + 0x3C);
    if (state == NULL) goto fail;
    animState = (u8 *)state + 0x34;
    state->id = *(u16 *)(entity + 0x6C);
    state->type = 1;
    state->worldX = (s16)*(s16 *)(entity + 0x4C) << 16;
    state->worldY = (s16)*(s16 *)(entity + 0x54) << 16;
    state->animIndex = findKindIndex(state->id);
    if ((s16)state->animIndex >= 0) goto main;
fail:
    _call_via_r1(entity, *(s32 *)(entity + 0x24));
    return;
main:
    initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + state->id * 0xC);
    {
        u16 keptBits = 0xC00 & *(u16 *)sprite;
        s32 rotateAttr = (s16)(*(s16 *)((u8 *)state + 0x22)) << 6;
        rotateAttr += 0x200;
        rotateAttr |= ((u16)(*(u16 *)((u8 *)state + 0x22)) + 8) << 12;
        *(u16 *)sprite = (u16)(keptBits | rotateAttr);
    }
    *(u16 *)sprite = (u16)(*(u16 *)sprite | gMainWorkspace.spriteAttrMask);
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camBase = gCameraState;
    { u32 off = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(camBase + off + ((gMainWorkspace.pageIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 off = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(camBase + off + ((gMainWorkspace.pageIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    if ((s16)*(s16 *)(entity + 0x5C) > 0) {
        *(u16 *)(sprite + 2) |= 0x10;
    }
    setAnimationFrame(sprite, animState, 7, 0);
    *(u16 *)(entity + 2) |= 0x1000;
    *(u8 *)(entity + (s16)*(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
    callbackSlot = &gMainObjTimerCallbacks;
    _call_via_r2(entity + 0x18, entity + 0x22, *callbackSlot);
}
