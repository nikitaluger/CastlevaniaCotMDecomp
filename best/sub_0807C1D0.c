extern u8 gTilemapPages[];
s32 checkGlobalStateChange(void *, void *, void *);
s16 divInt32(s32, s16);
void sub_0808DBF8(s32, s32, s32);
s32 getTileTerrainB(s32, s32, s32);
void stepDelayTimer(void *, void *);
void setSpriteScreenPosition(void *, void *);
void sub_080C31E0(void *, s32);
void cullOffscreenEntity(void *, void *);
struct S_FF0
{
  u8 _0[0x10];
  s32 f10;
  u8 _1[0x14ED - 0x14];
  u8 b14ED;
  u8 _2[0x173A - 0x14EE];
  u8 b173A;
  u8 _3[0x18A8 - 0x173B];
  u8 b18A8;
  u8 _4[0x18C2 - 0x18A9];
  u16 w18C2;
};
extern struct S_FF0 gMainWorkspace;
void sub_0807C1D0(void *arg0)
{
  s32 *new_var2;
  void *new_var;
  s32 temp_r3;
  void *temp_r0;
  void *temp_r5;
  void *temp_r5_2;
  void *temp_r6;
  void *temp_r7;
 do { temp_r0 = *((void **) (((u8 *) arg0) + 0x6C)); } while (0);
  temp_r7 = (void *) (((u8 *) temp_r0) + 4);
  new_var2 = (s32 *) (((u8 *) temp_r7) + 4);
  temp_r6 = *((void **) (((u8 *) arg0) + 0x38));
  if (checkGlobalStateChange(arg0, temp_r6, (void *) (((u8 *) temp_r0) + 4)) == 0)
  {
    if (((s32) ((s16) (*((u16 *) (((u8 *) temp_r6) + 4))))) > 0x100)
    {
      new_var = *((void **) (((u8 *) temp_r7) + 0x2C));
      *((u16 *) (((u8 *) temp_r6) + 4)) = (u16) ((*((u16 *) (((u8 *) temp_r6) + 4))) - 0x40);
      *((u16 *) (((u8 *) temp_r6) + 6)) = (u16) ((*((u16 *) (((u8 *) temp_r6) + 6))) - 0x40);
      temp_r5 = new_var;
      *((s16 *) (((u8 *) temp_r5) + 6)) = divInt32(0x400, (s16) (*((u16 *) (((u8 *) temp_r6) + 4))));
      temp_r5_2 = *((void **) (((u8 *) temp_r7) + 0x2C));
      temp_r3 = *((u16 *) (((u8 *) temp_r6) + 6));
      *((s16 *) (((u8 *) temp_r5_2) + 8)) = divInt32(0x400, (s16) temp_r3);
    }
    *((s32 *) (((u8 *) temp_r0) + 4)) = (temp_r3 = (*((s32 *) (((u8 *) temp_r0) + 4))) + (*((s32 *) (((u8 *) temp_r7) + 8))));
    if (1 & (*((u16 *) (((u8 *) (*((void **) (((u8 *) temp_r7) + 0x2C)))) + 0x14))))
    {
      sub_0808DBF8(temp_r3, *((s32 *) (((u8 *) temp_r7) + 4)), 0);
      {
sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
return;
}
    }
    if ((getTileTerrainB(((u32) gTilemapPages) + (((s32) gMainWorkspace.b18A8) << 6), temp_r3, *new_var2) << 16) != 0)
    {
      sub_0808DBF8(*((s32 *) (((u8 *) temp_r0) + 4)), *((s32 *) (((u8 *) temp_r7) + 4)), 0);
      {
sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
return;
}
    }
    *((u16 *) (((u8 *) temp_r6) + 0)) = gMainWorkspace.w18C2;
    stepDelayTimer((void *) (((u8 *) temp_r0) + 0x20), temp_r6);
    setSpriteScreenPosition(temp_r6, temp_r7);
    if ((gMainWorkspace.b173A == 0x1C) || ((gMainWorkspace.b14ED == 0) && (gMainWorkspace.f10 != 0)))
    {

      sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));

      return;
    }
    cullOffscreenEntity(arg0, temp_r6);
  }
}
