extern s32 checkActorViewBounds(s32, s32);
extern s32 getAngleFromDelta(s32, s32);
extern s32 sub_080147D4(s32);
extern void setSpriteFlipForDirection(s32, s32);
extern void setObjectAnimationFrame(s32, void *, s32, s32);
extern void sub_0803B7E4(void *, void *);
extern void sub_0803B7E0(void *, void *);
extern u8 gMainWorkspace[];
extern void *gMainObjTimerCallbacks;
void sub_08032604(void *arg0)
{
  u8 *self;
  u8 *sprite;
  u8 *work;
  u8 *animTrack;
  u8 *stepState;
  u8 *ws_1;
  u8 *ws_2;
  u8 *ws_arm;
  u8 *__repair_phase_ws;
  s32 dx;
  s32 __repair_phase_dx;
  s32 dy;
  s32 __repair_phase_dy;
  s32 angle;
  s32 __repair_phase_angle;
  s32 val;
  s32 a;
  s32 b;
  s32 stepIndex;
  s32 stepOffset;
  u8 opcode;
  u32 *table;
  void *handler;
  self = arg0;
  sprite = *((u8 **) (self + 0x38));
  work = *((u8 **) (self + 0x3C));
  animTrack = work + 0x34;
  stepState = work + 0x48;
  if (checkActorViewBounds((s32) sprite, (s32) work) == 1)
  {
    return;
  }
  stepState[5] = 0;
  stepState[4] = 0;
  stepState[0xD] = (stepState[0xD] + 0x10) & 0x10;
  stepState[0xE] = 0;
  self[0x80] = 0;
  stepState[0xC] = (stepState[0xC] + 1) & 1;
  ws_2 = gMainWorkspace;
  ws_1 = gMainWorkspace;
  ws_1 += 0x1750;
  ws_2 = work + 0xC;
  dx = (*((s32 *) ws_1)) - (*((s32 *) ws_2));
  ws_2 += 0x174C;
   dy = (*((s32 *) ws_2)) - (*((s32 *) (work + 8))); 
  angle = getAngleFromDelta(dx, dy);
  if (stepState[0xC] == 0)
  {
    a = sub_080147D4(*((s32 *) (stepState + 0x10)));
    b = sub_080147D4(angle);
    if (a != b)
    {
      stepState[0xC]++;
    }
  }
  switch (stepState[0xC])
  {
    case 0:
      if (!((*((s32 *) stepState)) >= 0))
    {
      val = 0x80 << 6;
      *((s32 *) stepState) = val;
    }
    else
    {
      val = -0x2000;
      *((s32 *) stepState) = val;
    }
      ws_2 = work + 0x10;
      *((s32 *) ws_2) = val;
      break;

    case 1:
      ws_arm = gMainWorkspace;
      __repair_phase_ws = gMainWorkspace;
      ws_arm += 0x1750;
      __repair_phase_dx = (*((s32 *) ws_arm)) - (*((s32 *) (work + 0xC)));
      __repair_phase_ws += 0x174C;
      __repair_phase_dy = (*((s32 *) __repair_phase_ws)) - (*((s32 *) (work + 8)));
      __repair_phase_angle = getAngleFromDelta(__repair_phase_dx, __repair_phase_dy);
      *((s32 *) (stepState + 0x10)) = __repair_phase_angle;
      if (sub_080147D4(__repair_phase_angle) < 0)
      {
        *((s32 *) (work + 0x10)) = -0x3000;
      }
      else
      {
        *((s32 *) (work + 0x10)) = 0xC0 << 6;
      }
      *((s32 *) stepState) = *((s32 *) (stepState + 0x10));
    {
      setSpriteFlipForDirection((s32) sprite, __repair_phase_angle);
    }
      break;

    default:
      break;

  }

  setObjectAnimationFrame((s32) sprite, animTrack, 0, 1);
  *((u8 *) ((arg0 + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
  {
    sub_0803B7E4(self + 0x18, self + 0x22);
  }
  *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) += 1;
  stepIndex = *((s16 *) (self + 0x22));
  stepOffset = stepIndex * 2;
  opcode = *((u8 *) ((self + 0x18) + stepOffset));
  table = *((u32 **) (stepState + 0x14));
  handler = (void *) table[opcode];
  sub_0803B7E0(self, handler);
}
