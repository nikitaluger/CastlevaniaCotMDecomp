extern void stepDelayTimer(void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806D588(void *, void *);
extern void spawnKind2CEntity(void *, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_88774
{
  u8 _0[0x1754];
  s32 minCounter;
};
extern struct S_02025FF0_88774 gMainWorkspace;

/* Apply gravity to a falling object; when it passes the floor limit, spawn an
 * effect, play a sound and raise a script event, then update the sprite. */
void sub_08088774(u8 *self)
{
  u8 *body = *((u8 **) (self + 0x6C));
  u8 *timer = body + 4;
  u8 *sprite = *((u8 **) (self + 0x38));
  u8 *pos = timer;
  s32 newY;
  s32 *scriptEvent;
  u32 stepOffset;

  *((s32 *) (pos + 0xC)) = (*((s32 *) (pos + 0xC))) + (0x80 << 5);
  *((s32 *) (body + 4)) = (*((s32 *) (body + 4))) + (*((s32 *) (pos + 8)));
  newY = (*((s32 *) (pos + 4))) + (*((s32 *) (pos + 0xC)));
 do { *((s32 *) (pos + 4)) = newY; if (newY > 0x7FFFFF) { *((s32 *) (pos + 0xC)) = (s32) 0xFFFF8000; spawnKind2CEntity(self, 0x20000003, *((s32 *) (body + 4)), newY); if (gMainWorkspace.minCounter <= 4) { gMainWorkspace.minCounter = 5; } sub_08005E80(0x1A1); stepOffset = *((s16 *) (self + 0x22)); stepOffset <<= 1; stepOffset += (u32) self; *((u8 *) (stepOffset + 0x19)) = 0; scriptEvent = (s32 *) 0x08671BB0; sub_080C31E4(self + 0x18, self + 0x22, *scriptEvent); } stepDelayTimer(timer + 0x1C, sprite); } while (0);
  sub_0806D588(sprite, pos);
}
