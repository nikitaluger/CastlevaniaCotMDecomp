s32 sub_080141AC(void *, void *);
void sub_08013C5C(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_080142C0(void *, void *);
void sub_080235C0(void *);
void sub_08013AC4(void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, u32);
s32 sub_08013B5C(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_08013C8C(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866D88C[];
extern u32 D_08671BDC[];

/* Updates a projectile/weapon entity: runs the hit and damage responses for its
 * owner and sub-object, dispatches a slot callback, then copies the owner's
 * camera-corrected world position back through the coordinate table. */
void sub_08022C50(u8 *self)
{
  u8 *parent;
  u8 *obj;
  u8 *objSub;
  u8 *objState;
  u8 *pt;
  u8 *pb;
  u32 idx;
  u32 camOff;
  u32 mode;
  u8 slotByte;
  u8 *slots;
  s32 slotOff;
  s32 zero;
  parent = *((u8 **) (self + 0x38));
  obj = *((u8 **) (self + 0x3C));
  objSub = obj + 0x34;
  objState = obj + 0x48;
  if (sub_080141AC(parent, obj) == 1)
  {
    *((u16 *) (objState + 0x0A)) = 0;
  }
  else
  {
    *((u16 *) (objState + 0x0A)) = 1;
  }
  zero = 0;
  *((u32 *) (objState + 0x00)) = zero;
  mode = *((s16 *) (objState + 0x0A));
  if (mode == ((unsigned short) 1))
  {
    sub_08013C5C(self, parent);
    if (sub_08013558(parent, obj, *((void **) (obj + 0x28))) != 0)
    {
      sub_08013978(self, *((void **) (obj + 0x28)));
    }
    sub_080142C0(self, *((void **) (obj + 0x28)));
    mode = mode & (*((u16 *) obj));
    if (mode && ((*((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1A))) != 5))
    {
      u32 *tableArg;
      sub_080235C0(self);
      sub_08013AC4(self);
      sub_08005E80(0x8A);
      *((u8 *) (((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self)) + 0x1B)) = zero;
      tableArg = D_08671BDC;
      sub_080C31E8(self + 0x18, self + 0x22, 5, *tableArg);
    }
    if ((*((u16 *) obj)) & 0x0C)
    {
      sub_080235C0(self);
    }
  }
  if (sub_08013B5C(parent, obj) == 0)
  {
    u8 *slot;
    *((u32 *) (self + 0x14)) = (u32) D_0866D88C;
    *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) + 1;
    slot = (u8 *) ((((u32) (*((s16 *) (self + 0x22)))) * 2) + ((u32) self));
    *((u8 *) (slot + 0x19)) = (*((u8 *) (slot + 0x19))) + 1;
    slotOff = (*((s16 *) (self + 0x22))) * 2;
    slots = self;
    slots += 0x18;
    slotByte = *((u8 *) (((u32) slots) + ((u32) slotOff)));
    sub_080C31E0((s32) self, *((u32 *) ((*((u32 *) (self + 0x14))) + (slotByte * 4))));
    *((u16 *) (self + 0x22)) = (*((u16 *) (self + 0x22))) - 1;
    if (((*((u16 *) (self + 2))) & 0x8000) == 0)
    {
      sub_080113A8(parent, objSub);
      sub_0801165C(obj, 0);
    }
    else
    {
      return;
    }
  }
  sub_08013C8C(self, parent);
  {
    s32 baseCoord = (*((s32 *) (obj + 0x0C))) + (*((s32 *) (objState + 0x00)));
    pt = gCameraState;
    pb = gMainWorkspace;
    pb += 0x18A8;
    idx = (((u32) (*pb)) + 1) * 0x40;
    pt += 0x127C;
    camOff = *((u32 *) (pt + idx));
    *((u32 *) (parent + 0x18)) = baseCoord - ((camOff + 0xFFFF8000) & 0xFFFF0000);
  }
}
