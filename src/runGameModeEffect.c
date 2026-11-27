extern void *spawnEntity(s32, s32, s32, s32);
extern void recordSpawnEvent(void);
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
/* Runs the effect chosen by the global game-mode byte: spawns or clears an entity, updates the caller's state counters and fixed-point timer, and returns the possibly modified value. */ u32 runGameModeEffect(s32 owner, u8 *state, u32 result, u8 eventKey)
{
  u8 *gameState = gGameStatus;
  u8 command = gMainWorkspace.command;
  void *spawned;
  u32 *statusCounterPtr;
  u32 *clearPtr;
  u32 statusValueA;
  u32 statusValueB;
  u32 decrementedStatus;
  u32 timerValue;
  s32 timerHigh;
  switch (command)
  {
    case 0x2A:
      spawned = spawnEntity(owner, 0x34, 0x0A, 0x12);
      if (spawned != NULL)
    {
      ((struct SpawnedEntity *) spawned)->flags = 0x1000;
    }
      break;

    case 0x35:
      clearPtr = (u32 *) (state + 0x98);
      *clearPtr = 0;
      result |= 0xE0000000;
      statusCounterPtr = (u32 *) (state + 0x94);
      if ((*statusCounterPtr) == 3)
    {
      statusValueA = *((u32 *) (state + 0x40));
      if (statusValueA == 1)
      {
        *statusCounterPtr = statusValueA;
      }
      statusValueB = *((u32 *) (state + 0x40));
      if (statusValueB == 2)
      {
        *statusCounterPtr = statusValueB;
      }
    }
      break;

    case 0x38:
      decrementedStatus = *((u32 *) (state + 0x94));
      decrementedStatus--;
      if (decrementedStatus <= 1)
    {
      *((u32 *) (state + 0x94)) = 3;
    }
      result = result >> 1;
      if (result == 0)
    {
      result = 1;
    }

    case 0x29:

    case 0x22:
      spawned = spawnEntity(owner, 0x34, 0x0A, 0x12);
      if (spawned != NULL)
    {
      *((u16 *) (((u8 *) spawned) + 0x7C)) = 0;
    }
      recordSpawnEvent();
      break;

    case 0xAA:
      result = 0x270F;
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
      if (eventKey == gameState[0x304])
    {
      u32 *timerPtr;
      u32 *stateTimerPtr;
      spawned = spawnEntity(owner, 0x3C, 0x0A, 0x12);
      if (spawned != NULL)
      {
        *((u16 *) (((u8 *) spawned) + 0x7C)) = 0;
      }
      recordSpawnEvent();
      timerPtr = (u32 *) (gameState + 0x2CC);
      timerValue = *timerPtr;
      timerHigh = ((s32) timerValue) >> 16;
      if (result <= ((u32) timerHigh))
      {
        *timerPtr = timerValue - (result << 16);
        stateTimerPtr = (u32 *)(state + 0xC0);
        *stateTimerPtr = result >> 3;
        result |= 0xF0000000;
      }
      else
      {
        result -= timerHigh;
        stateTimerPtr = (u32 *)(state + 0xC0);
        if (timerHigh < 0)
        {
          timerHigh += 7;
        }
        *stateTimerPtr = timerHigh >> 3;
        *timerPtr = 0;
      }
    }
      break;

  }

  return result;
}
