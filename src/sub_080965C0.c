s32 scaleByRandom(s32);
s32 randomSignedOffset(s32);
void sub_08091E3C(s32, s32, s32, s32, s32, s32);
s16 divInt32(s16, s32);
s16 sub_080C36E4(s16, s32);
void sub_080C31E4(void *, void *, void *);
extern u8 D_08100B1E[];
extern void *gMainObjTimerCallbacks;

/* Periodic entity update: occasionally spawns an effect/projectile, counts down
 * a timer, and on expiry resets it and advances to the next script step. */
void sub_080965C0(void *self)
{
  u8 *gfx = *(u8 **)(self + 0x38);
  u8 *body = *(u8 **)(self + 0x3C);
  u8 *state = body + 0x48;
  u8 *pTable = D_08100B1E;
  s32 animIdx = *(s32 *)state;
  s32 tableOffset = animIdx * 4;
  pTable += 2;
  *(u16 *)(gfx + 0x28) = *(u16 *)(pTable + tableOffset);
  if (sub_080C36E4(*(s16 *)(state + 0x14), 6) == 0)
  {
    s32 spawnX = (*(s32 *)(body + 8)) + randomSignedOffset(0xE0000);
    s32 spawnY = (*(s32 *)(body + 0xC)) + 0x30000;
    s32 speed = scaleByRandom(0x8000) + 0x2000;
    s16 phase = divInt32(*(s16 *)(state + 0x14), 6);
    phase = sub_080C36E4(phase, 3);
    sub_08091E3C(spawnX, spawnY, 0, speed, 0x16C1, phase);
  }
  (*(s16 *)(state + 0x14))--;
  if ((*(s16 *)(state + 0x14)) < 0)
  {
    *(s16 *)(state + 0x14) = 3;
    *((u8 *)self + ((*(s16 *)(self + 0x22)) * 2) + 0x19) = 0;
    {
      void **pBB0 = &gMainObjTimerCallbacks;
      sub_080C31E4(self + 0x18, self + 0x22, *pBB0);
    }
  }
}
