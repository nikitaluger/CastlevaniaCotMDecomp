struct S_02025FF0_BD84
{
  u8 _0[0x174C];
  s32 targetX;
  s32 targetY;
};
extern struct S_02025FF0_BD84 D_02025FF0;
extern s32 sub_08005910(s32, s32);
extern void sub_0801468C(void *, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Point the enemy toward a target position: compute the reversed angle to the
 * target stored in the shared state, save it, set the sprite's facing and
 * speed, then clear the script parameter and dispatch the next command. */
void sub_0805BD84(void *arg0)
{
  void *actor;
  u8 *enemy;
  u8 *enemyState;
  s32 deltaY;
  s32 deltaX;
  s32 angle;
  struct S_02025FF0_BD84 *p;
  actor = *((void **) (((u8 *) arg0) + 0x38));
  enemy = *((u8 **) (((u8 *) arg0) + 0x3C));
  enemyState = enemy + 0x48;
  p = &D_02025FF0;
  deltaY = p->targetY - (*((s32 *) (enemy + 0xC)));
  deltaX = p->targetX - (*((s32 *) (enemy + 8)));
  angle = (sub_08005910(deltaY, deltaX) + (0x80 << 8)) & 0xFFFF;
  *((s32 *) (enemyState + 8)) = angle;
  *((s32 *) (enemyState + 4)) = 0x80 << 0xA;
  sub_0801468C(actor, (angle + (0x80 << 8)) & 0xFFFF);
  *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) = 0;
  {
    s32 *lit = (s32 *) 0x08671BB0;
    u8 *base18 = ((u8 *) arg0) + 0x18;
 do { sub_080C31E4(base18, ((u8 *) arg0) + 0x22, *lit); *((u8 *) ((((u8 *) arg0) + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2)) + 0x19)) += 1; base18 = base18 + ((*((s16 *) (((u8 *) arg0) + 0x22))) * 2); } while (0);
    sub_080C31E0(arg0, *((void **) ((*((u32 *) (((u8 *) arg0) + 0x14))) + ((*((u8 *) base18)) * 4))));
  }
}
