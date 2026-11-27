extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void installUpdateHandler(void *, void *, void *);
extern void sub_08014290(void);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void initSpriteGraphics(void *, u8 *, s32);
extern void setAnimationFrame(void *, u8 *, s32, s32);
struct CameraInfo { u8 _0[0x18C2]; u16 spriteAttrMask; };
extern struct CameraInfo gMainWorkspace;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;
extern u32 gTrigFuncTable;

/* The sprite object created for the entity. */
struct Sprite {
    u16 gfxAttr;
    u8 _[0x1C - 2];
    u32 flags;
};

/* Per-entity actor state reached through entity->actor. */
struct Actor {
    u8 _0[8];
    s32 x;
    s32 y;
    s32 scaleX;
    s32 scaleY;
    u8 _1[0x1C - 0x18];
    s16 id;
    u8 _2[0x22 - 0x1E];
    s16 dirIndex;
};

struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _1[0x14 - 4];
    u32 fnTable;
    u8 _2[0x22 - 0x18];
    s16 dirIndex;
    u32 prevUpdate;
    u8 _3[0x38 - 0x28];
    u32 sprite;
    u32 actor;
    u8 _4[0x4C - 0x40];
    s32 xPos;
    u8 _5[0x5C - 0x50];
    s32 yPos;
    u8 _6[0x6C - 0x60];
    s32 param6C;
    u8 _7[0x7C - 0x70];
    s32 param7C;
};

/* Creates the entity's sprite and 0x48-byte work state, seeds a trig-scaled
 * actor at the entity's position, starts its animation and dispatches the
 * current script step; on allocation failure it calls the saved cleanup. */
void createScaledEntitySprite(struct Entity *entity) {
    struct Sprite *sprite;
    struct Actor *actor;
    u8 *anim;
    s32 ret;
    u8 *ctrlBase;
    u32 v;
    u32 fn;
    s16 pcOffset;
    u16 *pcWords;
    u32 *pfc;
    s16 gfxFrame;
    s16 *dirWords;

    sprite = (struct Sprite *)allocSpriteObject();
    if (sprite == NULL) goto Lend;
    entity->sprite = (u32)sprite;
    allocWorkSlot(entity, 0, 0x48, 0);
    if (entity->actor == 0) goto Lend;
    sprite->flags = 0x8000000B;
    actor = (struct Actor *)entity->actor;
    anim = ((u8 *)actor) + 0x34;
    installUpdateHandler(entity, actor, &sub_08014290);
    actor->id = 0x2D;
    actor->x = entity->xPos;
    actor->y = entity->yPos;
    pfc = &gTrigFuncTable;
    actor->scaleX = (entity->param6C >> 8) * (sub_080C31E0(entity->param7C + 0x4000, *pfc) >> 8);
    actor->scaleY = (entity->param6C >> 8) * (sub_080C31E0(entity->param7C, *pfc) >> 8);
    ret = findKindIndex(actor->id);
    actor->dirIndex = ret;
    if ((ret << 16) >= 0) goto Lcont;
Lend:
    sub_080C31E0((s32)entity, entity->prevUpdate);
    return;
Lcont:
    dirWords = (s16 *)actor;
    gfxFrame = dirWords[0x11];
    sprite->gfxAttr = ((gfxFrame << 6) + 0x200) | ((u16)(ret + 8) << 12);
    sprite->gfxAttr = sprite->gfxAttr | gMainWorkspace.spriteAttrMask;
    initSpriteGraphics((u8 *)sprite, anim, (s32)gSpriteAnimDataTable + actor->id * 0xC);
    setAnimationFrame((u8 *)sprite, anim, 0x14, 0);
    entity->flags = entity->flags | 0x1000;
    pcOffset = entity->dirIndex;
    pcWords = (u16 *)entity;
    ((u8 *)(&pcWords[pcOffset]))[0x19] = 0;
    {
        u32 *scriptData = &gMainObjTimerCallbacks;
        ctrlBase = ((u8 *)entity) + 0x18;
        sub_080C31E4(ctrlBase, ((u8 *)entity) + 0x22, *scriptData);
    }
    pcOffset = entity->dirIndex;
    pcWords = (u16 *)entity;
    ((u8 *)(&pcWords[pcOffset]))[0x19] = ((u8 *)(&pcWords[pcOffset]))[0x19] + 1;
    pcOffset = entity->dirIndex;
    pcWords = (u16 *)ctrlBase;
    {
        u16 *stepEntry = &pcWords[pcOffset];
        v = ((u8 *)stepEntry)[0];
    }
    fn = *((u32 *)(((u8 *)entity->fnTable) + (v * 4)));
    sub_080C31E0((s32)entity, fn);
}
