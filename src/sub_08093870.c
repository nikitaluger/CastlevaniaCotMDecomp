extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern void sub_0808E348(s32, s32, s32, s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern u8 D_081007D0[];

/* Periodic entity update: sets the gfx animation from a table, occasionally spawns
 * an effect when the timer is a multiple of four, then counts the timer down and
 * on expiry resets it and advances to the next script step. */
void sub_08093870(u8 *self)
{
  u8 *gfx = *(u8 **)(self + 0x38);
  u8 *body = *(u8 **)(self + 0x3C);
  u8 *state = body + 0x34;
  u8 *pTable = D_081007D0;
  s32 animIdx = *(s32 *)(body + 0x34);
  s32 tableOffset = animIdx * 6;
  s32 spawnTimer;
  s32 *msgPtr;

  pTable += 4;
  *(u16 *)(gfx + 0x28) = *(u16 *)(pTable + tableOffset);

  spawnTimer = *(u16 *)(state + 0xC);
  if ((spawnTimer & 3) == 0) {
    s32 spawnX = *(s32 *)(body + 8) + sub_0800583C(0xE0 << 12);
    s32 spawnY = *(s32 *)(body + 0xC) + sub_0800583C(0x80 << 10);
    s32 speed = sub_08005820(0x80 << 8) + (0x80 << 6);
    sub_0808E348(spawnX, spawnY, 0, speed, 0xC0 << 6, 0, 8);
  }

  {
    s32 timer = *(u16 *)(state + 0xC);
    timer = timer - 1;
    *(u16 *)(state + 0xC) = timer;
    if ((timer << 16) <= 0) {
      u32 stepPos;
      *(u16 *)(state + 0xC) = 4;
      stepPos = *(s16 *)(self + 0x22);
      stepPos <<= 1;
      stepPos += (u32)self;
      *(u8 *)(stepPos + 0x19) = 0;
      msgPtr = (s32 *)0x08671BB0;
      sub_080C31E4(self + 0x18, self + 0x22, *msgPtr);
    }
  }
}
