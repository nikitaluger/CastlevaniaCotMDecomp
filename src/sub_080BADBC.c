s32 startScriptOnce(void *, s32, s32);
s32 setFacingDirection(void *, s32);
s32 sub_080BB940(void *, void *);
s32 sub_080C31E4(void *, void *, s32);

/* Grabbed-target step: mark the attachment as held, aim the work object at the
 * grabbed target and drag it along; after step 0x10, once the target's action
 * byte clears, switch it to its held animation and advance the script. */
void sub_080BADBC(void *entity)
{
  u8 action;
  void *attach;
  void *work;
  void *target;
  s32 *scriptTable;
  work = *((void **) (((s8 *) entity) + 0x3C));
  attach = work + 0x48;
  target = *((void **) (((s8 *) entity) + 0x4C));
  *((s32 *) (((s8 *) attach) + 0x4C)) = 1;
  sub_080BB940(work, target);
  setFacingDirection(target, *((s32 *) (((s8 *) work) + 8)));
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)))) > 0x10U)
  {
    action = *((u8 *) (((s8 *) target) + 0x25));
    if (action == 0)
    {
      startScriptOnce(target, 5, 0);
      *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = action;
      scriptTable = (s32 *) 0x08671BB0;
      sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
    }
  }
}
