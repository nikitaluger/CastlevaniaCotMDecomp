extern void sub_0806A800(void *, s32);
struct S_08086D58
{
  u8 _0[0x14EE];
  u8 v;
};
extern struct S_08086D58 gMainWorkspace;

/* Gate on a global progress byte, then apply a preset from the preset table to
 * the object, choosing its variant from the object's state word. */
void sub_08086D58(u8 *object, s32 selector)
{
  int new_var;
  s32 progress;
  s32 lowBound = 0x11;
  s32 highBound = 0x41;
  progress = gMainWorkspace.v;
  if (progress > 0x4A)
  {
    goto big;
  }
  if (progress >= highBound)
  {
    return;
  }
  if (progress > 0x1A)
  {
    goto sw;
  }
  if (progress < lowBound)
  {
    goto sw;
  }
  return;
  big:
  if (progress == 0x56)
  {
    return;
  }

  if (progress == 0x5A)
  {
    return;
  }
  sw:
  switch (selector)
  {
    case 9:
      if ((*((u16 *) (object + 0x2C))) == 5)
      {
        sub_0806A800(object, 0x83);
      }
      if ((*((u16 *) (object + 0x2C))) == 6)
      {
        sub_0806A800(object, 0x80);
      }
      if ((*((u16 *) (object + 0x2C))) == 0xA)
      {
        sub_0806A800(object, 0);
        return;
      }
      break;

    case 10:

    case 12:
      if ((*((u16 *) (object + 0x2C))) == 6)
      {
        sub_0806A800(object, 0x84);
      }
      if ((*((u16 *) (object + 0x2C))) == 7)
      {
        sub_0806A800(object, 0x81);
      }
      if ((*((u16 *) (object + 0x2C))) == 0xB)
      {
        sub_0806A800(object, 5);
        return;
      }
      break;

    case 11:
      if ((*((u16 *) (object + 0x2C))) == 5)
      {
        sub_0806A800(object, 0x85);
      }
      new_var = 6;
      if ((*((u16 *) (object + 0x2C))) == new_var)
      {
        sub_0806A800(object, 0x82);
      }
      if ((*((u16 *) (object + 0x2C))) == 0xA)
      {
        sub_0806A800(object, 0xA);
      }
      break;

  }
}
