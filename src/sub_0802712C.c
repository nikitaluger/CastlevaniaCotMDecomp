extern s32 sub_08027A4C(void *, s32, void *, void *);
extern s32 sub_080C31E4(void *, void *, s32);

/* Path command: reset the motion vector; when flag 0x4 is set, snap the
 * motion offset and re-run the command stream, otherwise rotate the offset
 * into the actor's working X/Y position. */
void sub_0802712C(void *arg0)
{
  s32 *stream;
  void *work;
  void *motion;
  work = *((void **) (((s8 *) arg0) + 0x3C));
  motion = work + 0x48;
  *((s32 *) (((s8 *) work) + 0x14)) = 0;
  *((s32 *) (((s8 *) work) + 0x10)) = 0;
  if (4 & (*((u16 *) (((s8 *) arg0) + 0x64))))
  {
    *((s32 *) (((s8 *) motion) + 0xC)) = (s32) (*((s32 *) (((s8 *) motion) + 8)));
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    stream = (s32 *) 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *stream);
    return;
  }
  sub_08027A4C(arg0, *((s32 *) (((s8 *) motion) + 8)), work + 8, work + 0xC);
}
