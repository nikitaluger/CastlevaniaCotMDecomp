void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 sub_08013558(void *, void *, s32);
void spawnContactEffectOnHit(void *, s32);
void sub_0803B1F4(void *, void *, void *);
void updateActorWorldPosition(void *);
void sub_0803B1A4(void *);
s32 sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);
s32 updateObjectDisplayState(void *, void *);
void syncChildObjectParams(void *, void *, void *);
void sub_0803B1B4(void *, void *);
void syncSpriteToWorldPosition(void *, void *);

/* Sub-state byte at task + index*2 + 0x19. */
struct TaskState { u8 _0[0x19]; u8 state; };

/* Runs a scripted task: validates the actor/subject pair, advances its state
 * machine, and dispatches the current handler from the table at task+0x14. */
void sub_08033054(void *task)
{
  u8 *stateEntry;
  void *actor = *((void **) (((u8 *) task) + 0x38));
  void *subject = *((void **) (((u8 *) task) + 0x3C));
  applySpritePaletteVariant(task, actor);
  if (checkActorViewBounds(actor, subject) == 1)
  {
    *((u8 *) (((u8 *) (*((void **) (((u8 *) task) + 0x30)))) + 0x80)) = 0;
    return;
  }
  if (sub_08013558(actor, subject, *((s32 *) (((u8 *) subject) + 0x28))) != 0)
  {
    spawnContactEffectOnHit(task, *((s32 *) (((u8 *) subject) + 0x28)));
  }
  {
    void *stateData = ((u8 *) subject) + 0x54;
    sub_0803B1F4(task, subject, stateData);
    if (1 & (*((u16 *) subject)))
    {
      u8 *stateArgs;
      s32 *callbacks;
      updateActorWorldPosition(task);
      sub_0803B1A4(stateData);
      {
        void *parent = *((void **) (((u8 *) task) + 0x30));
        sub_080C31E0(parent, *((s32 *) (((u8 *) parent) + 0x24)));
      }
      {
        s32 stateOffset = ((s16) (*((u16 *) (((u8 *) task) + 0x22)))) * 2;
        u8 *stateBytePtr = (u8 *)(stateOffset + (u32)task);
        stateBytePtr[0x19] = 0;
      }
      callbacks = (s32 *) 0x08671BB0;
      stateEntry = ((u8 *) task) + 0x18;
      stateArgs = stateEntry;
      sub_080C31E4(stateArgs, ((u8 *) task) + 0x22, *callbacks);
      {
        s32 stateOffset = ((s16) (*((u16 *) (((u8 *) task) + 0x22)))) * 2;
        u8 *stateBytePtr = (u8 *)(stateOffset + (u32)task);
        stateBytePtr[0x19] = stateBytePtr[0x19] + 1;
      }
      {
        s32 stateOffset = *(s16 *)((u8 *)task + 0x22) * 2;
        u8 handlerIndex;
        u32 handlerTable;
        stateEntry += stateOffset;
        handlerIndex = *stateEntry;
        handlerTable = *((u32 *) (((u8 *) task) + 0x14));
        sub_080C31E0(task, *((s32 *) (handlerTable + (handlerIndex * 4))));
      }
      return;
    }
  }
  syncChildObjectParams(task, subject, actor);
  if (updateObjectDisplayState(actor, subject) == 0)
  {
    *((u32 *) (((u8 *) task) + 0x14)) = 0x0866DD08;
    *((u16 *) (((u8 *) task) + 0x22)) = (*((u16 *) (((u8 *) task) + 0x22))) + 1;
    {
      s32 stateOffset = ((s16) (*((u16 *) (((u8 *) task) + 0x22)))) * 2;
      u8 *stateBytePtr = (u8 *)(stateOffset + (u32)task);
      stateBytePtr[0x19] = stateBytePtr[0x19] + 1;
    }
    {
      s32 stateOffset = *(s16 *)((u8 *)task + 0x22) * 2;
      u8 *localEntry;
      u8 handlerIndex;
      u32 handlerTable;
      localEntry = (u8 *)task;
      localEntry += 0x18;
      localEntry += stateOffset;
      handlerIndex = *localEntry;
      handlerTable = *((u32 *) (((u8 *) task) + 0x14));
      sub_080C31E0(task, *((s32 *) (handlerTable + (handlerIndex * 4))));
    }
    *((u16 *) (((u8 *) task) + 0x22)) = (*((u16 *) (((u8 *) task) + 0x22))) - 1;
  }
  else
  {
    void *stateData = ((u8 *) subject) + 0x54;
    sub_0803B1B4(subject, stateData);
  }
  syncSpriteToWorldPosition(task, actor);
}
