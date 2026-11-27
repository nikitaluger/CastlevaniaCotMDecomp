struct S_02025FF0_174C { u8 _0[0x174C]; u32 v0; u32 v1; };
extern struct S_02025FF0_174C gMainWorkspace;
extern void sub_08051D3C(void *, void *, u16, s32);
extern void sub_080520CC(void *, void *, s32);
extern s32 signOf(s32);
extern s32 fixedPointDistance(s32, s32);
extern s32 sub_08005910(s32, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_08051E94(void *, void *, s32, s32);
extern void sub_08051F98(void *, void *, s32, s16, s32);

/* Weapon-swing step: rebuilds the swinging arc trail, spawns a scaled effect,
 * advances the swing phase and pose counter, and on the final step aims the
 * arc at the player (or widens the swing when out of range) before advancing
 * the command script. */
/* Weapon-swing step: rebuild the arc trail, spawn a scaled effect, advance the swing phase and pose counter, then on the final step aim the arc at the player (or widen it when out of range) and advance the command script. */ void updateWeaponSwing(void *self)
{
  void *sprite = *((void **) (((u8 *) self) + 0x38));
  u8 *selfBytes;
  void *work = *((void **) (((u8 *) self) + 0x3C));
  u32 animOffset = 0x34;
  void *anim = ((u8 *) work) + animOffset;
  u8 *body = ((u8 *) work) + 0x48;
  u8 *trail = ((u8 *) work) + 0xA0;
  int poseTimer = *((u16 *) body);
  void *arcTrail;
  u8 phase;
  u8 phaseTmp;
  u16 poseCount;
  s32 deltaX;
  s32 deltaY;

  sub_08051D3C(self, trail, poseTimer, 1);
  if ((0x3F & (*((((u8 *) self) + ((*((s16 *) (((u8 *) self) + 0x22))) * 2)) + 0x19))) == 0)
  { sub_080520CC(self, body, 0x18000); }
  phaseTmp = *((volatile u8 *) (body + 7));
  phase = phaseTmp;
  if (phase <= 0x3F)
  { *((s32 *) (body + 0x58)) = (*((s32 *) (body + 0x58))) + (((s8) (*((u8 *) ((u8 *) self + 0x6C)))) * 0x1800); }
  else if (((u8) (phase + 0x80)) <= 0x3F)
  { *((s32 *) (body + 0x58)) = (*((s32 *) (body + 0x58))) - (((s8) (*((u8 *) ((u8 *) self + 0x6C)))) * 0x1800); }
  *((u8 *) (body + 7)) = phase + 1;
  arcTrail = body + 0xA8;
  *((s32 *) arcTrail) = *((s32 *) (body + 0x58));
  poseCount = *((u16 *) body);
  poseCount = (poseCount + 1) & 0xFF;
  *((u16 *) body) = poseCount;
  selfBytes = (u8 *) self;
  if ((poseCount == 0xF0) && (signOf(*((s32 *) (body + 0x58))) == ((s8) (*((u8 *) (selfBytes + 0x6C))))))
  {
    deltaX = gMainWorkspace.v0 - (*((s32 *) (body + 0x58)));
    deltaY = gMainWorkspace.v1 - (*((s32 *) (body + 0x5C)));
    if (fixedPointDistance(deltaX, deltaY) <= 0x3FFFFF)
    {
      *((s32 *) (body + 0x0C)) = sub_08005910(gMainWorkspace.v1 - (*((s32 *) (body + 0x84))), gMainWorkspace.v0 - (*((s32 *) (body + 0x60))));
      sub_08051E94(self, arcTrail, 0xC000 - (((s8) (*((u8 *) (selfBytes + 0x6C)))) * 0x1800), 0);
      sub_08051F98(self, body, 0x3C, 1, 0);
      return;
    }
    setAnimationFrame(sprite, anim, 2, 0);
    sub_08051E94(self, arcTrail, 0xC000 - (((s8) (*((u8 *) (selfBytes + 0x6C)))) * 0x3800), 0x800);
    trail = NULL;
    sub_08051F98(self, body, 0x3C, (float) 3, (s32) trail);
  }
}
