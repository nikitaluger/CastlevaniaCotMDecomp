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
M2C_UNK setAnimationFrame(s32, s32, s32, s32);
M2C_UNK advanceMotion(void *, s32);
M2C_UNK moveEntityWithCollision(void *, s32);
M2C_UNK sub_08044FD4(s32, void *, void *, void *);
M2C_UNK sub_080C31E4(void *, void *, s32);

/* Launched/thrown actor update: apply gravity or collision, pick fall/land animation, test contact, then clear the state. */
void sub_08044980(void *self)
{
  s32 anim;
  s32 gfx;
  s32 *ptbl;
  void *entity;
  void *state;
  gfx = *((s32 *) (((s8 *) self) + 0x38));
  entity = *((void **) (((s8 *) self) + 0x3C));
  anim = entity + 0x34;
  state = entity + 0x48;
  if ((*((u8 *) (((s8 *) state) + 5))) != 0)
  {
    advanceMotion(entity, 0x2D82);
  }
  else
  {
    moveEntityWithCollision(entity, 0x2D82);
  }
  if (((s32) (*((s32 *) (((s8 *) entity) + 0x14)))) > 0x8000)
  {
    setAnimationFrame(gfx, anim, 0x17, 0);
  }
  sub_08044FD4(1, self, entity, state);
  if (4 & (*((u16 *) (((s8 *) entity) + 2))))
  {
    *((u8 *) (((s8 *) state) + 5)) = 0U;
    setAnimationFrame(gfx, anim, 5, 0);
    *((s8 *) (((s8 *) (((*((s16 *) (((s8 *) self) + 0x22))) * 2) + self)) + 0x19)) = 0;
    ptbl = &(*((s32 *) 0x08671BB0));
    sub_080C31E4(self + 0x18, self + 0x22, *ptbl);
  }
}
