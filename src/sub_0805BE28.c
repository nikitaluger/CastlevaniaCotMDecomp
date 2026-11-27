s32 sub_08005910(s32, s32);
void stepAnimationTrack(void *, void *);
void advanceMotion(void *, s32);
void sub_080146D0(void *, s32, s32);
void sub_080C31E8(void *, void *, s32, void *);

struct S_02025FF0 {
  u8 _0[0x174C];
  s32 x;
  s32 y;
};
extern struct S_02025FF0 gMainWorkspace;
extern void *gScriptStepCallbacks;

/* Run down a timer; when it expires, aim at the global (player) position and
 * start a script, otherwise move along the stored angle without gravity. */
void sub_0805BE28(void *entity)
{
  u8 *self = (u8 *)entity;
  void *sprite;
  u8 *motion;
  void *anim;
  u8 *extra;
  s32 timer;

  sprite = *(void **)(self + 0x38);
  motion = *(u8 **)(self + 0x3C);
  anim = motion + 0x34;
  extra = motion + 0x48;

  timer = *(s32 *)(extra + 0x04);
  if (timer <= 0)
  {
    if (*(s16 *)(motion + 0x20) == 0)
    {
      *(s32 *)(extra + 0x08) = sub_08005910(gMainWorkspace.y - *(s32 *)(motion + 0x0C),
                                            gMainWorkspace.x - *(s32 *)(motion + 0x08));
      *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
      {
        void **script = &gScriptStepCallbacks;
        sub_080C31E8(self + 0x18, self + 0x22, 1, *script);
      }
    }
  }
  else
  {
    s32 nextTimer = timer + 0xFFFFE000;
    *(s32 *)(extra + 0x04) = nextTimer;
    sub_080146D0(motion, *(s32 *)(extra + 0x08), nextTimer);
    advanceMotion(motion, 0);
  }

  stepAnimationTrack(sprite, anim);
}
