/* Room-entry transition check: compares this entity's state id against the
 * three ids in the transition table, arming/clearing the transition and
 * recording it on the object when it takes effect. */
void sub_0803B0F8(void *arg0, void *arg1, void *arg2, void *arg3)
{
  s32 value;
  value = *((u16 *) (((s8 *) arg1) + 0x28));
  if ((value == (*((u16 *) (((s8 *) arg3) + 0)))) || (value == (*((u16 *) (((s8 *) arg3) + 8)))))
  {
    if ((*((u8 *) (((s8 *) arg2) + 5))) == 0)
    {
      *((u8 *) (((s8 *) arg2) + 5)) = 1U;
      *((u8 *) (((s8 *) arg2) + 4)) = (u8) ((*((u8 *) (((s8 *) arg2) + 4))) + 1);
    }
    value = 0;
    goto store;
  }
  if (value == (*((u16 *) (((s8 *) arg3) + 4))))
  {
    *((u8 *) (((s8 *) arg2) + 5)) = 0U;
    return;
  }
  if (((*((u8 *) (((s8 *) arg2) + 5))) == 0) && ((*((s32 *) (((s8 *) arg0) + 0x10))) == 0))
  {
    value = *((s32 *) (((s8 *) arg2) + 0));
    store:
    *((s32 *) (((s8 *) arg0) + 0x10)) = value;

  }
}
