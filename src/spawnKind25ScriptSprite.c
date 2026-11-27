extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);
struct ScriptSpriteWork {
    u8 _0[8];
    s32 x;           /* 0x08: world X, 16.16 */
    s32 y;           /* 0x0C: world Y, 16.16 */
    s32 f10;
    s32 f14;
    u8 _18[4];
    s16 kind;        /* 0x1C: SPRITE_KIND_SCRIPTED_SPAWN */
    u8 _1E[4];
    s16 slot;        /* 0x22: graphics slot from findKindIndex */
};
struct ScriptSpriteEntity {
    u8 _0[2];
    u16 flags;       /* 0x02 */
    u8 _4[0x22-4];
    s16 stateIndex;  /* 0x22 */
    u8 _24[0x38-0x24];
    u8 *sprite;      /* 0x38 */
    struct ScriptSpriteWork *state; /* 0x3C */
    u8 _40[0x4C-0x40];
    s16 x;           /* 0x4C */
    u8 _4E[6];
    s16 y;           /* 0x54 */
    u8 _56[0x5C-0x56];
    u32 f5C;
    u8 _60[0x6C-0x60];
    u32 f6C;
    u8 _70[0x74-0x70];
    s16 animTableIndex; /* 0x74: selects the initial animation frame */
};
struct ScriptSpriteWorkspace { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 gfxFlags; };
extern struct ScriptSpriteWorkspace gMainWorkspace;
struct ScriptSpriteScroll { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScriptSpriteScroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern s16 D_080CE8AC[];
extern u32 gMainObjTimerCallbacks;

/* Spawns a kind-0x25 script sprite for an entity: allocates its sprite and 0x48-byte
 * work state, seeds kind, position and initial animation, places it against the
 * camera scroll, then dispatches the entity's current script step. */
void spawnKind25ScriptSprite(struct ScriptSpriteEntity *entity) {
    u8 *sprite;
    struct ScriptSpriteWork *work;
    u8 *scratch;
    s32 slot;
    u32 attrs;
    u8 *coordBase;
    s32 *callback;
    s16 frameIndex;

    sprite = allocSpriteObject();
    work = NULL;
    scratch = NULL;
    slot = 0;
    if (((sprite == NULL) || ((entity->sprite = sprite, allocWorkSlot((u8 *)entity, 0, 0x48, 0), work = entity->state, work == NULL))) ||
        ((scratch = (u8 *)work + 0x34, work->kind = SPRITE_KIND_SCRIPTED_SPAWN, work->x = entity->x << 16, work->y = entity->y << 16,
          slot = findKindIndex(SPRITE_KIND_SCRIPTED_SPAWN), work->slot = slot, ((s32)(slot << 16) < 0)))) {
        if (sprite || slot) {
            _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        } else {
            _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
    }
    initSpriteGraphics(sprite, scratch, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    frameIndex = entity->animTableIndex;
    setAnimationFrame(sprite, scratch, D_080CE8AC[frameIndex], 0);
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = CHILD_SPRITE_GFX_ID;
    coordBase = (u8 *)&gCameraState;
    { u32 coordOff = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 coordOff = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(coordBase + coordOff + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->stateIndex + 0x19) = 0;
    callback = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
}
