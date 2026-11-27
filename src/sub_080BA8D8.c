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
M2C_UNK startScriptOnce(void *, s32, s32);
M2C_UNK setFacingDirection(void *, s32);
M2C_UNK sub_080BB940(void *, void *);
M2C_UNK sub_080C31E4(void *, void *, s32);
/* Updates a linked entity's state/facing, clears a state field, and (when a flag
 * exceeds 0x10 and the entity is idle) applies a type change and fires a callback. */
void sub_080BA8D8(void *obj)
{
  u8 entityType;
  void *config;
  void *entity;
  void *state;
  s32 *callbackEntry;
  config = *((void **) (((s8 *) obj) + 0x3C));
  state = config + 0x48;
  entity = *((void **) (((s8 *) obj) + 0x4C));
  sub_080BB940(config, entity);
  if ((*((s32 *) (((s8 *) state) + 0x64))) != 0)
  {
    if (1)
    {
    }
    setFacingDirection(entity, *((s32 *) (((s8 *) config) + 8)));
    if (1)
    {
    }
  }
  *((s32 *) (((s8 *) state) + 0x4C)) = 0;
  if (((u32) (*((u8 *) (((s8 *) (((*((s16 *) (((s8 *) obj) + 0x22))) * 2) + obj)) + 0x19)))) > 0x10U)
  {
    entityType = *((u8 *) (((s8 *) entity) + 0x25));
    if (entityType == 0)
    {
      startScriptOnce(entity, 4, 0);
      *((u8 *) (((s8 *) (((*((s16 *) (((s8 *) obj) + 0x22))) * 2) + obj)) + 0x19)) = entityType;
      callbackEntry = (s32 *) 0x08671BB0;
      sub_080C31E4(obj + 0x18, obj + 0x22, *callbackEntry);
    }
  }
}
