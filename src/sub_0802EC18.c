extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
struct Actor {
    u8 _0[8];
    s32 worldX;
    s32 worldY;
    s32 spawnX;
    s32 spawnY;
    u8 _18[4];
    s16 kind;
    u8 _1E[4];
    s16 slot;
};
struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 index;
    u8 _24[0x38-0x24];
    u8 *object;
    struct Actor *effect;
    u8 _40[0x4C-0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState gMainWorkspace;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable gCameraState;
extern u8 gSpriteAnimDataTable[];
extern u32 gMainObjTimerCallbacks;

/* Spawns an entity's sprite and actor state, seeds its kind and position,
 * sets up the initial animation, sprite graphics and camera-relative position,
 * then registers the entity's script. */
void sub_0802EC18(struct Entity *arg0) {
    u8 *sprite;
    struct Actor *state;
    u8 *anim;
    s32 animIndex;
    u32 gfxAttr;
    u8 *scrollBase;
    s32 *scriptData;

    sprite = allocSpriteObject();
    state = NULL;
    anim = NULL;
    animIndex = 0;
    if (((sprite == NULL) || ((arg0->object = sprite, allocWorkSlot((u8 *)arg0, 0, 0x48, 0), state = arg0->effect, state == NULL))) ||
        ((anim = (u8 *)state + 0x34, state->kind = 0x29, state->worldX = arg0->posX << 16, state->worldY = arg0->posY << 16,
          animIndex = findKindIndex(0x29), state->slot = animIndex, ((s32)(animIndex << 16) < 0)))) {
        if (sprite || animIndex) {
            sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
            return;
        } else {
            sub_080C31E0((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
            return;
        }
    }
    initSpriteGraphics(sprite, anim, (s32)gSpriteAnimDataTable + state->kind * 0xC);
    setAnimationFrame(sprite, anim, 0x0C, 0);
    gfxAttr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = gfxAttr;
    *(u16 *)sprite = gfxAttr | gMainWorkspace.flags;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    scrollBase = (u8 *)&gCameraState;
    { u32 offset = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(scrollBase + offset + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = 0;
    scriptData = (s32 *)0x08671BB0;
    sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *scriptData);
}
