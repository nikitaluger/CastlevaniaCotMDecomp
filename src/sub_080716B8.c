s32 sub_0806D35C(void *, void *, void *);
void sub_0806D2F8(void *, void *);
void sub_0806D588(void *, void *);
void sub_0806E114(void *, s32, s32, s32);
void sub_080722E0(void *, u32);
void sub_08072334(void *, s32, s32, void *);
void sub_08003740(void *, void *);
void sub_080C31E4(void *, void *, void *);
void sub_080C31E0(void *, void *);
extern void *gMainObjTimerCallback;

struct GameState {
    u8 _0[0x10];
    u32 field10;
    u8 _1[0x14ED - 0x14];
    u8 field14ED;
    u8 _1b[0x14FC - 0x14EE];
    u32 field14FC;
    u8 _2[0x173A - 0x1500];
    u8 field173A;
};
extern struct GameState gMainWorkspace;

/* Updates a child entity: applies camera/scroll adjustment, advances its
 * position and state timer, changes animation state on a mismatch, then
 * spawns an effect or retires the entity depending on global game flags. */
void sub_080716B8(void *entity)
{
  u8 *self = (u8 *) entity;
  u8 *parent = *((u8 **) (self + 0x6C));
  u8 *body = parent + 4;
  void *status = *((void **) (self + 0x38));
  s32 check;
  u8 *stateObj;
  s32 remaining;
  s32 tmp;
  s32 tmp2;
  s32 delta;
  check = sub_0806D35C(self, status, body);
  if (check != 0)
  {
    goto done;
  }
  stateObj = *((u8 **) (body + 0x40));
  if ((*((u8 *) (stateObj + 1))) != (*((u8 *) (parent + 0x48))))
  {
    tmp = 2;
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = check;
    {
      void **animFn = &gMainObjTimerCallback;
      u8 *slots = self + 0x18;
      sub_080C31E4(slots, self + 0x22, *animFn);
      {
        u8 *timer = (u8 *) ((*((s16 *) (self + 0x22))) * tmp);
        u8 *statePtr = slots;
        u8 stateIndex;
        void *nextFn;
        timer += (u32) self;
        timer[0x19]++;
        statePtr += (*((s16 *) (self + 0x22))) * 2;
        stateIndex = *statePtr;
        nextFn = ((void **) (*((void **) (self + 0x14))))[stateIndex];
        sub_080C31E0(self, nextFn);
      }
    }
    return;
  }
  remaining = (*((s32 *) (body + 0x24))) - 1;
  *((s32 *) (body + 0x24)) = remaining;
  if (remaining == 0)
  {
    *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = remaining;
    {
      void **animFn = &gMainObjTimerCallback;
      u8 *slots = self + 0x18;
      sub_080C31E4(slots, self + 0x22, *animFn);
      {
        u8 *timer = (u8 *) ((*((s16 *) (self + 0x22))) * 2);
        u8 *statePtr = slots;
        u8 stateIndex;
        void *nextFn;
        timer += (u32) self;
        timer[0x19]++;
        statePtr += (*((s16 *) (self + 0x22))) * 2;
        stateIndex = *statePtr;
        nextFn = ((void **) (*((void **) (self + 0x14))))[stateIndex];
        sub_080C31E0(self, nextFn);
      }
    }
    return;
  }
  sub_08072334(body, *((s32 *) (stateObj + 0x0C)), *((s32 *) (stateObj + 0x10)), parent + 0x20);
  sub_080722E0(body, *((u8 *) (parent + 0x24)));
  tmp = (*((s32 *) (body + 0x1C))) >> 8;
  delta = tmp * (*((s32 *) (body + 0x08)));
  if (delta < 0)
  {
    delta += 0xFF;
  }
  delta >>= 8;
  *((s32 *) (parent + 0x04)) += delta;
  tmp2 = (*((s32 *) (body + 0x1C))) >> 8;
  delta = tmp2 * (*((s32 *) (body + 0x0C)));
  if (delta < 0)
  {
    delta += 0xFF;
  }
  delta >>= 8;
  *((s32 *) (body + 0x04)) += delta;
  sub_0806D588(status, body);
  sub_08003740(parent + 0x30, status);
  if ((*((u16 *) ((*((u8 **) (body + 0x3C))) + 0x14))) & 1)
  {
    sub_0806E114(*((void **) (self + 0x28)), 8, *((s32 *) (parent + 0x04)), *((s32 *) (body + 0x04)));
    goto via;
  }
  if (gMainWorkspace.field14FC != 0)
  {
    goto via;
  }
  if (gMainWorkspace.field173A == 0x1C)
  {
    goto via;
  }
  if (gMainWorkspace.field14ED != 0)
  {
    goto d2f8;
  }
  if (gMainWorkspace.field10 == 0)
  {
    goto d2f8;
  }
  via:
  sub_080C31E0(self, *((void **) (self + 0x24)));

  return;
  d2f8:
  sub_0806D2F8(self, status);

  return;
  done:
  return;
}
