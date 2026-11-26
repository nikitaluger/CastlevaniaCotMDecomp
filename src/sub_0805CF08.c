extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void sub_0805D90C(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

/* Graphics/animation descriptor hung off the spawned effect object. */
struct EffectGfx {
    u8 _0;
    u8 type;
    u8 layer;
    u8 priority;
    u16 gfxIndex;
    u16 anim0, anim1, anim2, anim3;
    u16 palette;
    u32 object;
    u16 tail;
};
/* Effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;
    s32 worldY;
    u32 f10;
    u32 f14;
    u32 f18;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateCb;
    struct EffectGfx *gfx;
    u8 _2C[0x48 - 0x2C];
    u32 ext;
};
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22 - 4];
    s16 index;
    u8 _24[0x38 - 0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C - 0x40];
    s32 worldX;
    s32 worldY;
    u8 _54[0x6C - 0x54];
    u16 kind;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
extern s16 D_080D002C[];

/* Spawn a graphics effect from a main object's parameter block at +0x4C: allocate
   a free object, build its EffectGfx and position it with the scroll offset. */
void sub_0805CF08(struct MainObj *mainObj)
{
    u8 *params;
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    short two;
    u8 *gfx;
    u8 *ext;
    u32 zero;
    u8 *gameState;
    u8 *scrollTable;
    u8 *tablePtr;
    s32 *audioCmd;

    params = ((u8 *)mainObj) + 0x4C;
    effect = allocSpriteObject();
    owner = NULL;
    gfx = NULL;
    anim = NULL;
    if (((effect == NULL) || ((mainObj->object = effect, allocWorkSlot((u8 *)mainObj, 0, 0x54, 0), owner = mainObj->effect, owner == NULL))) || ((anim = ((u8 *)owner) + 0x34, owner->updateCb = *((u32 *)(((u8 *)mainObj) + 0x24)), *((u32 *)(((u8 *)mainObj) + 0x24)) = (u32)sub_0805D90C, owner->f18 = 1, owner->worldX = mainObj->worldX, owner->worldY = *((s32 *)(params + 4)), initSpriteGraphics(effect, anim, (s32)0x080D0020), setAnimationFrame(effect, anim, D_080D002C[(*((u16 *)(params + 8))) & 0xF], 1), gfx = allocEffectPart(), owner->gfx = (struct EffectGfx *)gfx, gfx == NULL)))
    {
        sub_080C31E0((u8 *)mainObj, *((s32 *)(((u8 *)mainObj) + 0x24)));
        return;
    }
    zero = 0;
    ((struct EffectGfx *)gfx)->type = 4;
    owner->gfx->layer = 0x80;
    owner->gfx->priority = zero;
    owner->gfx->gfxIndex = zero;
    owner->gfx->anim0 = 5;
    owner->gfx->anim1 = 5;
    owner->gfx->anim2 = zero;
    owner->gfx->anim3 = 0xFFFA;
    owner->gfx->palette = zero;
    two = 2;
    owner->gfx->object = (u32)effect;
    owner->gfx->tail = zero;
    *((u16 *)effect) |= gMainWorkspace.flags;
    *((u32 *)(effect + 0x1C)) = 0x80000007;
    gameState = (u8 *)(&gMainWorkspace);
    scrollTable = (u8 *)(&gCameraState);
    {
        u32 k = 0x1278;
        *((u32 *)(effect + 0x14)) = owner->worldX - (((*((u32 *)((scrollTable + k) + (((*((u8 *)(gameState + 0x18A8))) + 1) << 6)))) + 0x8000) & 0xFFFF0000);
    }
    {
        u32 k = 0x127C;
        *((u32 *)(effect + 0x18)) = owner->worldY - (((*((u32 *)((scrollTable + k) + (((*((u8 *)(gameState + 0x18A8))) + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
    }
    ext = ((u8 *)owner) + 0x48;
    *((u32 *)(((u8 *)owner) + 0x14)) = 0x80 << 10;
    *((u32 *)(ext + 4)) = zero;
    ((u16 *)ext)[1] = 8;
    *((u16 *)ext) = 0x96 << two;
    *((u32 *)(ext + 8)) = 0x16C1;
    if (((*((u16 *)(params + 8))) & 0xF) == 5)
    {
        *((u32 *)(((u8 *)owner) + 0x14)) = 0x80 << 7;
        *((u32 *)(ext + 8)) = zero;
    }
    mainObj->flags |= 0x1000;
    *((u8 *)((u8 *)mainObj + 0x19 + two * mainObj->index)) = zero;
    audioCmd = (s32 *)0x08671BB0;
    tablePtr = ((u8 *)mainObj) + 0x18;
    sub_080C31E4(tablePtr, ((u8 *)mainObj) + 0x22, *audioCmd);
    *((u8 *)((u8 *)mainObj + 0x19 + 2 * mainObj->index)) = *((u8 *)((u8 *)mainObj + 0x19 + 2 * mainObj->index)) + 1;
    tablePtr += mainObj->index * 2;
    sub_080C31E0((u8 *)mainObj, *((s32 *)((*((u32 *)(((u8 *)mainObj) + 0x14))) + (4 * (*tablePtr)))));
}
