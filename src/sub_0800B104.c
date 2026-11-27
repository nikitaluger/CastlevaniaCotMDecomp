extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern void sub_0800B888(void *, void *);
extern void sub_0800B9A8(s32, s32, void *);
extern void sub_080103A0(u8, u8);
extern void sub_080C31E4(void *, void *, void *);
struct S_02021E90
{
  u8 _0[0x146C];
  u16 f146C;
};
extern struct S_02021E90 gCameraState;
extern void *gPoseScriptCallbacks;
extern void *gMainObjTimerCallbacks;
/* Entity reaction update: when a global state flag is set, play an effect,
 * spawn the matching graphics, clear the current pose byte and run a script. */
void sub_0800B104(u8 *entity)
{
  u8 *dataPtr;
  dataPtr = *((u8 **) (entity + 0x3C));
  if (gCameraState.f146C & 2)
  {
    sub_08005E80(0x159);
    sub_0800B824(0x81D7, 0x270, 0x600);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = 0;
    {
      void **fnaddr = &gPoseScriptCallbacks;
      sub_080C31E4(entity + 0x18, entity + 0x22, *fnaddr);
    }
  } else if (gCameraState.f146C & 1) {
    u8 v50;
    u8 *r4;
    u16 r7 = 0;
    sub_08005E80(0x15B);
    v50 = *(entity + 0x50);
    r4 = entity + 0x54;
    sub_080103A0(v50, *r4);
    sub_0800B9A8((s8) (*r4), 2, dataPtr);
    sub_0800B888(entity, dataPtr);
    sub_0800B824(0x81D9, 0x270, 0x600);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = r7;
    {
      void **fnaddr = &gMainObjTimerCallbacks;
      sub_080C31E4(entity + 0x18, entity + 0x22, *fnaddr);
    }
  }
}
