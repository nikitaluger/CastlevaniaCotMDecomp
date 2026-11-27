#ifndef M2C_DEFINES
#define M2C_DEFINES
#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))
#define M2C_BITWISE(type, expr) ((type)(expr))
#define M2C_ERROR(desc) (0)
#define M2C_CARRY 0
#define M2C_OVERFLOW(a) (0)
#endif
typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
M2C_UNK stepDelayTimer(void *, void *);
M2C_UNK sub_0806D588(void *, void *);
M2C_UNK sub_080C31E0(void *, s32);
inline s8 *inline_fn(void *arg0)
{
  return (s8 *) arg0;
}

/* Advance a physics body: ramp and clamp its acceleration, integrate velocity
 * and position, refresh the countdown and screen-relative position, then
 * destroy the actor once it falls too far below the view. */
void sub_080882EC(void *obj)
{
  s32 accel;
  void *body;
  void *dyn;
  void *owner;
  body = *((void **) (inline_fn(obj) + 0x6C));
  dyn = body + 4;
  owner = *((void **) (inline_fn(obj) + 0x38));
  accel = (*((s32 *) (inline_fn(dyn) + 0xC))) + 0x4000;
  *((s32 *) (inline_fn(dyn) + 0xC)) = accel;
  if (accel > 0x80000)
  {
    *((s32 *) (inline_fn(dyn) + 0xC)) = 0x80000;
  }
  *((s32 *) (inline_fn(body) + 4)) = (s32) ((*((s32 *) (inline_fn(body) + 4))) + (*((s32 *) (inline_fn(dyn) + 8))));
  *((s32 *) (inline_fn(dyn) + 4)) = (s32) ((*((s32 *) (inline_fn(dyn) + 4))) + (*((s32 *) (inline_fn(dyn) + 0xC))));
  stepDelayTimer(body + 0x20, owner);
  sub_0806D588(owner, dyn);
  if (((s32) (*((s32 *) (inline_fn(owner) + 0x18)))) > 0x01000000)
  {
    *((s32 *) (inline_fn((void *) 0x02025FF0) + 0x1C)) = 2;
    sub_080C31E0(obj, *((s32 *) (inline_fn(obj) + 0x24)));
  }
}
