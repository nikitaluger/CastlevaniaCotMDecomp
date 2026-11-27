extern void stepAnimationTrack(void *);
/* Step an animation and adjust a 16.16 accumulator by whole units for specific
 * frame transitions; returns a status code and updates the stored frame. */
int sub_0804A4F0(u8 *entity, u8 *unused, u8 *state, u8 *prev)
{
  u8 *entityRef = entity;
  u8 *statePtr = state;
  u8 *prevPtr = prev;
  u32 result = 0;
  u16 oldFrame;
  u16 newFrame;
  u8 category;
  stepAnimationTrack(entity);
  oldFrame = *((u16 *) (prevPtr + 6));
  newFrame = *((u16 *) (entityRef + 0x28));
  if (oldFrame == newFrame)
  {
    goto epilogue;
  }
  category = prevPtr[8];
  switch (category)
  {
    case 2:
      newFrame = *((u16 *) (entityRef + 0x28));
      switch (newFrame)
    {
      case 0xF:
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
        break;

      case 0xA:
        if (oldFrame == 5)
      {
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
      }
      {
        u16 oldFrameReload = *((u16 *) (prevPtr + 6));
        if (oldFrameReload != 0xF)
        {
          goto store;
        }
        goto add_shared;
      }

      case 5:
        *((u32 *) (statePtr + 0xC)) += 0x10000;
        result = 1;
        break;

    }

      break;

    case 7:
      newFrame = *((u16 *) (entityRef + 0x28));
      switch (newFrame)
    {
      case 0x14:
        *((u32 *) (statePtr + 0xC)) += 0x10000;
        result = 1;
        break;

      case 0x1A:
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
        break;

      case 0x17:
        if (oldFrame == 0x14)
      {
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
      }
        if ((*((u16 *) (prevPtr + 6))) != 0x1A)
      {
        goto store;
      }
        goto add_shared;

    }

      break;

    case 0xC:
      newFrame = *((u16 *) (entityRef + 0x28));
      switch (newFrame)
    {
      case 0x17:
        goto add_shared;

      case 0x1D:
        result = 1;
        break;

      case 0x22:
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
        break;

      case 0x27:
        *((u32 *) (statePtr + 0xC)) -= 0x10000;
        break;

      case 0x2C:
        *((u32 *) (statePtr + 0xC)) += 0x10000;
        result = 2;
        break;

    }

      break;

  }

  goto store;
  add_shared:
  *((u32 *) (statePtr + 0xC)) += 0x10000;

  store:
  *((u16 *) (prevPtr + 6)) = *((u16 *) (entityRef + 0x28));
  epilogue:
  return result;

}
