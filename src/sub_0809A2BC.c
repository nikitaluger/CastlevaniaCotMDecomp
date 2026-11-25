extern s32 sub_080057F8(void);
extern void sub_080114DC(void *, void *, s32, s32);
extern void sub_0809C5E4(s32);
extern void sub_080C31E4(void *, void *, void *);
extern void *D_08671BB0;

/* Advance the actor's work offset by +-1.0 from its script flag, periodically
 * signal its parts object, and on trigger start an animation, clear the current
 * script step and dispatch the next script callback. */
void sub_0809A2BC(void *arg0)
{
  void *entity = arg0;
  void *sprite = *((void **) (((u8 *) arg0) + 0x38));
  u8 *work = *((u8 **) (((u8 *) arg0) + 0x3C));
  u8 *animState = work + 0x34;
  u8 *parts = work + 0x48;
  s16 scriptIndex = *((s16 *) (((u8 *) arg0) + 0x22));
  u8 flag;
  if ((((u8 *) arg0)[(scriptIndex * 2) + 0x19] & 2) == 0)
  {
    *((s32 *) (work + 0x08)) = (*((s32 *) (work + 0x08))) + 0x10000;
  }
  else
  {
    *((s32 *) (work + 0x08)) = (*((s32 *) (work + 0x08))) + ((s32) 0xFFFF0000);
  }
  if ((sub_080057F8() & 0x3F) == 0)
  {
    sub_0809C5E4(*((s32 *) (parts + 0x08)));
  }
  if (((u8 *) arg0)[0x4C] != 0)
  {
    sub_080114DC(sprite, animState, 0, 0);
    scriptIndex = *((s16 *) (((u8 *) arg0) + 0x22));
    ((u8 *) arg0)[(scriptIndex * 2) + 0x19] = 0;
    {
      void **scriptCb = &D_08671BB0;
      sub_080C31E4(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *scriptCb);
    }
  }
}
