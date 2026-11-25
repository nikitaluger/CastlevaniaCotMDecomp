typedef s32 M2C_UNK;
typedef s8 M2C_UNK8;
typedef s16 M2C_UNK16;
typedef s32 M2C_UNK32;
M2C_UNK sub_080C31E0(void *, s32);
M2C_UNK sub_080C31E4(void *, void *, s32);
inline s8 *inline_fn(void *arg0)
{
  return (s8 *) arg0;
}

/* Oscillate the two counters at +0x3C/+0x4C, clamping them when they run out
 * of range, then publish the pair to a global word. When the primary counter
 * reaches zero, run scripts on the object list at +0x30, clear the current
 * script step's action byte and advance the script. */
void sub_080099BC(void *entity)
{
  s32 otherPlus2;
  s32 count;
  s32 countMinus2;
  s32 countReload;
  s8 *pCount;
  void *node;
  count = *((s32 *) (inline_fn(entity) + 0x3C));
  pCount = inline_fn(entity) + 0x3C;
  if ((count != 0) && (((countMinus2 = count - 2, *((s32 *) pCount) = countMinus2, otherPlus2 = (*((s32 *) (inline_fn(entity) + 0x4C))) + 2, *((s32 *) (((s8 *) entity) + 0x4C)) = otherPlus2, countMinus2 < 0)) || (otherPlus2 > 0x10)))
  {
    *((s32 *) (inline_fn(entity) + 0x3C)) = 0;
    *((s32 *) (inline_fn(entity) + 0x4C)) = 0x10;
  }
  countReload = *((s32 *) (((s8 *) entity) + 0x3C));
  *((s16 *) (inline_fn((void *) 0x03000830) + 6)) = (s16) (((*((s32 *) (inline_fn(entity) + 0x4C))) << 8) | (*((s32 *) (((s8 *) entity) + 0x3C))));
  if ((*((s32 *) (((s8 *) entity) + 0x3C))) == 0)
  {
    node = *((void **) (inline_fn(entity) + 0x30));
    if (node != NULL)
    {
      do
      {
        sub_080C31E0(node, *((s32 *) (inline_fn(node) + 0x24)));
        node = *((void **) (inline_fn(node) + 0x2C));
      }
      while (node != NULL);
    }
    *((s8 *) (((s8 *) (((*((s16 *) (inline_fn(entity) + 0x22))) * 2) + entity)) + 0x19)) = 0;
    sub_080C31E4(entity + 0x18, entity + 0x22, *((s32 *) 0x08671BB0));
  }
}
