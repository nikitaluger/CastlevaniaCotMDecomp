extern s32 sub_08005E80(s32);
extern s32 sub_080114DC(s32, s32, s32, s32);
extern s32 sub_080AC908(s32, s32, void *, void *);
extern s32 sub_080B06F4(void *, s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* When an effect reaches its final state, launch an effect, play a sound, and
 * end the state. */
void sub_080AB66C(void *self)
{
  s32 gfx;
  s32 anim;
  int cbTable;
  void *state;
  void *entity;
  gfx = *((s32 *) (((s8 *) self) + 0x38));
  entity = *((void **) (((s8 *) self) + 0x3C));
  anim = (s32)entity + 0x34;
  state = (void *)((s32)entity + 0x48);
  sub_080AC908(gfx, anim, entity, state);
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19))) == 0x3C)
  {
    sub_080114DC(gfx, anim, 4, 0);
    sub_080B06F4((void *)((s32)entity + 0x68), *((s32 *) (((s8 *) entity) + 8)), (*((s32 *) (((s8 *) entity) + 0xC))) + 0xFFF00000);
    *((s8 *) (((s8 *) state) + 0x11)) = 0;
    sub_08005E80(0x17B);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
    cbTable = 0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *((s32 *) cbTable));
  }
}
