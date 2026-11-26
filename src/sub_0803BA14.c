extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014990(void *);
extern void sub_0808E05C(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 gMainObjTimerCallback[];
void sub_0803BA14(u8 *self)
{
  u8 *actor = *((u8 **) (self + 0x38));
  u8 *enemy = *((u8 **) (self + 0x3C));
  u8 *litBytes;
  u8 *enemyData = enemy + 0x34;
  u8 stateByte;
  s32 *litPtr;
  setAnimationFrame(actor, enemyData, 5, 0);
  {
    u32 slotAddr = *((s16 *) (self + 0x22));
    slotAddr <<= 1;
    slotAddr += (u32) self;
    stateByte = *((u8 *) (slotAddr + 0x19));
  }
  if ((stateByte & 7) == 1)
  {
    sub_0808E05C(*((s32 *) (enemy + 0x08)), *((s32 *) (enemy + 0x0C)), 1, 8);
  }
  if (sub_08014990(actor) < 0)
  {
    s32 newVel = (*((s32 *) (enemy + 0x10))) + (0xC0 << 5);
    *((s32 *) (enemy + 0x10)) = newVel;
    if (newVel >= 0)
    {
      *((s32 *) (enemy + 0x10)) = 0;
      {
        u32 slotAddr = *((s16 *) (self + 0x22));
        slotAddr <<= 1;
        slotAddr += (u32) self;
        *((u8 *) (slotAddr + 0x19)) = 0;
      }
      litPtr = (s32 *) gMainObjTimerCallback;
      sub_080C31E4(self + 0x18, self + 0x22, *litPtr);
    }
  }
  else
  {
    s32 newVel = (*((s32 *) (enemy + 0x10))) + ((s32) 0xFFFFE800);
    *((s32 *) (enemy + 0x10)) = newVel;
    if (newVel <= 0)
    {
      *((s32 *) (enemy + 0x10)) = 0;
      {
        u32 slotAddr = *((s16 *) (self + 0x22));
        slotAddr <<= 1;
        slotAddr += (u32) self;
        *((u8 *) (slotAddr + 0x19)) = 0;
      }
      litBytes = gMainObjTimerCallback;
      sub_080C31E4(self + 0x18, self + 0x22, *((s32 *) litBytes));
    }
  }
}
