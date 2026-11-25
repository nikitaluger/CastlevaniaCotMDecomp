s32 sub_08005E80(s32);
s32 sub_080BB984(s32, s32);
s32 sub_080BB9C8(void *);
s32 sub_080BBA4C(void *);
s32 sub_080BE6F8();
s32 sub_080C31E4(void *, void *, s32);

/* Attached-walk step: bob the actor's vertical velocity and update its part
 * animation each tick; at step 0xC play the grab sound and reposition the
 * attached parts, and at step 0x3C restore the music and advance the script. */
void sub_080BA688(void *entity)
{
  s32 *scriptTable;
  s32 work;
  work = *((s32 *) (((s8 *) entity) + 0x3C));
  sub_080BB984(work, work + 0x48);
  sub_080BB9C8(entity);
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19))) == 0xC)
  {
    sub_08005E80(0x1AA);
    sub_080BBA4C(entity);
  }
  if ((*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19))) == 0x3C)
  {
    sub_080BE6F8();
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19)) = 0;
    scriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *scriptTable);
  }
}
