/* Spawns the sprite object owned by a fresh child state: allocates the sprite
 * and a 0x28-byte child state, initialises the animation from the shared gfx
 * template, picks the frame for the entity's variant, copies its coordinates and
 * parameters, converts them to screen space, then advances the parent's state. */
struct Entity {
    u8 _00[2]; u16 flags; u8 _04[0x10]; u32 unk14; u8 _18[4]; u32 unk1C;
    u8 _20[2]; s16 stateIndex; void *updateFn; u8 _28[0x10];
    void *sprite; void *childState;
    u8 _40[0xC]; u32 x; u8 _50[0xC]; u32 y; u8 _60[0xC];
    u16 spawnFlags; u8 _6E[6]; s16 variant; u8 _76[6]; u32 paramA; u8 _80[0xC]; u32 paramB; u8 _90[0xC]; u32 paramC;
};
struct SpriteObj { u16 attr0; u16 attr1; u8 _04[0x10]; u32 x; u32 y; u32 param; };
struct GlobalData { u8 _0[0x18a8]; u8 frameIndex; u8 _a9[0x19]; u16 spriteBits; };
extern struct GlobalData D_02025FF0;
extern u8 D_02021E90[];      /* shared video state (BG scroll buffers) */
extern u32 D_08100234[];     /* shared gfx template descriptor */
extern s16 D_08100240[];     /* animation frame per variant */
extern void *D_08671BB0;
void *sub_0800355C(void);                             /* alloc sprite */
void sub_0800168C(void *, int, int, int);             /* alloc + clear slot */
void sub_0801131C(void *, void *, void *);            /* init sprite gfx */
void sub_08011368(void *, void *, s16, int);          /* set animation frame */
void sub_080C31E0(void *, void *);                    /* indirect call */
void sub_080C31E4(void *, void *, s32);               /* indirect call */

void sub_0808E0EC(struct Entity *entity) {
    void *sprite;
    void *childState;
    void **stateTable;
    u8 *stateData;
    u8 *cmdPtr;
    s16 variant;
    u8 *statePtr;

    sprite = sub_0800355C();
    if (sprite == NULL) goto fail;
    entity->sprite = sprite;
    sub_0800168C(entity, 0, 0x28, 0);
    childState = entity->childState;
    if (childState == NULL) {
fail:
        sub_080C31E0(entity, entity->updateFn);
        return;
    }
    sub_0801131C(sprite, childState, D_08100234);
    variant = entity->variant;
    sub_08011368(sprite, childState, D_08100240[variant], 0);
    if (entity->spawnFlags & 0x10) ((struct SpriteObj *)sprite)->attr1 |= 0x10;
    if (entity->spawnFlags & 0x20) ((struct SpriteObj *)sprite)->attr1 |= 0x20;
    ((struct SpriteObj *)sprite)->param = (entity->spawnFlags & 0x0F) | 0x80000000;
    ((struct SpriteObj *)sprite)->attr0 |= D_02025FF0.spriteBits;
    statePtr = (u8 *)childState + 0x14;
    *(u32 *)((u8 *)childState + 0x14) = entity->x;
    *(u32 *)(statePtr + 4) = entity->y;
    *(u32 *)(statePtr + 8) = entity->paramA;
    *(u32 *)(statePtr + 0xC) = entity->paramB;
    *(u32 *)(statePtr + 0x10) = entity->paramC;
    {
        u8 *coordTable = D_02021E90;
        u8 *globalBase = (u8 *)&D_02025FF0;
        u8 *xBase;
        u8 *yBase;
        u32 coordIdx;

        globalBase += 0x18A8;

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        xBase = coordTable + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)(statePtr) - ((*(u32 *)(xBase + coordIdx) + 0x8000) & 0xFFFF0000);

        coordIdx = ((u32)*globalBase + 1) * 0x40;
        yBase = coordTable + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)(statePtr + 4) - ((*(u32 *)(yBase + coordIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    *(u16 *)((u8 *)entity + 2) |= 0x1000;
    *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x19) = 0;
    stateTable = &D_08671BB0;
    stateData = (u8 *)entity;
    stateData += 0x18;
    sub_080C31E4(stateData, (u8 *)entity + 0x22, (s32)*stateTable);
    *(u8 *)((u32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity + 0x19) += 1;
    cmdPtr = stateData + (u32)(*(s16 *)((u8 *)entity + 0x22)) * 2;
    sub_080C31E0((u8 *)entity, *(void **)(*(u8 **)((u8 *)entity + 0x14) + *(u8 *)cmdPtr * 4));
}
