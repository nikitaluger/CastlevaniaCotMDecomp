extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern void sub_0800B888(void *, void *);
extern void sub_0800B9A8(s32, s32, void *);
extern void sub_080103BC(u8);
extern void sub_080C31E4(void *, void *, void *);
struct S_02021E90
{
  u8 _0[0x146C];
  u16 f146C;
};
extern struct S_02021E90 D_02021E90;
extern void *D_08671BC0;
extern void *D_08671BB0;

/* Entity reaction update: when a global state flag is set, play an effect,
 * spawn the matching graphics, clear the current pose byte and run a script. */
void sub_0800B360(u8 *entity)
{
  u8 *dataPtr;
  dataPtr = *((u8 **) (entity + 0x3C));
  if (D_02021E90.f146C & 2)
  {
    sub_08005E80(0x159);
    sub_0800B824(0x81DA, 0x270, 0x600);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = 0;
    {
      void **fnaddr = &D_08671BC0;
      sub_080C31E4(entity + 0x18, entity + 0x22, *fnaddr);
    }
  } else if (D_02021E90.f146C & 1) {
    u8 *valuePtr;
    u16 zero = 0;
    sub_08005E80(0x15A);
    valuePtr = entity + 0x50;
    sub_080103BC(*valuePtr);
    sub_0800B9A8((s8) (*valuePtr), 0, dataPtr);
    sub_0800B888(entity, dataPtr);
    sub_0800B824(0x81DC, 0x270, 0x600);
    *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = zero;
    {
      void **fnaddr = &D_08671BB0;
      sub_080C31E4(entity + 0x18, entity + 0x22, *fnaddr);
    }
  }
}
