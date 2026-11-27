/* Second spawn-sprite script command: create a sprite object from the thread's
 * script reference, configure its position/animation/sprite fields from the kind
 * tables, make the thread wait and advance the command state. */
extern void *allocSpriteObject(void);
extern void allocWorkSlot(u8 *, s32, s32, s32);
extern s32 findKindIndex(s32);
extern void initSpriteGraphics(u8 *, u8 *, void *);
extern void *allocEffectPart(void);
extern void setAnimationFrame(u8 *, u8 *, s32, s32);
extern void registerScriptObject(u8 *, s32);
extern void setSpriteFlip(u8 *, s32);
extern s32 signOf(s32);
extern void sub_080C31E0(void *, u32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gSpriteAnimDataTable[];
extern u8 gSpriteDefaultAttrsAlt[];
extern u32 gMainObjTimerCallbacks[];
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
  s32 posX;
  s32 posY;
  u32 f10;
  u32 f14;
  u32 frameIndex;
  s16 kind;
  u8 _1E[4];
  s16 kindIndex;
  u32 callback;
  struct SpriteDef *spriteDef;
};
struct ScriptRef {
  s16 value0;
  s16 value1;
  s16 type;
};
struct ScriptRefHolder {
  u8 _0[4];
  struct ScriptRef *ref;
};
struct ScriptThread {
  u8 _0[2];
  u16 flags;
  u8 _4[0x22 - 4];
  s16 menuIndex;
  u32 callback;
  u8 _28[0x38 - 0x28];
  u8 *menuItems;
  struct SpawnedObject *work;
  u8 _40[0xAC - 0x40];
  struct ScriptRefHolder *refHolder;
};
struct MainWorkspace {
  u8 _0[0x18A8];
  u8 mapIndex;
  u8 _18A9[0x19];
  u16 gfxFlag;
};
struct CameraState {
  u8 _0[0x1278];
  u32 cameraX;
  u32 cameraY;
};
struct KindTable {
  u16 tile;
  s16 frame;
  u16 mode;
  u8 _6[0x14 - 6];
};
extern struct MainWorkspace gMainWorkspace;
extern struct CameraState gCameraState;
extern struct KindTable gSpriteKindTable[];

