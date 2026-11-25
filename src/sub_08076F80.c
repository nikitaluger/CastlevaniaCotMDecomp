s32 sub_08003740(void *, s32);
s32 sub_0806D2F8(void *, void *);
s32 sub_0806D518();
void sub_0806D588(void *, void *);
void sub_08084428(void *, s16, s16);
extern void _call_via_r1(void *, s32);
struct S_02025FF0
{
  u8 _0[0x10];
  u32 f10;
  u8 _1[0x14ED - 0x14];
  u8 f14ED;
  u8 _2[0x173A - 0x14EE];
  u8 f173A;
  u8 _3[0x18C2 - 0x173B];
  u16 gfxWord;
};
extern struct S_02025FF0 D_02025FF0;

/* Script step: copies state and position from the object at self+0x6C into the
 * sprite, updates its tiles, then either bounds-checks the sprite or fires the
 * step callback, depending on global state flags. */
void sub_08076F80(void *arg0)
{
  u8 *self = (u8 *) arg0;
  u32 sourceObj;
  u8 *position;
  u8 *sprite;
  u8 *selfCopy;
  struct S_02025FF0 *state;
  sourceObj = *((u32 *) (self + 0x6C));
  position = (u8 *) (sourceObj + 4);
  sprite = *((u8 **) (self + 0x38));
  if (sub_0806D518(self, sprite, position) == 0)
  {
    state = &D_02025FF0;
    {
      u16 word = D_02025FF0.gfxWord;
      *((u16 *) sprite) = word;
    }
    if (sub_08003740((void *) (sourceObj + 0x20), (s32) sprite) == 0)
    {
      goto fee;
    }
    sub_08084428(position, (s16) (0x19A + (*((u16 *) (position + 0x20)))), 0);
    sub_0806D588(sprite, position);
    if (state->f173A == 0x1C)
    {
      goto fee;
    }
 do { if (state->f14ED != 0) { goto do802; } if (state->f10 == 0) { goto do802; } fee: _call_via_r1(selfCopy = self, *((s32 *) (self + 0x24))); return; do802: sub_0806D2F8(self, sprite); return; } while (0);
  }
}
