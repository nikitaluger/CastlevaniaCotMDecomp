void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Decrement the control countdown; while it is nonzero, set control+4 to
 * 0x16C1 and advance the script step. */
void sub_0803E940(void *arg0)
{
  void *gfx;
  void *state;
  u8 *anim;
  u8 *control;
  u8 *data;
  s32 countdown;
  u32 *stepHandler;
  data = (u8 *) arg0;
  gfx = *((void **) (data + 0x38));
 do { state = *((void **) (((u8 *) arg0) + 0x3C)); anim = ((u8 *) state) + 0x34; control = ((u8 *) state) + 0x48; setAnimationFrame(gfx, anim, 0, 1); countdown = (*((u16 *) (control + 0x02))) - 1; } while (0);
  *((u16 *) (control + 0x02)) = countdown;
  if ((countdown << 16) != 0)
  {
    *((u32 *) (control + 0x04)) = 0x000016C1;
    *((u8 *) (((u8 *) ((((u32) (*((s16 *) (((u8 *) arg0) + 0x22)))) * 2) + ((u32) arg0))) + 0x19)) = 0;
    stepHandler = (u32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *stepHandler);
  }
}
