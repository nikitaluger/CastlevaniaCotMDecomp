struct S_02025FF0
{
  u8 _[0x1870];
  u32 v;
};
extern struct S_02025FF0 D_02025FF0;
s32 sub_0808DBF8(s32, s32, s32);
void sub_08005E80(u16);
void sub_080C31E0(void *, s32);

/* Spawn a level-8 effect just above the work object, play sound 0x189 and run
 * the actor's update callback; flag the parent as hit when it is not the
 * tracked player object. */
void sub_08032E3C(void *arg0)
{
  void *work = *((void **) (((u8 *) arg0) + 0x3C));
  u32 player = D_02025FF0.v;
  void *parent = *((void **) (((u8 *) arg0) + 0x28));
  if (((u32) parent) != D_02025FF0.v)
  {
    *((u8 *) (((u8 *) parent) + 0x80)) = 1;
  }
  sub_0808DBF8(*((s32 *) (((u8 *) work) + 8)), (*((s32 *) (((u8 *) work) + 0xC))) + 0x80000, 8);
  sub_08005E80(0x189);
  sub_080C31E0(arg0, *((s32 *) (((u8 *) arg0) + 0x24)));
}
