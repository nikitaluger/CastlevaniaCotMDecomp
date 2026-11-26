/* Script command: spawn a sprite/effect object at the thread's scripted spawn
 * coordinates, configure its animation and attributes from the kind tables,
 * then idle the thread and advance the command state. */
extern void *allocSpriteObject(void);
extern s32 allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, s32);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void setSpriteFlip(u8 *, s32);
extern s32 signOf(s32);
extern void registerScriptObject(u8 *, s32);
extern void sub_0802358C(void);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);

struct SpriteDef {
  u8 _0;
  u8 kind;
  u8 subkind;
  u8 state;
  u16 tile;
  u16 f6;
  u16 f8;
  u16 fA;
  u16 fC;
  u16 mode;
  u32 sprite;
  u16 zero;
};
struct SpawnedObject {
  u8 _0[8];
  s32 x;
  s32 y;
  u32 f10;
  u32 f14;
  u32 frameIndex;
  s16 kind;
  u8 _1E[4];
  s16 kindIndex;
  u32 callback;
  struct SpriteDef *spriteDef;
};
struct SpawnInfo {
  u8 _0[4];
  s16 *coords;
};
struct ScriptThread {
  u8 _0[2];
  u16 flags;
  u8 _4[0x14 - 4];
  u32 f14;
  u8 _18[0x22 - 0x18];
  s16 stateIndex;
  u8 _24[0x38 - 0x24];
  u8 *sprite;
  struct SpawnedObject *state;
  u8 _40[0xAC - 0x40];
  struct SpawnInfo *spawnInfo;
};
struct S_02025FF0 {
  u8 _0[0x18A8];
  u8 mapIndex;
  u8 _18A9[0x19];
  u16 gfxFlag;
};
extern struct S_02025FF0 gMainWorkspace;
struct S_02021E90 {
  u8 _0[0x1278];
  u32 cameraX;
  u32 cameraY;
};
extern struct S_02021E90 gCameraState;
struct KindTable {
  u16 tile;
  s16 frame;
  u16 mode;
  u8 _6[0x14 - 6];
};
extern u8 gSpriteKindTable[];
extern u16 D_080CE844[];
extern u8 gSpriteAnimDataTable[];

void scriptCmdSpawnAtCoords(struct ScriptThread *thread)
{
  struct SpawnInfo *spawnInfo = thread->spawnInfo;
  struct SpawnedObject *work;
  u8 *sprite;
  u8 *anim;
  u8 *spriteDefPtr;
  s32 kindIndex;
  u32 zero;
  u8 *gfxBase;
  u8 *kindTable;
  s32 kind;
  s32 flip;
  sprite = allocSpriteObject();
  work = NULL;
  spriteDefPtr = NULL;
  kindIndex = 0;
  if ((((sprite == NULL) || ((thread->sprite = sprite, allocWorkSlot((u8 *) thread, 0, 0xC4, 0), work = thread->state, work == NULL))) || ((anim = ((u8 *) work) + 0x34, work->callback = *((u32 *) (((u8 *) thread) + 0x24)), *((u32 *) (((u8 *) thread) + 0x24)) = (u32) sub_0802358C, zero = 0, work->kind = SPRITE_KIND_SCRIPTED_SPAWN, kindTable = gSpriteKindTable, kind = SPRITE_KIND_SCRIPTED_SPAWN, work->frameIndex = ((struct KindTable *) kindTable)[kind].frame, work->x = spawnInfo->coords[0] << 16, work->y = spawnInfo->coords[1] << 16, kindIndex = findKindIndex(SPRITE_KIND_SCRIPTED_SPAWN), work->kindIndex = kindIndex, ((s32) (kindIndex << 16)) < 0))) || ((initSpriteGraphics(sprite, anim, ((s32) gSpriteAnimDataTable) + (work->kind * 0xC)), spriteDefPtr = allocEffectPart(), work->spriteDef = (struct SpriteDef *) spriteDefPtr, spriteDefPtr == NULL)))
  {
    sub_080C31E0((u8 *) thread, *((u32 *) (((u8 *) thread) + 0x24)));
    return;
  }
  work->spriteDef->kind = zero;
  work->spriteDef->subkind = 8;
  work->spriteDef->state = 1;
  work->spriteDef->tile = ((struct KindTable *) kindTable)[work->kind].tile;
  work->spriteDef->f6 = D_080CE844[0];
  work->spriteDef->f8 = D_080CE844[1];
  work->spriteDef->fA = D_080CE844[2];
  work->spriteDef->fC = D_080CE844[3];
  work->spriteDef->mode = ((struct KindTable *) kindTable)[work->kind].mode;
  work->spriteDef->sprite = (u32) sprite;
  work->spriteDef->zero = zero;
  {
    s32 attr = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) work) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) work) + 0x22))) + 8) << 12));
    *((u16 *) sprite) = attr;
    *((u16 *) sprite) = attr | gMainWorkspace.gfxFlag;
  }
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  gfxBase = (u8 *) (&gCameraState);
  {
    u32 coord;
    u32 k = 0x1278;
    coord = *((u32 *) ((gfxBase + k) + ((gMainWorkspace.mapIndex + 1) << 6)));
    *((u32 *) (sprite + 0x14)) = work->x - ((coord + 0x8000) & 0xFFFF0000);
  }
  {
    u32 k = 0x127C;
    *((u32 *) (sprite + 0x18)) = work->y - (((*((u32 *) ((gfxBase + k) + ((gMainWorkspace.mapIndex + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  {
    u8 *b48 = ((u8 *) work) + 0x48;
    *((u32 *) b48) = zero;
    *((u16 *) (b48 + 4)) = zero;
    *((u16 *) (b48 + 6)) = zero;
    *((u16 *) (b48 + 8)) = zero;
    *((u16 *) (b48 + 0xA)) = zero;
    *((u16 *) (b48 + 0x10)) = zero;
    *((u32 *) (b48 + 0x1C)) = work->x;
    *((u32 *) (b48 + 0x20)) = work->y;
  }
  {
    u8 *b98 = ((u8 *) work) + 0x98;
    *((u32 *) b98) = zero;
    flip = (signOf(work->x) >> 31) & 0x8000;
    *((u32 *) (b98 + 4)) = flip;
    *((u32 *) (b98 + 8)) = zero;
    *((u32 *) (b98 + 0xC)) = 0x28000;
    *((u32 *) (b98 + 0x10)) = 0x2000;
    *((u32 *) (b98 + 0x14)) = 0x280;
  }
  setSpriteFlip(sprite, flip);
  setAnimationFrame(sprite, anim, 0, 1);
  registerScriptObject((u8 *) thread, 0);
  thread->flags |= THREAD_FLAG_WAIT_SPRITE;
  *((u8 *) ((((u8 *) thread) + (2 * thread->stateIndex)) + 0x19)) = zero;
  {
    u8 *cmdPtr;
    s32 *lit;
    lit = (s32 *) 0x08671BB0;
    cmdPtr = ((u8 *) thread) + 0x18;
    sub_080C31E4(cmdPtr, ((u8 *) thread) + 0x22, *lit);
    *((u8 *) ((((u8 *) thread) + (2 * thread->stateIndex)) + 0x19)) = (*((u8 *) ((((u8 *) thread) + (2 * thread->stateIndex)) + 0x19))) + 1;
    cmdPtr = cmdPtr + (2 * thread->stateIndex);
    sub_080C31E0((u8 *) thread, *((u32 *) ((*((u32 *) (((u8 *) thread) + 0x14))) + (4 * (*((u8 *) cmdPtr))))));
  }
}
