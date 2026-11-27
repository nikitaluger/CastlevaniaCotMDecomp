extern s32 _call_via_r1(s32, void *);
extern u16 sChildMotionParams[];
extern void *gTrigFuncTable[];

/* Sets the angle-driven motion parameters of an object's three child entities
 * from a direction selector; an out-of-range selector clears the children. Each
 * child's two trig components come from the shared fixed-point sin callback,
 * scaled by 13/65536 and added to the table's offset values. */
void configureChildMotionFromDirection(u8 *self, u8 *source)
{
  u8 *object;
  u8 *objectState;
  u16 *motion;
  u32 baseAngle;
  u32 dir;
  u32 angleB;
  u32 angleC;
  s32 trig;
  void **trigFnPtr;

  object = *((u8 **) (self + 0x3C));
  objectState = object + 0x48;
  motion = sChildMotionParams;
  baseAngle = 0;
  dir = ((u32) (*((u16 *) (source + 0x28)))) - 0x2C;

  switch (dir)
  {
    case 0: baseAngle = 0xA0 << 8; goto common;
    case 2: baseAngle = 0x80 << 8; goto common;
    case 4: baseAngle = 0xC0 << 7; goto common;
    case 6: baseAngle = 0x80 << 7; goto common;
    case 8: baseAngle = 0x80 << 6; goto common;
    case 10: baseAngle = 0; goto common;
    case 12: baseAngle = 0xE0 << 8; goto common;
    case 14: baseAngle = 0xC0 << 8; goto common;
  }

  *((u8 *) ((*((u8 **) (object + 0x28))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (objectState + 0x34))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (objectState + 0x38))) + 1)) = 0;

common:
  {
    volatile u32 *child = (volatile u32 *) (object + 0x28);
    *((u16 *) (((u8 *) (*child)) + 6)) = motion[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = motion[1];
  }

  trigFnPtr = gTrigFuncTable;
  trig = _call_via_r1(baseAngle + 0x4000, *trigFnPtr);
  *((u16 *) ((*((u8 **) (object + 0x28))) + 0x0A)) = (u16) (((trig * 13) / 65536) + motion[2]);
  trig = _call_via_r1(baseAngle, *trigFnPtr);
  *((u16 *) ((*((u8 **) (object + 0x28))) + 0x0C)) = (u16) (((trig * 13) / 65536) + motion[3]);

  {
    volatile u32 *child = (volatile u32 *) (objectState + 0x34);
    *((u16 *) (((u8 *) (*child)) + 6)) = motion[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = motion[1];
  }

  angleB = (baseAngle + 0xFFFFE000) & 0xFFFF;
  trig = _call_via_r1(angleB + 0x4000, *trigFnPtr);
  *((u16 *) ((*((u8 **) (objectState + 0x34))) + 0x0A)) = (u16) (((trig * 13) / 65536) + motion[2]);
  trig = _call_via_r1(angleB, *trigFnPtr);
  *((u16 *) ((*((u8 **) (objectState + 0x34))) + 0x0C)) = (u16) (((trig * 13) / 65536) + motion[3]);

  {
    volatile u32 *child = (volatile u32 *) (objectState + 0x38);
    *((u16 *) (((u8 *) (*child)) + 6)) = motion[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = motion[1];
  }

  angleC = (baseAngle + 0x2000) & 0xFFFF;
  trig = _call_via_r1(angleC + 0x4000, *trigFnPtr);
  *((u16 *) ((*((u8 **) (objectState + 0x38))) + 0x0A)) = (u16) (((trig * 13) / 65536) + motion[2]);
  trig = _call_via_r1(angleC, *trigFnPtr);
  *((u16 *) ((*((u8 **) (objectState + 0x38))) + 0x0C)) = (u16) (((trig * 13) / 65536) + motion[3]);
}
