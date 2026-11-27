extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);

/* Work state hung off the entity's +0x3C pointer. */
struct Kind29Work {
    u8 _0[8];
    s32 x;           /* 0x08: world X, 16.16 */
    s32 y;           /* 0x0C: world Y, 16.16 */
    s32 f10;
    s32 f14;
    u8 _18[4];
    s16 kind;        /* 0x1C: SPRITE_KIND_FIXED_FRAME_29 */
    u8 _1E[4];
    s16 slot;        /* 0x22: graphics slot from findKindIndex */
};

/* Entity requesting the sprite. */
struct Kind29Entity {
    u8 _0[2];
    u16 flags;       /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _4[0x22-4];
    s16 index;       /* 0x22: current script step */
    u8 _24[0x38-0x24];
    u8 *object;      /* 0x38 */
    struct Kind29Work *work; /* 0x3C */
    u8 _40[0x4C-0x40];
    s16 x;           /* 0x4C */
    u8 _4E[6];
    s16 y;           /* 0x54 */
};

struct Kind29Workspace { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 gfxFlags; };
extern struct Kind29Workspace gMainWorkspace;
struct Kind29Scroll { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct Kind29Scroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;

/* Spawns a kind-0x29 fixed-frame sprite for an entity: allocates the sprite and its
 * 0x48-byte work state, seeds the kind and fixed-point position from the entity, sets
 * a fixed starting animation frame, places it against the camera scroll, then marks
 * the entity ready and dispatches its current script step. */
void spawnKind29FixedFrameSprite(struct Kind29Entity *entity) {
    u8 *sprite;
    struct Kind29Work *work;
    u8 *scratch;
    s32 slot;
    u32 attrs;
    u8 *coordBase;
    s32 *callback;

    sprite = allocSpriteObject();
    work = NULL;
    scratch = NULL;
    slot = 0;
    if (((sprite == NULL) || ((entity->object = sprite, allocWorkSlot((u8 *)entity, 0, 0x48, 0), work = entity->work, work == NULL))) ||
        ((scratch = (u8 *)work + 0x34, work->kind = SPRITE_KIND_FIXED_FRAME_29, work->x = entity->x << 16, work->y = entity->y << 16,
          slot = findKindIndex(SPRITE_KIND_FIXED_FRAME_29), work->slot = slot, ((s32)(slot << 16) < 0)))) {
        if (sprite || slot) {
            _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        } else {
            _call_via_r1((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
    }
    initSpriteGraphics(sprite, scratch, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    setAnimationFrame(sprite, scratch, FIXED_FRAME_29_START_FRAME, 0);
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = CHILD_SPRITE_GFX_ID;
    coordBase = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(coordBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(coordBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    entity->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)entity + 2 * entity->index + 0x19) = 0;
    callback = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    _call_via_r2((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
}
