extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void *allocEffectPart(void);
extern void registerScriptObject(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);
extern s32 _call_via_r1(u8 *, s32);
extern void sub_0803EA3C(void);
extern u32 gScriptStepCallbackTable;

struct SpriteDef { u8 _0; u8 type; u8 layer; u8 priority; u16 gfxIndex; u16 anim0, anim1, anim2, anim3; u16 palette; u32 object; u16 tail; };
struct SpriteState { u8 _0[8]; s32 worldX; s32 worldY; u8 _10[8]; u32 frame; s16 kind; u8 _1E[4]; s16 animSlot; u32 savedHandler; struct SpriteDef *spriteDef; u8 _2C[0x1C]; u16 duration; u16 interval; u32 spawnState; };
struct ScriptThread { u8 _0[2]; u16 flags; u8 _4[0x10]; u32 dispatchTable; u8 _18[0xA]; s16 scriptStep; u32 callback; u8 _28[0x10]; u8 *sprite; struct SpriteState *state; u8 _40[0xC]; s16 posX; u8 _4E[6]; s16 posY; u8 _56[6]; s16 flip; };
struct GameState { u8 _0[0x18A8]; u8 mapIndex; u8 _18A9[0x19]; u16 gfxFlag; };
extern struct GameState gMainWorkspace;
struct ScrollState { u8 _0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollState gCameraState;
struct KindTable { u16 tile; u16 anim; u16 palette; u8 _6[0xE]; };
extern u8 gSpriteKindTable[];
extern u16 gKind57LayerAttrs[];
extern u8 gSpriteAnimDataTable[];

/* Builds a script-spawned kind-0x57 sprite: allocates its sprite and work state,
 * fills a render part from the kind tables, places it against the camera scroll,
 * sets its duration and interval, registers it as a script object, then advances
 * the script. */
void spawnKind57ScriptSprite(struct ScriptThread *arg0) {
    u8 *sprite;
    struct SpriteState *state;
    u8 *animState;
    struct SpriteDef *spriteDef;
    s32 animSlot;
    u32 tmp;
    u32 spriteAttr;
    u8 *work;
    u8 *camera;
    u8 *scriptEntry;
    u8 *scriptEntry2;
    u32 *timerTable;
    s32 *dispatchTable;
    u32 command;
    u16 *timers;

    sprite = allocSpriteObject();
    state = NULL;
    spriteDef = NULL;
    animSlot = 0;
    if ((sprite == NULL) ||
        (arg0->sprite = sprite, allocWorkSlot((u8 *)arg0, 0, 0x50, 0), state = arg0->state, state == NULL) ||
        (animState = (u8 *)state + 0x34, state->savedHandler = *(u32 *)((u8 *)arg0 + 0x24), *(u32 *)((u8 *)arg0 + 0x24) = (u32)sub_0803EA3C,
         state->kind = SPRITE_KIND_SCRIPT_TIMER, work = (u8 *)&gSpriteKindTable, state->frame = *(s16 *)((u8 *)work + state->kind * 0x14 + 2),
         state->worldX = ((s16 *)((u8 *)arg0 + 0x4C))[0] << 16, state->worldY = ((s16 *)((u8 *)arg0 + 0x54))[0] << 16,
         animSlot = findKindIndex(SPRITE_KIND_SCRIPT_TIMER), state->animSlot = (s16)animSlot, ((s32)(animSlot << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + state->kind * 0xC), spriteDef = (struct SpriteDef *)allocEffectPart(), state->spriteDef = spriteDef, spriteDef == NULL)) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    state->spriteDef->type = 0;
    state->spriteDef->layer = 8;
    state->spriteDef->priority = 1;
    state->spriteDef->gfxIndex = ((struct KindTable *)work)[state->kind].tile;
    state->spriteDef->anim0 = gKind57LayerAttrs[0];
    state->spriteDef->anim1 = gKind57LayerAttrs[1];
    state->spriteDef->anim2 = gKind57LayerAttrs[2];
    state->spriteDef->anim3 = gKind57LayerAttrs[3];
    state->spriteDef->palette = ((struct KindTable *)work)[state->kind].palette;
    state->spriteDef->object = (u32)sprite;
    state->spriteDef->tail = 0;
    spriteAttr = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)state + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)state + 0x22) + 8) << 12));
    *(u16 *)sprite = spriteAttr;
    *(u16 *)sprite = spriteAttr | gMainWorkspace.gfxFlag;
    *(u32 *)(sprite + 0x1C) = 0x8000000A;
    camera = (u8 *)&gCameraState;
    { u32 k = 0x1278; *(u32 *)(sprite + 0x14) = state->worldX - ((*(u32 *)(camera + k + ((gMainWorkspace.mapIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 k = 0x127C; *(u32 *)(sprite + 0x18) = state->worldY - ((*(u32 *)(camera + k + ((gMainWorkspace.mapIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    timers = (u16 *)((u8 *)state + 0x48);
    timers[0] = 0x64;
    timers[1] = 0x0A;
    *(u32 *)(timers + 2) = 0;
    setAnimationFrame(sprite, animState, 0, 1);
    if (((s16 *)((u8 *)arg0 + 0x5C))[0] > 0)
        *(u16 *)(sprite + 2) = (u16)(*(u16 *)(sprite + 2) | 0x10);
    registerScriptObject((u8 *)arg0, 0);
    arg0->flags |= 0x1000;
    scriptEntry = (u8 *)(arg0->scriptStep * 2 + (u32)arg0);
    scriptEntry[0x19] = 0;
    timerTable = &gScriptStepCallbackTable;
    work = (u8 *)arg0 + 0x18;
    sub_080C31E4(work, (u8 *)arg0 + 0x22, *timerTable);
    scriptEntry2 = (u8 *)(arg0->scriptStep * 2 + (u32)arg0);
    scriptEntry2[0x19] = (u8)(scriptEntry2[0x19] + 1);
    work += arg0->scriptStep * 2;
    command = work[0];
    dispatchTable = *(s32 **)((u8 *)arg0 + 0x14);
    _call_via_r1((u8 *)arg0, dispatchTable[command]);
}
