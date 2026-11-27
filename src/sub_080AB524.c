extern u32 nextRandomWord(void);
extern void setSpriteFacingToTarget(void *, s32);
extern void sub_080AC908(void *, void *, void *, void *);
void sub_080C31E8(void *, void *, s32, s32);
extern u16 D_081021D4[];

/* Entity update: while this entity's state byte (indexed by its animation index) is 8,
 * decrement a timer; clear the state byte and dispatch a handler when it expires,
 * picking the handler argument from the entity's mode byte (random bit, always 1, or 0). */
void sub_080AB524(void *arg0)
{
  u8 *entity = (u8 *) arg0;
  s32 pick = 0;
  void *obj = *((void **) (entity + 0x38));
  u8 *state = *((u8 **) (entity + 0x3C));
  void *state34 = state + 0x34;
  u8 *state48 = state + 0x48;
  s32 remaining;
  u8 *flagPtr;
  s32 flags;
  sub_080AC908(obj, state34, state, state48);
  setSpriteFacingToTarget(obj, *((s32 *) (state + 0x08)));
  if (entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] == 8)
  {
    remaining = (*((u8 *) (state48 + 0x1C))) - 1;
    *((u8 *) (state48 + 0x1C)) = remaining;
    if (((u8) remaining) != 0)
    {
      entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] = 0;
      {
        s32 *handlerSlot = (s32 *) 0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, 1, *handlerSlot);
      }
    }
    else
    {
      s32 mode = *((u8 *) (state + 0x90));
      if (mode != 1)
      {
        if (mode > 1)
        {
          pick = 0;
        }
        else
          if (mode == 0)
        {
          pick = nextRandomWord() & 1;
        }
      }
      else
      {
        pick = 1;
      }
      flagPtr = state48 + 0x48;
      flags = (1 << pick) | (*flagPtr);
      {
        s32 zero = 0;
        *flagPtr = flags;
        if (((u8) flags) == 3)
        {
          *flagPtr = zero;
        }
        entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] = zero;
      }
      {
        s32 *handlerSlot = (s32 *) 0x08671BD0;
        sub_080C31E8(entity + 0x18, entity + 0x22, D_081021D4[pick], *handlerSlot);
      }
    }
  }
}
