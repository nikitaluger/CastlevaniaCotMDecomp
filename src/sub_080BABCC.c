extern s32 sub_08005E80(s32);
extern s32 sub_080BB984(void *, void *);
extern s32 sub_080BE824(s32);
extern s32 sub_080BE82C(s32, s32, s8);
extern s32 sub_080C31E4(void *, void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);

/* Effect-actor script step: tick the body animation and clear its counter; on
 * action 8 start an attack, and on action 0x28 advance a short burst counter,
 * ending the script after at most three steps. */
void sub_080BABCC(void *arg0)
{
  void *entity;
  void *body;
  s32 unused;
  u32 burstCount;
  void *litTable;
  s32 *litTable2;
  entity = *((s32 *) ((s8 *) arg0 + 0x3C));
  body = (void *)((s8 *)entity + 0x48);
  unused = *((void **) ((s8 *) arg0 + 0x4C));
  sub_080BB984(entity, body);
  sub_080BE824(*((s32 *) ((s8 *) body + 0x2C)));
  if (*((u8 *) ((s8 *) arg0 + (*((s16 *) ((s8 *) arg0 + 0x22)) * 2) + 0x19)) == 8)
  {
    sub_08005E80(0x1A9);
    sub_080BE82C(*((s32 *) ((s8 *) body + 0x30)), *((s32 *) ((s8 *) body + 0x54)), (s8)(*((u8 *) ((s8 *) unused + 0x35))));
  }
  if (*((u8 *) ((s8 *) arg0 + (*((s16 *) ((s8 *) arg0 + 0x22)) * 2) + 0x19)) == 0x28)
  {
    burstCount = *((u32 *) ((s8 *) body + 0x4C)) + 1;
    *((u32 *) ((s8 *) body + 0x4C)) = burstCount;
    if (burstCount <= 3U)
    {
      *((s8 *) ((s8 *) arg0 + (*((s16 *) ((s8 *) arg0 + 0x22)) * 2) + 0x19)) = 0;
      litTable = (void *)0x08671BD0;
      sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 3, *((s32 *)litTable));
      return;
    }
    *((s8 *) ((s8 *) arg0 + (*((s16 *) ((s8 *) arg0 + 0x22)) * 2) + 0x19)) = 0;
    litTable2 = (s32 *)0x08671BB0;
    sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *litTable2);
  }
}
