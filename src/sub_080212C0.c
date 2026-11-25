s32 sub_080161F0();
s32 sub_080212E4();
void sub_080C31E0(void *, s32);

/* Release the entity's child state block: unregister the entity from its
 * owner's tracking table (implicit arg0), free the linked object at work+0x28
 * when present, then run the state block's callback at +0x24. */
void sub_080212C0(void *entity)
{
  void *work;
  work = *((void **) (((u8 *) entity) + 0x3C));
  sub_080212E4();
  if ((*((s32 *) (((u8 *) work) + 0x28))) != 0)
  {
    entity++;
    entity--;
    sub_080161F0();
  }
  sub_080C31E0(entity, *((s32 *) (((u8 *) work) + 0x24)));
}
