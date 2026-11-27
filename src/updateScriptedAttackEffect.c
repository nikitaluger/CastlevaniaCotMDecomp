/* Per-frame update for a scripted attack/effect: checks whether it should be removed,
 * handles proximity/target and flag events (optionally firing an event), advances the
 * script step to dispatch a callback, then repositions the sprite's Y on screen. */
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E730[];
extern u32 gScriptEventCallbacks[];
s32 checkActorViewBounds(void *, void *);
void applySpritePaletteVariant(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 updateObjectDisplayState(void *, void *);
void sub_080C31E0(void *, s32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void sub_08055990(void *, void *);
void sub_08013C8C(void *, void *);

void updateScriptedAttackEffect(u8 *arg0)
{
  u8 *sprite;
  u8 *state;
  u8 *scratch;
  u8 *extra;
  u8 *coordBase;
  u8 *scrollPtr;
  u32 scrollOff;
  u32 scrollY;
  u8 cmd;
  u8 *script;
  s32 stepOff;
  sprite = *((u8 **) (arg0 + 0x38));
  state = *((u8 **) (arg0 + 0x3C));
  scratch = state + 0x34;
  extra = state + 0x48;
  if (checkActorViewBounds(sprite, state) == 1)
  {
    if (*((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x1A)) <= 2) return;
  }
  applySpritePaletteVariant(arg0, sprite);
  if (sub_08013558(sprite, state, *((void **) (state + 0x28))) != 0)
  {
    spawnContactEffectOnHit(arg0, *((void **) (state + 0x28)));
  }
  uploadPendingSpriteGraphic(arg0, *((void **) (state + 0x28)));
  if ((*((u16 *) state)) & 1)
  {
    if (*((u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0) + 0x1A)) != 5)
    {
      u32 *callback;
      updateActorWorldPosition(arg0);
      sub_08005E80(0x80);
      *((u8 *) (((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0)) + 0x1B)) = 0;
      callback = gScriptEventCallbacks;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 5, *callback);
    }
  }
  if (updateObjectDisplayState(sprite, state) == 0)
  {
    u8 *stepPtr;
    *((u32 *) (arg0 + 0x14)) = (u32) D_0866E730;
    *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) + 1;
    stepPtr = (u8 *) ((((u32) (*((s16 *) (arg0 + 0x22)))) * 2) + ((u32) arg0));
    *((u8 *) (stepPtr + 0x19)) = (*((u8 *) (stepPtr + 0x19))) + 1;
    stepOff = (*((s16 *) (arg0 + 0x22))) * 2;
    script = arg0;
    script += 0x18;
    cmd = *((u8 *) (((u32) script) + ((u32) stepOff)));
    sub_080C31E0((s32) arg0, *((u32 *) ((*((u32 *) (arg0 + 0x14))) + (cmd * 4))));
    *((u16 *) (arg0 + 0x22)) = (*((u16 *) (arg0 + 0x22))) - 1;
    if (((*((u16 *) (arg0 + 2))) & 0x8000) == 0)
    {
      stepAnimationTrack(sprite, scratch);
      advanceMotion(state, 0);
    }
    else
    {
      return;
    }
  }
  sub_08055990(sprite, state);
  sub_08013C8C(arg0, sprite);
  {
    s32 worldY = (*((s32 *) (state + 0x0C))) + (*((s32 *) (extra + 0x00)));
    coordBase = gCameraState;
    scrollPtr = gMainWorkspace;
    scrollPtr += 0x18A8;
    scrollOff = (((u32) (*((u8 *) scrollPtr))) + 1) * 0x40;
    coordBase += 0x127C;
    scrollY = *((u32 *) (coordBase + scrollOff));
    *((u32 *) (sprite + 0x18)) = worldY - ((scrollY + 0xFFFF8000) & 0xFFFF0000);
  }
}
