struct SpawnFlags
{
  u8 unused;
  u8 hitFlags;
};
struct GameState
{
  u8 _0[0x18A8];
  u8 frameCounter;
};
struct ScriptObj
{
  u8 _0[2];
  u16 flags;
  u8 _4[0x10];
  u32 stepTable;
  u8 _18[0x0A];
  s16 stepIndex;
  u8 _24[0x14];
  u32 sprite;
  u32 work;
  u8 _40[0x2C];
  u16 flipFlag;
};
struct Attacker
{
  u8 _0[0x14];
  u32 screenX;
  u32 screenY;
  u8 _1C[0xE];
  u8 spriteFlag;
};
struct AttackBody
{
  u16 hitFlags;
  u8 _02[6];
  u32 worldX;
  u32 worldY;
  u32 unused10;
  u32 unused14;
  u8 _18[0x10];
  void *target;
};
extern void playSound(s32);
extern void stepAnimationTrack(s32, void *);
extern void advanceMotion(void *, s32);
extern s32 updateObjectDisplayState(s32, void *);
extern s32 hitTestEntities(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern void _call_via_r1(void *, void *);
extern void _call_via_r3(void *, void *, s32, void *);
extern void *sScriptStepCallbacks;
extern u8 gCameraState[];
extern struct GameState gMainWorkspace;

/* Per-frame update of a scripted attack: clear the target's transient hit
 * flags, handle a hit/death event, dispatch one script command while the
 * attack is live, then place the sprite relative to the camera scroll. */
void updateScriptedAttackObject(struct ScriptObj *script)
{
  struct Attacker *attacker;
  struct AttackBody *attack;
  u8 *attackData34;
  u32 zero;
  struct SpawnFlags *spawnFlags;
  u8 maskedFlags;
  attacker = (struct Attacker *) script->sprite;
  attack = (struct AttackBody *) script->work;
  attackData34 = ((u8 *) attack) + 0x34;
  spawnFlags = (struct SpawnFlags *) attack->target;
  maskedFlags = spawnFlags->hitFlags & 0xFA;
  zero = 0;
  spawnFlags->hitFlags = maskedFlags;
  attack->unused14 = zero;
  attack->unused10 = zero;
  if (hitTestEntities(attack->target) != 0)
  {
    attack->hitFlags |= 1;
  }
  if ((*((u16 *) (((u8 *) attack->target) + 0x14))) & 1)
  {
    attack->hitFlags |= 1;
  }
  if (attack->hitFlags & 1)
  {
    u8 *stepState;
    attack->hitFlags &= 0xFFFE;
    sub_0808DBB4(attack->worldX, attack->worldY, 8);
    playSound(SCRIPT_ATTACK_DEATH_SFX);
    attacker->spriteFlag &= 0xBF;
    script->flipFlag &= 0xFFFB;
    stepState = (u8 *) ((((u32) script->stepIndex) * 2) + ((u32) script));
    stepState[0x1B] = 0;
    {
      void **eventCallbacks = &sScriptStepCallbacks;
      _call_via_r3(((u8 *) script) + 0x18, ((u8 *) script) + 0x22, 0, *eventCallbacks);
    }
  }
  if (updateObjectDisplayState((s32) attacker, attack) != 0)
  {
    goto lab_de;
  }
  script->stepTable = SCRIPT_ATTACK_STEP_TABLE;
  script->stepIndex = script->stepIndex + 1;
  {
    u8 *stepState = (u8 *) ((((u32) script->stepIndex) * 2) + ((u32) script));
    stepState[0x19] = stepState[0x19] + 1;
  }
  {
    s32 stepOffset = script->stepIndex * 2;
    u8 *scriptBase = ((u8 *) script) + 0x18;
    u8 opcode = *(scriptBase + stepOffset);
    void **stepHandlers = *((void **) (&script->stepTable));
    _call_via_r1(script, stepHandlers[opcode]);
  }
  script->stepIndex = script->stepIndex - 1;
  if ((script->flags & 0x8000) != 0)
  {
    goto done;
  }
  stepAnimationTrack((s32) attacker, attackData34);
  advanceMotion(attack, 0);
  lab_de:
  {
    u8 *stepState = (u8 *) ((((u32) script->stepIndex) * 2) + ((u32) script));
    if (stepState[0x1A] != 0)
    {
      struct SpawnFlags *spawnFlags2 = (struct SpawnFlags *) attack->target;
      spawnFlags2->hitFlags |= 5;
    }
  }

  *((u16 *) (((u8 *) attack->target) + 0x14)) = zero;
  {
    u32 coordOffset = 0x1278;
    u8 *coordTable = gCameraState;
    u32 coordX = *((u32 *) ((coordTable + coordOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
    coordX = coordX + 0x8000;
    coordX = coordX & 0xFFFF0000;
    attacker->screenX = attack->worldX - coordX;
  }
  {
    u32 coordOffset = 0x127C;
    u8 *coordTable = gCameraState;
    u32 coordY = *((u32 *) ((coordTable + coordOffset) + ((gMainWorkspace.frameCounter + 1) << 6)));
    coordY = (coordY + 0xFFFF8000) & 0xFFFF0000;
 do { attacker->screenY = attack->worldY - coordY; } while (0);
  }
  done:
  ;

  ;
  ;
}
