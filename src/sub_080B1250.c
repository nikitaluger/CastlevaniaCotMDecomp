s32 sub_0801165C(void *, s32);
s32 sub_080B3158(void *);
s32 sub_080C31E4(void *, void *, s32);

/* Advance the entity's work state with zero acceleration, bounce its velocity
 * when it reaches the level bounds, then, when no blocking entity remains,
 * reset the script step and dispatch the next handler. */
void sub_080B1250(void *entity)
{
  s32 *dispatchArg;
  s32 newVelocity;
  void *work;

  work = *((void **) (((s8 *) entity) + 0x3C));
  sub_0801165C(work, 0);
  if ((((s32)(*((s32 *) (((s8 *) work) + 0x14)))) < 0) && (((s32)(*((s32 *) (((s8 *) work) + 0xC)))) <= 0x0137FFFF))
  {
    newVelocity = 0x8000;
    goto setVelocity;
  }
  if ((((s32)(*((s32 *) (((s8 *) work) + 0x14)))) > 0) && (((s32)(*((s32 *) (((s8 *) work) + 0xC)))) > 0x01A00000))
  {
    newVelocity = -0x8000;
    setVelocity:
    *((s32 *) (((s8 *) work) + 0x14)) = newVelocity;
  }
  if (sub_080B3158(entity) != 0)
  {
    *(((s8 *) (((*((s16 *) (((s8 *) entity) + 0x22))) * 2) + entity)) + 0x19) = 0;
    dispatchArg = (s32 *) 0x08671BB0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *dispatchArg);
  }
}
