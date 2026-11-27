s32 sub_080C31E0(s32, s32);

/* Position six slots (objects[0..5]) evenly around a circle: each present
 * object's x/y at +0x4C/+0x5C is a trig offset from the centre (centreX,
 * centreY), using the RAM trig helper at gTrigFuncPtr[0]; the angle starts at
 * startAngle and advances 0x2AAA per slot (a quarter turn is 0x4000). */
void sub_080A05D0(s32 centreX, s32 centreY, u16 startAngle, void **objects)
{
  u16 angle;
  u32 slot;
  s32 *trigTable;
  void **obj;
  angle = startAngle;
  slot = 0;
  trigTable = (s32 *)0x08671BFC;
  obj = objects;
  do
  {
    if ((*obj) != NULL)
    {
      *((s32 *) (((s8 *) (*obj)) + 0x4C)) = (s32) (((sub_080C31E0(angle + 0x4000, *trigTable) >> 8) << 0xD) + centreX);
      *((s32 *) (((s8 *) (*obj)) + 0x5C)) = (s32) (((sub_080C31E0(angle, *trigTable) >> 8) << 0xD) + centreY);
    }
    angle += 0x2AAA;
    obj += 1;
    slot += 1;
  }
  while (slot <= 5U);
}
