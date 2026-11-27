s32 unlinkAndFreeObject();
s32 sub_0801F02C();
void sub_080C31E0(void *, s32);

/* Release the entity's child state block: unregister the entity from its
 * owner's tracking table (implicit arg0), free the linked object at work+0x28
 * when present, then run the state block's callback at +0x24. */
void sub_0801EF68(void *entity)
{
  void *work;
  work = *((void **) (((u8 *) entity) + 0x3C));
  sub_0801F02C();
  if ((*((s32 *) (((u8 *) work) + 0x28))) != 0)
  {
    entity++;
    entity--;
    unlinkAndFreeObject();
  }
  sub_080C31E0(entity, *((s32 *) (((u8 *) work) + 0x24)));
}
