typedef struct 
{
  u8 _pad0[0x28];
  u8 actionId[2];
  u16 actionTimer;
  u16 actionState;
  u8 _pad1[0x40 - 0x2E];
  s32 variant;
  u8 _pad2[0x70 - 0x44];
  s32 active;
} ActorScriptState;
extern void sub_08003740(void *, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_0806DE0C(void);
struct S_02025FF0
{
  u8 _0[0x14EE];
  u8 phase;
  u8 _1[0x14F4 - 0x14EF];
  u32 subPhase;
  u8 _2[0x14FC - 0x14F8];
  u32 flag;
};
extern struct S_02025FF0 D_02025FF0;
extern u32 D_0866F0DC[];
inline u32 inline_fn()
{
  return D_02025FF0.subPhase;
}

/* React to a global game-phase change by retargeting an actor's current action:
 * switch animations for phases 0x17/0x18, run the phase-0x47 sub-state branch
 * that picks character-specific data, then restart the actor's action. */
void sub_08086648(s32 entity, ActorScriptState *actor)
{
  switch (D_02025FF0.phase)
  {
    case 0x17:
      if ((actor->actionState == 0x12) && (actor->active != 0))
    {
      actor->actionState = 8;
      actor->actionTimer = 1;
      sub_08003740(((void *) actor) + 0x28, entity);
    }
      break;

    case 0x18:
      if ((actor->actionState == 0x0B) && (actor->active != 0))
    {
      actor->actionState = 7;
      actor->actionTimer = 1;
      sub_08003740(((void *) actor) + 0x28, entity);
    }
      break;

    case 0x47:
      if (((inline_fn() == 0) && (actor->active == 0)) && (actor->actionState > 3))
    {
      D_02025FF0.flag = 1;
      sub_0806DE0C();
      D_02025FF0.subPhase = 4;
      if (((u16) (actor->actionState - 4)) <= 5)
      {
        D_02025FF0.subPhase = 1;
      }
      if (((u16) (actor->actionState - 0x0A)) <= 5)
      {
        D_02025FF0.subPhase = 2;
      }
      if (((u16) (actor->actionState - 0x10)) <= 5)
      {
        D_02025FF0.subPhase = 3;
      }
      sub_08003A6C(((void *) actor) + 0x28, 0, D_0866F0DC[(actor->variant * 5) + inline_fn()]);
    }
      if ((actor->actionState == 0x1C) && (actor->active != 0))
    {
      actor->actionState = 0x16;
      actor->actionTimer = 1;
      sub_08003740(((void *) actor) + 0x28, entity);
    }
      break;

  }

}
