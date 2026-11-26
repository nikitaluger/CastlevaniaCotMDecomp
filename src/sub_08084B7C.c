extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_08086E28(void);
extern u8 gGameStatus[];
struct GameState
{
  u8 _0[0x14ED];
  u8 command;
};
extern struct GameState gMainWorkspace;
struct SpawnedEntity
{
  u8 _0[0x7C];
  u16 flags;
};
/* Runs the effect selected by the global command byte: spawns or resets an
 * entity, adjusts the caller's state counters and timer, and returns a
 * possibly modified value. */
u32 sub_08084B7C(s32 owner, u8 *state, u32 value, u8 key)
{
  u8 *stateBase = gGameStatus;
  u8 command = gMainWorkspace.command;
  void *spawned;
  u32 *statusPtr;
  u32 *zeroPtr;
  u32 statusVal1;
  u32 statusVal2;
  u32 decStatus;
  u32 timerVal;
  s32 timerHigh;
  switch (command)
  {
    case 0x2A:
      spawned = sub_0806D2A0(owner, 0x34, 0x0A, 0x12);
      if (spawned != NULL)
    {
      ((struct SpawnedEntity *) spawned)->flags = 0x1000;
    }
      break;

    case 0x35:
      zeroPtr = (u32 *) (state + 0x98);
      *zeroPtr = 0;
      value |= 0xE0000000;
      statusPtr = (u32 *) (state + 0x94);
      if ((*statusPtr) == 3)
    {
      statusVal1 = *((u32 *) (state + 0x40));
      if (statusVal1 == 1)
      {
        *statusPtr = statusVal1;
      }
      statusVal2 = *((u32 *) (state + 0x40));
      if (statusVal2 == 2)
      {
        *statusPtr = statusVal2;
      }
    }
      break;

    case 0x38:
      decStatus = *((u32 *) (state + 0x94));
      decStatus--;
      if (decStatus <= 1)
    {
      *((u32 *) (state + 0x94)) = 3;
    }
      value = value >> 1;
      if (value == 0)
    {
      value = 1;
    }

    case 0x29:

    case 0x22:
      spawned = sub_0806D2A0(owner, 0x34, 0x0A, 0x12);
      if (spawned != NULL)
    {
      *((u16 *) (((u8 *) spawned) + 0x7C)) = 0;
    }
      sub_08086E28();
      break;

    case 0xAA:
      value = 0x270F;
      break;

    case 0x71:

    case 0x72:

    case 0x73:

    case 0x74:

    case 0x75:

    case 0x76:

    case 0x77:

    case 0x78:

    case 0x79:

    case 0x7A:
      if (key == stateBase[0x304])
    {
      u32 *timer;
      u32 *pC0;
      spawned = sub_0806D2A0(owner, 0x3C, 0x0A, 0x12);
      if (spawned != NULL)
      {
        *((u16 *) (((u8 *) spawned) + 0x7C)) = 0;
      }
      sub_08086E28();
      timer = (u32 *) (stateBase + 0x2CC);
      timerVal = *timer;
      timerHigh = ((s32) timerVal) >> 16;
      if (value <= ((u32) timerHigh))
      {
        *timer = timerVal - (value << 16);
        pC0 = (u32 *)(state + 0xC0);
        *pC0 = value >> 3;
        value |= 0xF0000000;
      }
      else
      {
        value -= timerHigh;
        pC0 = (u32 *)(state + 0xC0);
        if (timerHigh < 0)
        {
          timerHigh += 7;
        }
        *pC0 = timerHigh >> 3;
        *timer = 0;
      }
    }
      break;

  }

  return value;
}
