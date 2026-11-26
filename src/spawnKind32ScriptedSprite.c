extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void setAnimationFrame(u8 *, u8 *, s16, s32);
extern void *allocEffectPart(void);
extern void updateScriptedObjectAndCleanup(void);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, s32);

struct EffectPart { u8 unk0; u8 kind; u8 layer; u8 priority; u16 gfxIndex; u16 anim0; u16 anim1; u16 anim2; u16 anim3; u16 palette; u32 object; u16 tail; };
struct EffectWork { u8 unk0[8]; s32 worldX; s32 worldY; u32 radiusA; u32 radiusB; u32 state; s16 kind; u8 unk1E[4]; s16 slot; u32 updateCb; struct EffectPart *gfx; };
struct GameState { u8 unk0[0x18A8]; u8 scrollIndex; u8 unk18A9[0x19]; u16 renderFlags; };
extern struct GameState gMainWorkspace;
struct ScrollState { u8 unk0[0x1278]; u32 cameraX; u32 cameraY; };
extern struct ScrollState gCameraState;
struct EffectStats { u16 gfxIndex; u8 unk2[2]; u16 palette; u8 unk6[0xE]; };
extern struct EffectStats gSpriteKindTable[];
extern u16 gKind32LayerAttrs[];
extern s16 gKind32AnimTable[];
extern u8 gSpriteAnimDataTable[];

/* Allocate a scripted object's sprite, work block and optional render part for
 * kind 0x32, initialise their graphics and screen position, then run its
 * entry script; on any allocation failure dispatch the saved handler instead. */
void spawnKind32ScriptedSprite(u8 *entity) {
    u8 *sprite;
    struct EffectWork *work;
    struct EffectWork *newWork;
    u8 *animState;
    struct EffectPart *part;
    s32 kindIndex;
    u32 gfxFlags;
    u32 zeroByte;
    u8 *camera;
    s32 *scriptOps;
    s16 *animIndexPtr;
    s16 *frameTable;
    s32 animIndex;

    sprite = allocSpriteObject();
    work = NULL;
    part = NULL;
    kindIndex = 0;
    if ((sprite == NULL) ||
        (*(u8 **)(entity + 0x38) = sprite, allocWorkSlot(entity, 0, 0x48, 0), (newWork = *(struct EffectWork **)(entity + 0x3C)) == NULL) ||
        ((work = newWork),
         animState = (u8 *)work + 0x34, work->updateCb = *(u32 *)(entity + 0x24), *(u32 *)(entity + 0x24) = (u32)updateScriptedObjectAndCleanup,
         work->kind = 0x32,
         work->worldX = *(s16 *)(entity + 0x4C) << 16, work->worldY = *(s16 *)(entity + 0x54) << 16,
         kindIndex = findKindIndex(0x32), work->slot = kindIndex, ((s32)(kindIndex << 16) < 0)) ||
        (initSpriteGraphics(sprite, animState, (s32)gSpriteAnimDataTable + work->kind * 0xC),
         animIndexPtr = (s16 *)(entity + 0x7C),
         frameTable = gKind32AnimTable,
         animIndex = *animIndexPtr,
         setAnimationFrame(sprite, animState, frameTable[animIndex], 1),
         (*(u16 *)(entity + 0x84) & 2) && (part = allocEffectPart(), work->gfx = part, part == NULL))) {
        sub_080C31E0(entity, *(s32 *)(entity + 0x24));
        return;
    }
    if (part != NULL) {
        work->gfx->kind = 0;
        work->gfx->layer = 8;
        work->gfx->priority = 1;
        work->gfx->gfxIndex = gSpriteKindTable[work->kind].gfxIndex;
        work->gfx->anim0 = gKind32LayerAttrs[0];
        work->gfx->anim1 = gKind32LayerAttrs[1];
        work->gfx->anim2 = gKind32LayerAttrs[2];
        work->gfx->anim3 = gKind32LayerAttrs[3];
        work->gfx->palette = gSpriteKindTable[work->kind].palette;
        work->gfx->object = (u32)sprite;
        work->gfx->tail = 0;
    }
    gfxFlags = (*(u16 *)sprite & 0xC00) |
          (((*(s16 *)((u8 *)work + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)work + 0x22) + 8) << 12));
    zeroByte = 0;
    *(u16 *)sprite = gfxFlags;
    *(u16 *)sprite = gfxFlags | gMainWorkspace.renderFlags;
    *(u32 *)(sprite + 0x1C) = 0x8000000B;
    work->radiusA = *(u32 *)(entity + 0x5C);
    work->radiusB = *(u32 *)(entity + 0x6C);
    camera = (u8 *)&gCameraState;
    { u32 xOff = 0x1278; *(u32 *)(sprite + 0x14) = work->worldX - ((*(u32 *)(camera + xOff + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 yOff = 0x127C; *(u32 *)(sprite + 0x18) = work->worldY - ((*(u32 *)(camera + yOff + ((gMainWorkspace.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    *(u16 *)(entity + 2) = *(u16 *)(entity + 2) | 0x1000;
    *(u8 *)(entity + 2 * *(s16 *)(entity + 0x22) + 0x19) = (u8)zeroByte;
    scriptOps = (s32 *)0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *scriptOps);
}
