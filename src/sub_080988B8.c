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
s32 signOf(s32);
inline s8 toS8(s8 value)
{
  return value;
}

/* Store the object's facing direction byte at obj+0x35: +1 when `coord` lies
 * before the tracked global coordinate (signOf > 0), otherwise -1 (0xFF). */
void sub_080988B8(s32 obj, s32 coord)
{
  s8 *dir;
  if (signOf(coord) > 0)
  {
    dir = obj + 0x35;
    coord = 1;
  }
  else
  {
    dir = obj + 0x35;
    coord = 0xFF;
  }
  *dir = toS8(coord);
}
