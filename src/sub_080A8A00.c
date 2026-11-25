s32 sub_08005910(s32, s32);
s32 sub_080AAA68(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(s32, s32);

/* Spawn a spread projectile at a trig-derived offset from the aim point, then bump the shot counter. */
void sub_080A8A00(void *base, void *ctrl)
{
  s32 spawnX;
  s32 *trigTable;
  s32 angle;
  angle = sub_08005910((*((s32 *) (((s8 *) ctrl) + 0x94))) - (*((s32 *) (((s8 *) ctrl) + 0x80))), (*((s32 *) (((s8 *) ctrl) + 0x90))) - (*((s32 *) (((s8 *) ctrl) + 0x7C)))) + (*((s32 *) (((s8 *) ctrl) + 0xA0)));
  trigTable = (s32 *) 0x08671BFC;
  spawnX = ((*((s32 *) (((s8 *) base) + 0x5C))) + (*((s32 *) (((s8 *) ctrl) + 0x90)))) + ((sub_080C31E0(angle + 0x4000, *((s32 *) 0x08671BFC)) >> 8) * 0x2800);
  sub_080AAA68(*((s32 *) (((s8 *) ctrl) + 0x138)), spawnX, ((*((s32 *) (((s8 *) base) + 0x6C))) + (*((s32 *) (((s8 *) ctrl) + 0x94)))) + ((sub_080C31E0(angle, *trigTable) >> 8) * 0x2800), angle, (s32) (*((u8 *) (((s8 *) ctrl) + 0xF0))), (s32) (*((u8 *) (((s8 *) ctrl) + 0xDA))));
  *((u8 *) (((s8 *) ctrl) + 0xF0)) = (u8) ((*((u8 *) (((s8 *) ctrl) + 0xF0))) + 1);
}
