/* Allocate the kind-0x87 effect's sprite and work state, save the owner's
 * update handler and install this effect's cleanup, initialise the graphics
 * and screen position from the camera scroll, start the animation, then
 * dispatch the owner's first script step. */
extern void *allocSpriteObject(void);
extern void sub_0801C4BC(void *);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void cleanupKind87Sprite(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Render layer installed in the owner's sprite slot at +0x38. */
struct SpriteDesc { u8 _0; u8 enabled; u8 type; u8 subtype; u16 gfx0; u16 gfx1; u16 gfx2; u16 gfx3; u16 gfx4; u16 frame; u32 owner; u16 tail; };

/* 0x48-byte work block at the owner's +0x3C slot. */
struct MoverState {
    u8 _0[8];
    s32 x;                      /* 0x08: world X, 16.16 */
    s32 y;                      /* 0x0C: world Y, 16.16 */
    u32 velX;                   /* 0x10 */
    u32 velY;                   /* 0x14 */
    u32 flags18;                /* 0x18 */
    s16 anim;                   /* 0x1A: sprite kind */
    u8 _1E[4];
    s16 state;                  /* 0x22: animation slot from findKindIndex */
    u32 prevCallback;           /* 0x24: owner's previous update handler */
    struct SpriteDesc *desc;    /* 0x28 */
};

/* Script-driven owner of the effect. */
struct Entity {
    u8 _0[2];
    u16 flags;                  /* 0x02 */
    u8 _4[0x22 - 4];
    s16 scriptIndex;            /* 0x22: current script step */
    u8 _24[0x38 - 0x24];
    u8 *workObj;                /* 0x38: sprite / render layer */
    struct MoverState *mover;   /* 0x3C: work block */
    u8 _40[0x4C - 0x40];
    s16 posX;                   /* 0x4C */
    u8 _4E[6];
    s16 posY;                   /* 0x54 */
    u8 _56[0x6C - 0x56];
    s16 f5C;
    u8 _5E[0x6C - 0x5E];
    u16 f6C;
};

struct Globals { u8 _0[0x18A8]; u8 frame; u8 _18A9[0x19]; u16 flags; };
extern struct Globals gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 f1278; u32 f127C; };
extern struct ScrollTable gCameraState;
extern u8 gSpriteAnimDataTable[];

void spawnKind87SpriteOnlyEffect(struct Entity *entity) {
    u8 *sprite;
    struct MoverState *work;
    u8 *gfxInit;
    s32 kindIndex;
    u32 attrs;
    u8 *scroll;
    s32 *callbackTable;

    sprite = allocSpriteObject();
    if (sprite == NULL) {
        sub_0801C4BC(entity);
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    entity->workObj = sprite;
    allocWorkSlot((u8 *)entity, 0, KIND87_EFFECT_WORK_SLOT, 0);
    work = entity->mover;
    if (work == NULL) {
        sub_0801C4BC(entity);
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    gfxInit = (u8 *)work + 0x34;
    work->prevCallback = *(u32 *)((u8 *)entity + 0x24);
    *(u32 *)((u8 *)entity + 0x24) = (u32)cleanupKind87Sprite;
    work->anim = SPRITE_KIND_KIND87_EFFECT;
    work->flags18 = 1;
    work->x = entity->posX << 16;
    work->y = entity->posY << 16;
    kindIndex = findKindIndex(SPRITE_KIND_KIND87_EFFECT);
    work->state = kindIndex;
    if ((s32)(kindIndex << 16) < 0) {
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
        return;
    }
    initSpriteGraphics(sprite, gfxInit, (s32)gSpriteAnimDataTable + work->anim * 0xC);
    attrs = (*(u16 *)sprite & 0xC00) |
            (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
             ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.flags;
    *(u32 *)(sprite + 0x1C) = KIND87_EFFECT_GFX_ID;
    scroll = (u8 *)&gCameraState;
    { u32 scrollOff = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(scroll + scrollOff + ((gMainWorkspace.frame + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOff = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(scroll + scrollOff + ((gMainWorkspace.frame + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    setAnimationFrame(sprite, gfxInit, 0x0F, 0);
    entity->flags |= 0x1000;
    *(u8 *)((u8 *)entity + 2 * entity->scriptIndex + 0x19) = 0;
    callbackTable = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callbackTable);
}
