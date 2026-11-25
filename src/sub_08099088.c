/* Update a companion entity: advance its motion, use the script-step flags to set
 * owner animation bits and spawn a one-off effect, mirror state/pan into a global
 * buffer, then examine the current animation frame's command. Command 0x54
 * finalizes the entity (state 3, sound, script restart); otherwise it stays 2. */
s32 sub_08005FC4(s32, s32, s32, s32, s32 *);
s32 sub_08011528(u16 *, void *);
s32 sub_08011898(void *, s32);
s32 sub_08014848(s32, s32, s32, s32, s32, s32);
s32 sub_0809C4E0(s32, s32);
s32 sub_080C31E4(void *, void *, s32);
extern s32 sub_080C0384;
inline s8 *inline_fn(void *arg0) { return (s8 *) arg0; }

void sub_08099088(void *self)
{
  s8 *selfBytes;
  u16 *ownerFlags;
  u8 pan;
  int soundVal;
  void *timers;
  void *ent;
  void *anim;
  s32 posX, posY, cmdId;
  s8 *cmdPtr;
  s32 **cmdTablePtr;
  s32 frameSlot;
  s8 *cmdBase;
  s32 *handlerTable;
  ownerFlags = *((u16 **) (inline_fn(self) + 0x38));
  ent = *((void **) (inline_fn(self) + 0x3C));
  soundVal = 0x3F40;
  anim = ent + 0x34;
  if (1)
  {
    timers = ent + 0x48;
    sub_08011898(ent, 0x2D82);
    selfBytes = inline_fn(self);
    if (!(2 & (*((u8 *) (inline_fn(((*((s16 *) (selfBytes + 0x22))) * 2) + self) + 0x19)))))
    {
      *ownerFlags = (0xFFF & (*ownerFlags)) | 0xE000;
    }
    if (!(3 & (*((u8 *) (inline_fn(((*((s16 *) (inline_fn(self) + 0x22))) * 2) + self) + 0x19)))))
    {
      posX = *((s32 *)(inline_fn(ent)+8));
      posY = (*((s32 *)(inline_fn(ent)+0xC))) + 0xFFE80000;
      sub_08014848(2, 2, posX, posY, 0x300000, 0x180000);
    }
    *((s16 *) (inline_fn((void *) 0x03000830) + 4)) = soundVal;
    pan = *((u8 *) (inline_fn(ent) + 0x6B));
    *((s16 *) (inline_fn((void *) 0x03000830) + 6)) = (s16) (pan | ((0x10 - pan) << 8));
    sub_08011528(ownerFlags, anim);
    cmdTablePtr = *(s32 ***)(inline_fn(anim) + 8);
    frameSlot = *((s16 *) (inline_fn(anim) + 0xE)) + *((u8 *) (inline_fn(anim) + 1));
    cmdBase = (s8 *)*cmdTablePtr;
    cmdPtr = (s8 *)(frameSlot * 4);
    cmdPtr = (s8 *)((s32)cmdPtr + (s32)cmdBase);
    cmdPtr -= 4;
    cmdId = *(u16 *)(cmdPtr + 2);
    if (cmdId == 0x54)
    {
      sub_0809C4E0(*((s32 *) (inline_fn(timers) + 8)), 3);
      sub_08005FC4(0, 0x186, 0x18, 0, &sub_080C0384);
      *inline_fn(inline_fn(((*((s16 *) (inline_fn(self) + 0x22))) * 2) + self) + 0x19) = 0;
      handlerTable = (s32 *)0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
      return;
    }
  }
  sub_0809C4E0(*((s32 *) (inline_fn(timers) + 8)), 2);
}
