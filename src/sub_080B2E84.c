/* Copy an entity's body and view state from a parent object, mirror the
 * parent's layer flag onto the view, and when the current entry marks an end
 * case, stop the child and run the next animation command. */
extern void sub_08005E80(u16);
extern void sub_08011528(void *, void *);
extern void _call_via_r2(void *, void *, s32);
extern s32 gMainObjTimerCallback;
inline s32 *field0C(u8 *arg0)
{
  return (s32 *) (arg0 + 0x0C);
}

struct H2 { u8 pad[2]; u16 f2; };

void sub_080B2E84(void *arg0)
{
  u8 *entity = arg0;
  void *view = *((void **) (entity + 0x38));
  void *body = *((void **) (entity + 0x3C));
  u8 *frameBytePtr;
  u8 *bodyData = ((u8 *) body) + 0x34;
  void *parent = *((void **) (entity + 0x28));
  u8 *parentBody;
  void *parentBodyPtr = *((void **) (((u8 *) parent) + 0x3C));
  u32 zero;
  parentBody = (u8 *) parentBodyPtr;
  sub_08011528(view, bodyData);
  *((s32 *) (((u8 *) body) + 0x08)) = *((s32 *) (parentBody + 0x08));
  *field0C((u8 *) body) = *field0C(parentBody);
  {
    void *p = *((void **) (entity + 0x28));
    void *q = *((void **) (((u8 *) p) + 0x38));
    if (0x10 & *((u16 *) (((u8 *) q) + 0x02)))
    {
      ((struct H2 *)view)->f2 |= 0x10;
    }
    else
    {
      *((u16 *) (((u8 *) view) + 0x02)) = 0xFFEF & *((u16 *) (((u8 *) view) + 0x02));
    }
  }
  frameBytePtr = (u8 *) (((u8 *) bodyData) + 0x01);
  {
    s32 **tablePtr = *((s32 ***) (((u8 *) bodyData) + 0x08));
    s16 *animData = (s16 *) bodyData;
    s32 entryIndex = animData[0x07] + (*frameBytePtr);
    s32 *entries = *tablePtr;
    u8 *entry = (u8 *)((s32)(entryIndex * 4) + (s32)entries) - 4;
    if ((*((u16 *) (entry + 2))) == 8)
    {
      void *target = *((void **) (((u8 *) body) + 0x28));
      zero = 0;
      *((u8 *) (((u8 *) target) + 0x01)) = 1;
      sub_08005E80(0x17F);
      {
        s16 *animIndex = (s16 *) entity;
        *((u8 *) ((entity + (animIndex[0x11] * 2)) + 0x19)) = zero;
      }
      {
        s32 *animScript = &gMainObjTimerCallback;
        _call_via_r2(entity + 0x18, entity + 0x22, *animScript);
      }
    }
  }
}
