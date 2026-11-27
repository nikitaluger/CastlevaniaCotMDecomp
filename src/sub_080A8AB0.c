s32 getAngleFromDelta(s32, s32);
s32 sub_080AA9F0(s32, s32, s32, u8);
s32 sub_080C31E0(s32, s32);

/* Spawn a projectile aimed at a target.
 * owner (arg0) is the firing entity; source (arg1) is its fire sub-struct:
 *   0x7C/0x80 = origin x/y, 0x90/0x94 = target x/y,
 *   0xA0 = base angle, 0xDA = projectile subtype.
 * owner's spawn offsets live at 0x5C/0x6C.  The angle from origin to target
 * (plus the base angle) is measured by getAngleFromDelta; the word at 0x08671BFC
 * is a function pointer that the bx-r1 thunk sub_080C31E0 uses to turn an
 * angle into an x/y offset (a quarter turn, 0x4000, gives the perpendicular).
 * The new object is created by sub_080AA9F0 (id 0x19C). */
s32 sub_080A8AB0(void *owner, void *source)
{
  s32 spawnX;
  int angleFuncSlot;
  s32 angle;
  angle = getAngleFromDelta((*((s32 *) (((s8 *) source) + 0x94))) - (*((s32 *) (((s8 *) source) + 0x80))), (*((s32 *) (((s8 *) source) + 0x90))) - (*((s32 *) (((s8 *) source) + 0x7C)))) + (*((s32 *) (((s8 *) source) + 0xA0)));
  angleFuncSlot = 0x08671BFC;
  spawnX = ((*((s32 *) (((s8 *) owner) + 0x5C))) + (*((s32 *) (((s8 *) source) + 0x90)))) + ((sub_080C31E0(angle + 0x4000, *((s32 *) angleFuncSlot)) >> 8) * 0x2800);
  return sub_080AA9F0(spawnX, ((*((s32 *) (((s8 *) owner) + 0x6C))) + (*((s32 *) (((s8 *) source) + 0x94)))) + ((sub_080C31E0(angle, *((s32 *) 0x08671BFC)) >> 8) * 0x2800), angle, *((u8 *) (((s8 *) source) + 0xDA)));
}
