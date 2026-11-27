extern void sub_08013C5C(void *, s32);
extern s32 sub_080141AC(s32, void *);
extern s32 sub_08013558(s32, void *, void *);
extern void sub_08013978(void *, void *);
extern void sub_080142C0(void *, void *);
extern void sub_08013AC4(void *);
extern s32 updateObjectDisplayState(s32, void *);
extern void stepAnimationTrack(s32, void *);
extern void sub_08011EE8(void *, s32, s32);
extern void sub_08013C8C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;
extern void *D_0866E278;
extern s32 sub_080457E0(void *);
extern void sub_08045970(void *, s32);

/* Per-frame update for one entity: runs collision/visibility/AI checks,
 * handles the death/recycle path by calling the routine pointed to by the
 * state's jump table, then refreshes the sprite's graphics flags. */
void sub_08045408(u8 *entity)
{
  s32 sprite;
  u8 *state;
  u8 *anim;
  u8 *fx;
  u8 *desc;
  void **callbackSlot;
  s32 slot;
  u8 flags;
  u8 *base;
  u8 select;
  void **table;
  void *target;
  u8 *fxPtr;
  sprite = *((s32 *) (entity + 0x38));
  state = *((u8 **) (entity + 0x3C));
  anim = state + 0x34;
  fx = state + 0x48;
  *((u8 *) ((*((u8 **) (fx + 0x08))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (fx + 0x0C))) + 1)) = 0;
  if (sub_080141AC(sprite, state) == 1)
  {
    ;
    if (((u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity)))[0x1A] == 0)
    {
      return;
    }
  }
  sub_08013C5C(entity, sprite);
  if ((sub_080457E0(entity) == 0) && (sub_08013558(sprite, state, *((void **) (state + 0x28))) != 0))
  {
    sub_08013978(entity, *((void **) (state + 0x28)));
  }
  sub_080142C0(entity, *((void **) (state + 0x28)));
  sub_080142C0(entity, *((u8 **) (fx + 0x08)));
  sub_080142C0(entity, *((u8 **) (fx + 0x0C)));
  if ((*((u16 *) state)) & 1)
  {
    u8 *desc1 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    if (desc1[0x1A] != 3)
    {
      u8 *desc2;
      sub_08013AC4(entity);
      desc2 = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
      desc2[0x1B] = 0;
      callbackSlot = &sScriptStepCallbacks;
      sub_080C31E8(entity + 0x18, entity + 0x22, 3, *callbackSlot);
    }
  }
  if (updateObjectDisplayState(sprite, state) == 0)
  {
    *((u32 *) (entity + 0x14)) = (u32) 0x0866E278;
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) + 1);
    desc = (u8 *) ((((u32) (*((s16 *) (entity + 0x22)))) * 2) + ((u32) entity));
    desc[0x19] = (u8) (desc[0x19] + 1);
    slot = (*((s16 *) (entity + 0x22))) * 2;
    base = entity + 0x18;
    select = *(base + slot);
    table = *((void **) (entity + 0x14));
    target = table[select];
    sub_080C31E0(entity, target);
    *((u16 *) (entity + 0x22)) = (u16) ((*((u16 *) (entity + 0x22))) - 1);
    if ((*((u16 *) (entity + 0x02))) & 0x8000)
    {
      return;
    }
    stepAnimationTrack(sprite, anim);
    sub_08011EE8(state, 0x16C1, 0);
  }
  sub_08045970(entity, sprite);
  if (!((*((u16 *) state)) & 0x0D))
  {
    if ((*((u16 *) (sprite + 0x28))) == 0x16)
    {
      fxPtr = *((u8 **) (fx + 0x08));
      flags = (u8) (fxPtr[1] | 1);
      fxPtr[1] = flags;
    }
    if ((*((u16 *) (sprite + 0x28))) == 0x0F)
    {
      fxPtr = *((u8 **) (fx + 0x0C));
      flags = (u8) (fxPtr[1] | 5);
      fxPtr[1] = flags;
    }
  }
  sub_08013C8C(entity, sprite);
}
