extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);

/* Work state hung off the main object's +0x3C pointer. */
struct Kind69Work {
    u8 _0[8];
    s32 x;           /* 0x08: world X, 16.16 */
    s32 y;           /* 0x0C: world Y, 16.16 */
    s32 f10;
    s32 f14;
    u8 _18[4];
    s16 kind;        /* 0x1C: SPRITE_KIND_MAIN_OBJ_EFFECT */
    u8 _1E[4];
    s16 slot;        /* 0x22: graphics slot from findKindIndex */
};

/* Main object requesting the effect. */
struct Kind69MainObj {
    u8 _0[2];
    u16 flags;       /* 0x02: EFFECT_SPRITE_READY set on success */
    u8 _4[0x22-4];
    s16 index;       /* 0x22: current script step */
    u8 _24[0x38-0x24];
    u8 *object;      /* 0x38 */
    struct Kind69Work *work; /* 0x3C */
    u8 _40[0x4C-0x40];
    s16 x;           /* 0x4C */
    u8 _4E[6];
    s16 y;           /* 0x54 */
};

struct Kind69Workspace { u8 _0[0x18A8]; u8 frameCounter; u8 _18A9[0x19]; u16 gfxFlags; };
extern struct Kind69Workspace gMainWorkspace;
struct Kind69Scroll { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct Kind69Scroll gCameraState;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;

/* Spawns a kind-0x69 effect for a main object: allocates the sprite and its
 * 0x48-byte work state, seeds the kind and fixed-point position from the object,
 * sets a fixed starting animation frame, places it against the camera scroll, then
 * marks the object ready and dispatches its current script step. */
void spawnKind69MainObjEffect(struct Kind69MainObj *obj) {
    u8 *sprite;
    struct Kind69Work *work;
    u8 *anim;
    s32 slot;
    u32 attrs;
    u8 *scrollBase;
    s32 *callback;

    sprite = allocSpriteObject();
    work = NULL;
    anim = NULL;
    slot = 0;
    if (((sprite == NULL) || ((obj->object = sprite, allocWorkSlot((u8 *)obj, 0, 0x48, 0), work = obj->work, work == NULL))) ||
        ((anim = (u8 *)work + 0x34, work->kind = SPRITE_KIND_MAIN_OBJ_EFFECT, work->x = obj->x << 16, work->y = obj->y << 16,
          slot = findKindIndex(SPRITE_KIND_MAIN_OBJ_EFFECT), work->slot = slot, ((s32)(slot << 16) < 0)))) {
        _call_via_r1((u8 *)obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC);
    setAnimationFrame(sprite, anim, MAIN_OBJ_EFFECT_START_FRAME, 0);
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlags;
    *(u32 *)(sprite + 0x1C) = CHILD_SPRITE_GFX_ID;
    scrollBase = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    obj->flags |= EFFECT_SPRITE_READY;
    *(u8 *)((u8 *)obj + 2 * obj->index + 0x19) = 0;
    callback = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    do { _call_via_r2((u8 *)obj + 0x18, (u8 *)obj + 0x22, *callback); } while (0);
}
