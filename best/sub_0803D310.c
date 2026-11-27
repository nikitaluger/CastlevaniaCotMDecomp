extern struct CC_KindTable gSpriteKindTable[];
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern void updateRefSprite(void *);
extern void sub_080149A4(void *, void *, u16 *, u16, s32);
extern s32 getSpriteFacingSign(u8 *);
extern s32 _call_via_r1(u8 *, s32);
extern s32 _call_via_r2(u8 *, u8 *, s32);
extern u8 gSpriteAnimDataTable[];

struct RefSpawnLayer {
    u8 unused;
    u8 kind;
    u8 subkind;
    u8 state;
    u16 gfxA;
    u16 affine0;
    u16 affine1;
    u16 affine2;
    u16 affine3;
    u16 palette;
    u32 sprite;
    u16 timer;
};
struct RefSpawnWork {
    u8 _0[8];
    s32 x;
    s32 y;
    u32 velX;
    u32 f14;
    u32 frameIndex;
    s16 kind;
    u8 _1E[4];
    s16 slot;
    u32 updateFn;
    struct RefSpawnLayer *spriteLayer;
    u8 _2C[8];
    u8 anim[0x24];
};
struct RefSpawnThread {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22 - 4];
    s16 stateIndex;
    u8 _24[0x38 - 0x24];
    u8 *sprite;
    struct RefSpawnWork *state;
    u8 _40[0x4C - 0x40];
    s16 f4C;
    u8 _4E[6];
    s16 f54;
    u8 _56[0xAC - 0x56];
    struct RefSpawnPositionHolder *refHolder;
};
struct RefSpawnMainWorkspace {
    u8 _0[0x18A8];
    u8 frameCounter;
    u8 _18A9[0x19];
    u16 gfxFlag;
};
struct RefSpawnScrollState { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct RefSpawnMainWorkspace gMainWorkspace;
extern struct RefSpawnScrollState gCameraState;

void sub_0803D310(struct RefSpawnThread *thread)
{
    u8 *sprite;
    struct RefSpawnWork *work;
    struct RefSpawnWork *newWork;
    u8 *anim;
    s32 slot;
    u32 attrs;
    u32 zero;
    u8 *camera;
    u8 *kindTable;
    s32 *callbackSlot;
    struct RefSpawnPositionHolder *refHolder;
    s16 refType;
    s32 facingSign;

    refHolder = thread->refHolder;
    sprite = allocSpriteObject();
    work = NULL;
    slot = 0;
    if ((sprite == NULL) ||
        (thread->sprite = sprite, allocWorkSlot((u8 *)thread, 0, 0x50, 0), newWork = thread->state, newWork == NULL) ||
        (work = newWork, anim = (u8 *)work + 0x34, work->updateFn = *(u32 *)((u8 *)thread + 0x24), *(u32 *)((u8 *)thread + 0x24) = (u32)updateRefSprite,
         refType = refHolder->ref->type,
         ({ u16 spriteKind; switch (refType) { case 0xFF: spriteKind = 0x0E; break; case 0x100: spriteKind = 0x3B; break; default: goto _skip_kind; } work->kind = spriteKind; _skip_kind: 0; }),
         kindTable = (u8 *)gSpriteKindTable,
         work->frameIndex = ((struct RefSpawnKindEntry *)kindTable)[work->kind].frame,
         work->x = refHolder->ref->value0 << 16, work->y = refHolder->ref->value1 << 16,
         slot = findKindIndex(work->kind), zero = 0, work->slot = slot, ((s32)(slot << 16) < 0)) ||
        (initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + work->kind * 0xC), work->spriteLayer = (struct RefSpawnLayer *)allocEffectPart(), work->spriteLayer == NULL)) {
        _call_via_r1((u8 *)thread, *(s32 *)((u8 *)thread + 0x24));
        return;
    }
    work->spriteLayer->kind = 0;
    work->spriteLayer->subkind = 8;
    work->spriteLayer->state = 1;
    work->spriteLayer->gfxA = ((struct RefSpawnKindEntry *)kindTable)[work->kind].tile;
    work->spriteLayer->affine0 = gSpriteAffineParams[0];
    work->spriteLayer->affine1 = gSpriteAffineParams[1];
    work->spriteLayer->affine2 = gSpriteAffineParams[2];
    work->spriteLayer->affine3 = gSpriteAffineParams[3];
    work->spriteLayer->palette = ((struct RefSpawnKindEntry *)kindTable)[work->kind].mode;
    work->spriteLayer->sprite = (u32)sprite;
    work->spriteLayer->timer = zero;
    attrs = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    *(u16 *)sprite = attrs;
    *(u16 *)sprite = attrs | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 scrollOffset = 0x1278; *(u32 *)(sprite + 0x14) = work->x - ((*(u32 *)(camera + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 scrollOffset = 0x127C; *(u32 *)(sprite + 0x18) = work->y - ((*(u32 *)(camera + scrollOffset + ((gMainWorkspace.frameCounter + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    {
        u8 *animPos = anim + 0x14;
        *(u16 *)(animPos + 8) = zero;
        *(u16 *)(animPos + 0xA) = 0x28;
        *(u32 *)(anim + 0x14) = work->x;
        *(u32 *)(animPos + 4) = work->y;
    }
    sub_080149A4(sprite, work, (u16 *)(anim + 0x1C), 0x28, 0x3C);
    facingSign = getSpriteFacingSign(sprite);
    work->velX = facingSign > 0 ? 0xD000 : (u32)0xFFFF3000;
    setAnimationFrame(sprite, anim, 0, 1);
    registerScriptObject((u8 *)thread, 0);
    thread->flags |= 0x1000;
    *(u8 *)((u8 *)thread + 2 * thread->stateIndex + 0x19) = 0;
    callbackSlot = (s32 *)MAIN_OBJ_TIMER_CALLBACK_TABLE;
    _call_via_r2((u8 *)thread + 0x18, (u8 *)thread + 0x22, *callbackSlot);
    {
        u32 timerAddr = 2 * (u32)thread->stateIndex;
        u8 *timerByte;
        timerAddr += (u32)thread;
        timerByte = (u8 *)timerAddr;
        *(u8 *)(timerByte + 0x19) = *(u8 *)(timerByte + 0x19) + 1;
    }
    {
        u8 *stepByte = (u8 *)thread + 0x18;
        stepByte += thread->stateIndex * 2;
        _call_via_r1((u8 *)thread, *(s32 *)(*(u8 **)((u8 *)thread + 0x14) + *stepByte * 4));
    }
}
