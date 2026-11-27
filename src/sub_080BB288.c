extern s32 sub_08005E80(s32);
extern s32 advanceMotion(void *, s32);
extern s32 sub_080BB984(void *, s32);
extern s32 sub_080BBA4C(void *);
extern s32 sub_080BBB60(void *);
extern s32 sub_080C31E4(void *, void *, s32);

/* Movement/animation step for a multi-part actor: update the body's vertical
 * wobble and velocity and integrate its position; on step 2 play a sound and
 * reposition the attached parts, on step 0xC set a horizontal velocity from
 * the linked object's facing byte, clear the step flag and advance the script. */
void sub_080BB288(void *arg0)
{
  int scriptTable;
  void *body;
  void *work;
  void *other;
  body = *((void **) (((s8 *) arg0) + 0x3C));
  work = body + 0x48;
  other = *((void **) (((s8 *) arg0) + 0x4C));
  sub_080BB984(body, work);
  sub_080BBB60(body);
  advanceMotion(body, 0);
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 2)
  {
    sub_08005E80(0x1AB);
    sub_080BBA4C(arg0);
  }
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19))) == 0xC)
  {
    *((s32 *) (((s8 *) body) + 0x10)) = (s32) (0 - ((*((s8 *) (((s8 *) other) + 0x35))) * 0x34000));
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
    scriptTable = 0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *((s32 *) scriptTable));
  }
}
