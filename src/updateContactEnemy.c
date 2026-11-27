extern void applySpritePaletteVariant(void *, s32);
extern s32 checkActorViewBounds(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void spawnContactEffectOnHit(void *, void *);
extern void uploadPendingSpriteGraphic(void *, void *);
extern void updateActorWorldPosition(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern void *gScriptEventCallbacks;
extern void *gContactEnemyStepHandlers[];
extern s32 sub_080457E0(void *);
extern void sub_08045970(void *, s32);

/* Per-frame update for the contact enemy: clear both effect flags, run the
 * view and hit checks, dispatch the current script step through its handler
 * table, then refresh the palettes and set effect flags from the sprite kind. */
void updateContactEnemy(u8 *entity)
{
  s32 sprite;
  u8 *state;
  u8 *animState;
  u8 *fxState;
  u8 *stepSlot;
  void **callbackSlot;
  s32 stepOffset;
  u8 fxFlags;
  u8 *scriptBase;
  u8 handlerIndex;
  void **handlers;
  void *handler;
  u8 *fxPtr;
  sprite = *((s32 *) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  animState = state + 0x34;
  fxState = state + 0x48;
  *((u8 *) ((*((u8 **) (fxState + 0x08))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (fxState + 0x0C))) + 1)) = 0;
  if (checkActorViewBounds(sprite, state) == 1)
  {
    ;
    if (((u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)))[0x1A] == 0)
    {
      return;
    }
  }
  applySpritePaletteVariant(entity, sprite);
  if ((sub_080457E0(entity) == 0) && (sub_08013558(sprite, state, *((void **) (state + 0x28))) != 0))
  {
    spawnContactEffectOnHit(entity, *((void **) (state + 0x28)));
  }
  uploadPendingSpriteGraphic(entity, *((void **) (state + 0x28)));
  uploadPendingSpriteGraphic(entity, *((u8 **) (fxState + 0x08)));
  uploadPendingSpriteGraphic(entity, *((u8 **) (fxState + 0x0C)));
  if ((*((u16 *) state)) & 1)
  {
    u8 *slot1 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    if (slot1[0x1A] != 3)
    {
      u8 *slot2;
      updateActorWorldPosition(entity);
      slot2 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
      slot2[0x1B] = 0;
      callbackSlot = &gScriptEventCallbacks;
      _call_via_r3(entity + 0x18, entity + 0x22, 3, *callbackSlot);
    }
  }
  if (updateObjectDisplayState(sprite, state) == 0)
  {
    *((u32 *) (entity + 0x14)) = (u32) gContactEnemyStepHandlers;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    stepSlot = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    stepSlot[0x19] = (u8) (stepSlot[0x19] + 1);
    stepOffset = (*((s16 *) (entity + 0x22))) * 2;
    scriptBase = entity + 0x18;
    handlerIndex = *(scriptBase + stepOffset);
    handlers = *((void **) (entity + 0x14));
    handler = handlers[handlerIndex];
    _call_via_r1(entity, handler);
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if ((*((u16 *) (entity + 0x02))) & 0x8000)
    {
      return;
    }
    stepAnimationTrack(sprite, animState);
    sub_08011EE8(state, 0x16C1, 0);
  }
  sub_08045970(entity, sprite);
  if (!((*((u16 *) state)) & 0x0D))
  {
    if ((*((u16 *) (sprite + 0x28))) == 0x16)
    {
      fxPtr = *((u8 **) (fxState + 0x08));
      fxFlags = (u8) (fxPtr[1] | 1);
      fxPtr[1] = fxFlags;
    }
    if ((*((u16 *) (sprite + 0x28))) == 0x0F)
    {
      fxPtr = *((u8 **) (fxState + 0x0C));
      fxFlags = (u8) (fxPtr[1] | 5);
      fxPtr[1] = fxFlags;
    }
  }
  sub_08013C8C(entity, sprite);
}
