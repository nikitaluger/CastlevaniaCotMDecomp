struct SpawnFlags
{
  u8 f0;
  u8 f1;
};
struct GameState
{
  u8 _0[0x18A8];
  u8 roomIndex18A8;
};
struct ScriptObj
{
  u8 _0[2];
  u16 f02;
  u8 _4[0x10];
  u32 f14;
  u8 _18[0x0A];
  s16 f22;
  u8 _24[0x14];
  u32 f38;
  u32 f3C;
  u8 _40[0x2C];
  u16 f6C;
};
struct Attacker
{
  u8 _0[0x14];
  u32 f14;
  u32 f18;
  u8 _1C[0xE];
  u8 f2A;
};
struct AttackBody
{
  u16 f00;
  u8 _02[6];
  u32 f08;
  u32 f0C;
  u32 f10;
  u32 f14;
  u8 _18[0x10];
  void *f28;
};
extern void sub_08005E80(s32);
extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(s32, void *);
extern s32 sub_08016238(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BDC;
extern u8 gCameraState[];
extern struct GameState gMainWorkspace;

/* Updates a scripted attack/hit entity: clears transient flags, handles hit and
 * lifetime results, advances the script when the attack is still live, then
 * re-anchors the attacker to the current room's coordinate table. */
void sub_080303D8(struct ScriptObj *script)
{
  struct Attacker *attacker;
  struct AttackBody *attack;
  u8 *attackData34;
  u32 zero;
  struct SpawnFlags *spawnFlags;
  u8 maskedFlags;
  attacker = (struct Attacker *) script->f38;
  attack = (struct AttackBody *) script->f3C;
  attackData34 = ((u8 *) attack) + 0x34;
  spawnFlags = (struct SpawnFlags *) attack->f28;
  maskedFlags = spawnFlags->f1 & 0xFA;
  zero = 0;
  spawnFlags->f1 = maskedFlags;
  attack->f14 = zero;
  attack->f10 = zero;
  if (sub_08016238(attack->f28) != 0)
  {
    attack->f00 |= 1;
  }
  if ((*((u16 *) (((u8 *) attack->f28) + 0x14))) & 1)
  {
    attack->f00 |= 1;
  }
  if (attack->f00 & 1)
  {
    u8 *scriptState;
    attack->f00 &= 0xFFFE;
    sub_0808DBB4(attack->f08, attack->f0C, 8);
    sub_08005E80(0x189);
    attacker->f2A &= 0xBF;
    script->f6C &= 0xFFFB;
    scriptState = (u8 *) ((((u32) script->f22) * 2) + ((u32) script));
    scriptState[0x1B] = 0;
    {
      void **cmdTableAddr = &D_08671BDC;
      sub_080C31E8(((u8 *) script) + 0x18, ((u8 *) script) + 0x22, 0, *cmdTableAddr);
    }
  }
  if (sub_08013B5C((s32) attacker, attack) != 0)
  {
    goto lab_de;
  }
  script->f14 = (u32) 0x0866DC30;
  script->f22 = script->f22 + 1;
  {
    u8 *scriptState = (u8 *) ((((u32) script->f22) * 2) + ((u32) script));
    scriptState[0x19] = scriptState[0x19] + 1;
  }
  {
    s32 scriptIndex = script->f22 * 2;
    u8 *scriptPc = ((u8 *) script) + 0x18;
    u8 opcode = *(scriptPc + scriptIndex);
    void **cmdTable = *((void **) (&script->f14));
    sub_080C31E0(script, cmdTable[opcode]);
  }
  script->f22 = script->f22 - 1;
  if ((script->f02 & 0x8000) != 0)
  {
    goto done;
  }
  sub_080113A8((s32) attacker, attackData34);
  sub_0801165C(attack, 0);
  lab_de:
  {
    u8 *scriptState = (u8 *) ((((u32) script->f22) * 2) + ((u32) script));
    if (scriptState[0x1A] != 0)
    {
      struct SpawnFlags *spawnFlags2 = (struct SpawnFlags *) attack->f28;
      spawnFlags2->f1 |= 5;
    }
  }

  *((u16 *) (((u8 *) attack->f28) + 0x14)) = zero;
  {
    u32 coordOffset = 0x1278;
    u8 *coordTable = gCameraState;
    u32 coordX = *((u32 *) ((coordTable + coordOffset) + ((gMainWorkspace.roomIndex18A8 + 1) << 6)));
    coordX = coordX + 0x8000;
    coordX = coordX & 0xFFFF0000;
    attacker->f14 = attack->f08 - coordX;
  }
  {
    u32 coordOffset = 0x127C;
    u8 *coordTable = gCameraState;
    u32 coordY = *((u32 *) ((coordTable + coordOffset) + ((gMainWorkspace.roomIndex18A8 + 1) << 6)));
    coordY = (coordY + 0xFFFF8000) & 0xFFFF0000;
 do { attacker->f18 = attack->f0C - coordY; } while (0);
  }
  done:
  ;

  ;
  ;
}
