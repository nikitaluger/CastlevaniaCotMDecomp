struct S_D
{
  u8 _0[0x10];
  u32 f10;
  u32 state14;
  u8 _1[4];
  u32 state1C;
  u8 _2[0x1824];
  u32 state1844;
};
extern struct S_D gMainWorkspace;
void sub_080C31E4(void *, void *, s32);
void stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);

/* Tick of a grounded actor: when the global state (+0x14) is 0x19, raise the
 * sprite's 0x10 flag, set the global mode (+0x1C) to 4 and restart the script;
 * then tick the actor's animation timer and refresh the sprite screen offset
 * from the mover position. */
void sub_08089630(void *arg0) {
  void *mover = *(void **)((u8 *)arg0 + 0x6C);
  void *moverPos = (u8 *)mover + 4;
  void *sprite = *(void **)((u8 *)arg0 + 0x38);
  if (gMainWorkspace.state14 == 0x19) {
    u16 *flagsPtr = (u16 *)((u8 *)sprite + 2);
    u16 oldFlags = *flagsPtr;
    int newFlags = 0x10;
    u8 zero = 0;
    newFlags |= oldFlags;
    *flagsPtr = (u16)newFlags;
    gMainWorkspace.state1C = 4;
    *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = zero;
    {
      s32 *advanceTable = (s32 *)0x08671BB0;
      sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *advanceTable);
    }
  }
  stepDelayTimer((u8 *)mover + 0x20, sprite);
  sub_0806D588(sprite, moverPos);
}
