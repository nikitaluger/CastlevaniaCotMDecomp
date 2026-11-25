struct S_02025FF0
{
  u8 _0[0x174C];
  u32 field_0x174C;
  u32 field_0x1750;
};
extern struct S_02025FF0 D_02025FF0;
s32 sub_080057F8(void);
s32 sub_08005910(s32 a, s32 b);
s32 sub_080C31E0(void *arg0, s32 a);
s32 sub_080C31E4(void *a, void *b, s32 c);
struct S_3C
{
  u8 _0[8];
  u32 x;
  u32 y;
};
struct S_48
{
  u8 _0[0x10];
  u32 unk10;
  u32 facing;
};
/* Sets the entity's facing angle from its coordinates relative to a global
 * point, clears its pose, runs a script, then advances the pose to pick another. */
void sub_0805728C(u8 *entity)
{
  u8 *self = entity;
  struct S_3C *data = *((struct S_3C **) (self + 0x3C));
  struct S_48 *state = (struct S_48 *) (((u8 *) data) + 0x48);
  s32 angle;
  struct S_48 *stateOut;
  if (sub_080057F8() & 1)
  {
    angle = sub_08005910(D_02025FF0.field_0x1750 - data->y, D_02025FF0.field_0x174C - data->x);
    state->facing = (angle + 0x3000) & 0xFFFF;
  }
  else
  {
    stateOut = state;
    angle = sub_08005910(D_02025FF0.field_0x1750 - data->y, D_02025FF0.field_0x174C - data->x);
    stateOut->facing = (angle + 0xFFFFD000) & 0xFFFF;
  }
  state->unk10 = 0;
  *((u8 *) ((self + (((s16) (*((u16 *) (self + 0x22)))) * 2)) + 0x19)) = 0;
  {
    s32 *scriptTable = (s32 *) 0x08671BB0;
    u8 *poseBase = self + 0x18;
    sub_080C31E4(poseBase, self + 0x22, *scriptTable);
  }
  {
    u8 *p;
    (*((self + (((s16) (*((u16 *) (self + 0x22)))) * 2)) + 0x19))++;
  }
  {
    u8 *poseBase = self + 0x18;
    int poseOffset;
    u8 *posePtr;
    u8 poseIndex;
    u32 scriptTable;
    poseOffset = (s16) (*((u16 *) (self + 0x22)));
    poseOffset *= 2;
    posePtr = poseBase + poseOffset;
    poseIndex = *posePtr;
    scriptTable = *((u32 *) (self + 0x14));
    sub_080C31E0(self, *((u32 *) (((u8 *) scriptTable) + (poseIndex * 4))));
  }
}
