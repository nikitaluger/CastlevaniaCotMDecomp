extern void sub_08005E80(s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);

/* Spawn a one-shot effect object for actor states 0/1/2, gated by a flag at
 * +0xB8 and a condition at +0x2C; states 0 and 1 also play a sound. */
void sub_0806932C(void *owner, void *actor)
{
  u8 *statePtr = ((u8 *) actor) + 0x129;
  u8 state = *statePtr;
  switch (state)
  {
    case 0:
      if ((*((u16 *) (((u8 *) actor) + 0x2C))) == 6)
    {
      s32 *guard = (s32 *) (((u8 *) actor) + 0xB8);
      if ((*guard) == 0)
      {
        void *obj = sub_0806D2A0(owner, 0x79, 10, 0x12);
        if (obj != 0)
        {
          *((s32 *) (((u8 *) obj) + 0x7C)) = *statePtr;
        }
        sub_08005E80(0x1C4);
        *guard = 1;
      }
    }
      break;

    case 1:
      if ((*((u16 *) (((u8 *) actor) + 0x2C))) == 4)
    {
      s32 *guard = (s32 *) (((u8 *) actor) + 0xB8);
      if ((*guard) == 0)
      {
        void *obj = sub_0806D2A0(owner, 0x79, 10, 0x12);
        if (obj != 0)
        {
          *((s32 *) (((u8 *) obj) + 0x7C)) = *statePtr;
        }
        sub_08005E80(0x1C4);
        *guard = state;
      }
    }
      break;

    case 2:
      if ((*((u16 *) (((u8 *) actor) + 0x2C))) == 4)
    {
      s32 *guard = (s32 *) (((u8 *) actor) + 0xB8);
      state = 0x7A;
      if ((*guard) == 0)
      {
        void *obj = sub_0806D2A0(owner, state, 10, 0x12);
        if (obj != 0)
        {
          *((s32 *) (((u8 *) obj) + 0x7C)) = *statePtr;
        }
        *guard = 1;
      }
    }
      break;

  }

}
