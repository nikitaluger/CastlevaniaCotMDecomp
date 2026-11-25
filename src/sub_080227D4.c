extern s32 sub_080C31E0(s32, void *);
extern u16 D_080CE830[];
extern void *D_08671BFC[];

/* Sets the angle-driven motion parameters of the object's three child entities
 * from a direction selector; an out-of-range selector clears the children. */
void sub_080227D4(u8 *self, u8 *source)
{
  u8 *obj;
  u8 *objState;
  u16 *params;
  u32 baseAngle;
  u32 dir;
  u32 angleB;
  u32 angleC;
  s32 trig;
  void **trigTable;

  obj = *((u8 **) (self + 0x3C));
  objState = obj + 0x48;
  params = D_080CE830;
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

  *((u8 *) ((*((u8 **) (obj + 0x28))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (objState + 0x34))) + 1)) = 0;
  *((u8 *) ((*((u8 **) (objState + 0x38))) + 1)) = 0;

common:
  {
    volatile u32 *child = (volatile u32 *) (obj + 0x28);
    *((u16 *) (((u8 *) (*child)) + 6)) = params[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = params[1];
  }

  trigTable = D_08671BFC;
  trig = sub_080C31E0(baseAngle + 0x4000, *trigTable);
  *((u16 *) ((*((u8 **) (obj + 0x28))) + 0x0A)) = (u16) (((trig * 13) / 65536) + params[2]);
  trig = sub_080C31E0(baseAngle, *trigTable);
  *((u16 *) ((*((u8 **) (obj + 0x28))) + 0x0C)) = (u16) (((trig * 13) / 65536) + params[3]);

  {
    volatile u32 *child = (volatile u32 *) (objState + 0x34);
    *((u16 *) (((u8 *) (*child)) + 6)) = params[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = params[1];
  }

  angleB = (baseAngle + 0xFFFFE000) & 0xFFFF;
  trig = sub_080C31E0(angleB + 0x4000, *trigTable);
  *((u16 *) ((*((u8 **) (objState + 0x34))) + 0x0A)) = (u16) (((trig * 13) / 65536) + params[2]);
  trig = sub_080C31E0(angleB, *trigTable);
  *((u16 *) ((*((u8 **) (objState + 0x34))) + 0x0C)) = (u16) (((trig * 13) / 65536) + params[3]);

  {
    volatile u32 *child = (volatile u32 *) (objState + 0x38);
    *((u16 *) (((u8 *) (*child)) + 6)) = params[0];
    *((u16 *) (((u8 *) (*child)) + 8)) = params[1];
  }

  angleC = (baseAngle + 0x2000) & 0xFFFF;
  trig = sub_080C31E0(angleC + 0x4000, *trigTable);
  *((u16 *) ((*((u8 **) (objState + 0x38))) + 0x0A)) = (u16) (((trig * 13) / 65536) + params[2]);
  trig = sub_080C31E0(angleC, *trigTable);
  *((u16 *) ((*((u8 **) (objState + 0x38))) + 0x0C)) = (u16) (((trig * 13) / 65536) + params[3]);
}
