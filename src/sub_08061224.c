extern void allocWorkSlot(void *, s32, s32, s32);
extern void *allocSpriteObject(void);
extern s32 sub_08061C9C(u8, u8);
extern void postDisplaySprite(s32, void *, s32, s32, s32);
extern void sub_080C2E68(s32, s32, s32);
extern void sub_08061E04(void);
extern void sub_08061E34(void);
extern s32 _call_via_r1(s32, s32);
extern void _call_via_r2(void *, void *, s32);
struct S_02021E90
{
  u8 _0[0x125C];
  s32 f125C;       /* effect flag, cleared on setup */
  s32 f1260;       /* receives the 0x40-byte block from 0x080D9ADC */
  u8 _1[0x1274 - 0x1264];
  s32 f1274;       /* RAM buffer that receives the ramp table */
  u8 _2[0x12A0 - 0x1278];
  u16 f12A0;       /* effect parameter, cleared */
  u8 _3[0x12E0 - 0x12A2];
  u16 f12E0;       /* effect parameter, cleared */
  u8 _4[0x1320 - 0x12E2];
  u16 f1320;       /* effect parameter, cleared */
};
extern struct S_02021E90 gCameraState;
struct S_02027A00
{
  u8 _0[0x12];
  u8 f12;          /* effect tile x */
  u8 f13;          /* effect tile y */
  u16 f14;         /* cleared on setup */
};
extern struct S_02027A00 D_02027A00;

/* Set up a main-object visual effect: reserve a sprite object and hook it to
 * the object, upload the palette and a data block, build a 0x540-entry ramp in
 * a RAM buffer, then pass control to the object's completion callback. */
void sub_08061224(u8 *obj)
{
  u16 ramp[0x540];
  int limit;
  u8 *newObj = NULL;
  s32 i;
  u8 *cbArg0;
  u8 *cbArg1;
  u16 *rampPtr;
  allocWorkSlot(obj, 0, 4, 0);
  if (((*((u32 *) (obj + 0x3C))) == 0) || ((newObj = allocSpriteObject(), newObj == NULL)))
  {
    _call_via_r1((s32) obj, *((s32 *) (obj + 0x24)));
    return;
  }
  *((u8 **) (obj + 0x38)) = newObj;
  D_02027A00.f14 = 0;
  if (sub_08061C9C(D_02027A00.f12, D_02027A00.f13) == 0)
  {
    *((u8 *) (newObj + 0x2A)) = (*((u8 *) (newObj + 0x2A))) & 0xBF;
  }
  postDisplaySprite(1, (void *) 0x080D9B1C, 0x05000000, 0x20, 0x10);
  gCameraState.f125C = 0;
  sub_080C2E68((s32) (&gCameraState.f1260), 0x080D9ADC, 0x40);
  *((vu16 *) 0x03000830) &= 0xF0FF;
  gCameraState.f1320 = 0;
  gCameraState.f12E0 = 0;
  gCameraState.f12A0 = 0;
  sub_08061E04();
  sub_08061E34();
  i = 0;
  limit = 0x53F;
  cbArg0 = obj + 0x18;
  cbArg1 = obj + 0x22;
  rampPtr = ramp;
  do
  {
    *rampPtr = (u16) i;
    rampPtr++;
    i++;
  }
  while (((u32) i) <= limit);
  postDisplaySprite(1, ramp, gCameraState.f1274, 0xA80, 0x10);
  *((u8 *) (((((u32) ((s16) (*((s16 *) (obj + 0x22))))) * 2) + ((u32) obj)) + 0x19)) = 0;
  _call_via_r2(cbArg0, cbArg1, *((s32 *) 0x08671BB0));
}
