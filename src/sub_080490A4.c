/*
 * Actor script step: integrate the work's motion (with a knockback impulse
 * when flag 0x8C is set), refresh its facing animation, toggle a sprite
 * attribute bit from the script byte's parity, and switch to the stored state
 * when that byte reaches its end value.
 */
extern void sub_0801165C(void *, s32);
extern void sub_080492B8(void *, void *, void *);
extern void sub_080C31E0(void *, void *);

#define KNOCKBACK_IMPULSE  0xB60
#define ATTR_SET_MASK      0x40
#define ATTR_CLEAR_MASK    0xBF
#define END_STATE_BYTE     0x3C

void sub_080490A4(void *arg0)
{
  void *sprite;
  void *work;
  void *animState;
  sprite = *((void **) (((u8 *) arg0) + 0x38));
  work = *((void **) (((u8 *) arg0) + 0x3C));
  animState = ((u8 *) work) + 0x34;
  if ((*((u8 *) (((u8 *) arg0) + 0x8C))) != 0)
  {
    sub_0801165C(work, KNOCKBACK_IMPULSE);
  }
  else
  {
    sub_0801165C(work, 0);
  }
  sub_080492B8(sprite, work, animState);
  {
    u8 *flag8C = ((u8 *) arg0) + 0x8C;
    if ((*(((u8 *) arg0) + 0x8C)) != 0)
    {
      s16 scriptIndex = *((s16 *) (((u8 *) arg0) + 0x22));
      if (!(((u8 *) arg0)[(scriptIndex * 2) + 0x19] & 1))
      {
        u8 *attr = (u8 *)sprite + 0x2A;
        s32 attrValue = ATTR_SET_MASK | *attr;
        *attr = (u8)attrValue;
      }
      else
      {
        u8 *attr = (u8 *)sprite + 0x2A;
        s32 attrValue = ATTR_CLEAR_MASK & *attr;
        *attr = (u8)attrValue;
      }
      if ((*(((u8 *) arg0) + 0x8C)) != 0)
      {
        s16 scriptIndex2 = *((s16 *) (((u8 *) arg0) + 0x22));
        if (((u8 *) arg0)[(scriptIndex2 * 2) + 0x19] == END_STATE_BYTE)
        {
          sub_080C31E0(arg0, *((void **) (((u8 *) arg0) + 0x24)));
        }
      }
    }
  }
}