void scriptCmdSpawnSprite2(struct ScriptThread *thread)
{
  struct ScriptRefHolder *refHolder;
  u8 *sprite;
  struct SpawnedObject *spawned;
  struct SpawnedObject *newSpawned;
  u8 *animState;
  s32 kindIndex;
  s32 direction;
  u32 attr;
  u32 zero;
  u8 *camBase;
  u8 *kindTable;
  u8 *cmdState;
  s32 *callbackEntry;
  refHolder = thread->refHolder;
  sprite = allocSpriteObject();
  spawned = NULL;
  if ((sprite == NULL) || ((thread->menuItems = sprite, allocWorkSlot((u8 *) thread, 0, 0x94, 0), (newSpawned = thread->work) == NULL)))
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  spawned = newSpawned;
  animState = ((u8 *) spawned) + 0x34;
  spawned->callback = thread->callback;
  thread->callback = SCRIPT_CMD2_DONE_CALLBACK;
  {
    s16 refType = refHolder->ref->type;
    switch (refType)
    {
      case SCRIPT_CMD2_REF_A:
        spawned->kind = SCRIPT_CMD2_KIND_A;
        break;

      case SCRIPT_CMD2_REF_B:
        spawned->kind = SCRIPT_CMD2_KIND_B;
        break;

    }

  }
  kindTable = (u8 *) gSpriteKindTable;
  spawned->frameIndex = ((struct KindTable *) (kindTable + (((s32) spawned->kind) * 0x14)))[0].frame;
  spawned->posX = refHolder->ref->value0 << 16;
  spawned->posY = refHolder->ref->value1 << 16;
  kindIndex = findKindIndex(spawned->kind);
  zero = 0;
  spawned->kindIndex = kindIndex;
  if ((kindIndex << 16) < 0)
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  initSpriteGraphics(sprite, animState, gSpriteAnimDataTable + (spawned->kind * 0xC));
  spawned->spriteDef = (struct SpriteDef *) allocEffectPart();
  if (spawned->spriteDef == NULL)
  {
    sub_080C31E0((u8 *) thread, thread->callback);
    return;
  }
  spawned->spriteDef->kind = 0;
  spawned->spriteDef->subkind = 8;
  spawned->spriteDef->state = 1;
  spawned->spriteDef->tile = ((struct KindTable *) kindTable)[spawned->kind].tile;
  spawned->spriteDef->f6 = *((u16 *) (gSpriteDefaultAttrsAlt + 0));
  spawned->spriteDef->f8 = *((u16 *) (gSpriteDefaultAttrsAlt + 2));
  spawned->spriteDef->fA = *((u16 *) (gSpriteDefaultAttrsAlt + 4));
  spawned->spriteDef->fC = *((u16 *) (gSpriteDefaultAttrsAlt + 6));
  spawned->spriteDef->mode = ((struct KindTable *) kindTable)[spawned->kind].mode;
  spawned->spriteDef->sprite = (u32) sprite;
  spawned->spriteDef->zero = zero;
  attr = ((*((u16 *) sprite)) & 0xC00) | ((((*((s16 *) (((u8 *) spawned) + 0x22))) << 6) + 0x200) | (((*((u16 *) (((u8 *) spawned) + 0x22))) + 8) << 12));
  *((u16 *) sprite) = attr;
  *((u16 *) sprite) = attr | gMainWorkspace.gfxFlag;
  *((u32 *) (sprite + 0x1C)) = 0x8000000A;
  camBase = (u8 *) (&gCameraState);
  {
    u32 camXOffset = 0x1278;
    *((u32 *) (sprite + 0x14)) = spawned->posX - (((*((u32 *) ((camBase + camXOffset) + ((gMainWorkspace.mapIndex + 1) << 6)))) + 0x8000) & 0xFFFF0000);
  }
  {
    u32 camYOffset = 0x127C;
    *((u32 *) (sprite + 0x18)) = spawned->posY - (((*((u32 *) ((camBase + camYOffset) + ((gMainWorkspace.mapIndex + 1) << 6)))) + 0xFFFF8000) & 0xFFFF0000);
  }
  {
    u8 *anim14 = animState + 0x14;
    *((u32 *) (animState + 0x14)) = zero;
    *((u16 *) (anim14 + 4)) = zero;
    *((u16 *) (anim14 + 6)) = zero;
    *((u16 *) (anim14 + 8)) = zero;
    *((u16 *) (anim14 + 10)) = zero;
  }
  {
    u8 *anim34 = animState + 0x34;
    *((u32 *) (animState + 0x34)) = zero;
    direction = (signOf(spawned->posX) >> 31) & 0x8000;
    *((u32 *) (anim34 + 4)) = direction;
    *((u32 *) (anim34 + 8)) = zero;
    *((u32 *) (anim34 + 0xC)) = 0x28000;
    *((u32 *) (anim34 + 0x10)) = 0x2000;
    *((u32 *) (anim34 + 0x14)) = 0x100;
  }
  setSpriteFlip(sprite, direction);
  setAnimationFrame(sprite, animState, 0, 1);
  registerScriptObject((u8 *) thread, 0);
  thread->flags |= THREAD_FLAG_WAIT_SPRITE;
  *((u8 *) ((((u8 *) thread) + (2 * thread->menuIndex)) + 0x19)) = 0;
  {
    callbackEntry = (s32 *) gMainObjTimerCallbacks;
    cmdState = ((u8 *) thread) + 0x18;
    sub_080C31E4(cmdState, ((u8 *) thread) + 0x22, *callbackEntry);
  }
  {
    u32 stateAddr = 2 * ((u32) thread->menuIndex);
    u8 *stateByte;
    stateAddr += (u32) thread;
    stateByte = (u8 *) stateAddr;
    *((u8 *) (stateByte + 0x19)) = (*((u8 *) (stateByte + 0x19))) + 1;
  }
  {
    u8 *cmdByte = cmdState + (2 * thread->menuIndex);
    sub_080C31E0((u8 *) thread, *((u32 *) ((*((u8 **) (((u8 *) thread) + 0x14))) + ((*((u8 *) cmdByte)) * 4))));
  }
}
