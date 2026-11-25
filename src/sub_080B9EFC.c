s32 sub_08098664(s32, s32, s32);
s32 sub_080988B8(s32, s32);
s32 sub_080BB8AC(void *);
s32 sub_080BB940(void *, s32);
s32 sub_080BE8C0(s32);
s32 sub_080C31E4(void *, void *, s32);

/* Target-attach step: put the chosen target (entity+0x4C) into its hooked
 * mode, aim the work object at it and move the target along with it; after
 * 0x3C steps release the attachment and advance the script. */
void sub_080B9EFC(void *entity)
{
  s32 target;
  void *work;
  void *attach;
  s32 *scriptTable;
  work = *((void **) (((s8 *) entity) + 0x3C));
  attach = work + 0x48;
  target = *((s32 *) (((s8 *) entity) + 0x4C));
  sub_08098664(target, 1, 1);
  sub_080BB940(work, target);
  sub_080988B8(target, *((s32 *) (((s8 *) work) + 8)));
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19))) == 0x3C)
  {
    sub_080BE8C0(*((s32 *) (((s8 *) attach) + 0x34)));
    sub_080BB8AC(attach);
    attach = (u8 *) entity;
    *((s8 *) (((s8 *) (((*((s16 *) (attach + 0x22))) * 2) + entity)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
  }
}
