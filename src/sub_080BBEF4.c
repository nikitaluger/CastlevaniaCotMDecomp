extern s32 sub_08013B5C(void *, void *);
extern void sub_08013C8C(void *, void *);
extern void sub_08014668(void *, s8);

extern s32 D_086706B0[];

/* If the display state didn't handle this frame, dispatch the current script
 * step; then, when the work flag is set, offset the entity from its parent and
 * set its facing direction. */
void sub_080BBEF4(void *arg0)
{
  void *work;
  void *entity;
  void *parent;
  void *parentEntity;
  void *parentState;
  s32 stepIdx;

  work = *((void **)((s8 *)arg0 + 0x38));
  entity = *((void **)((s8 *)arg0 + 0x3C));
  parent = *((void **)((s8 *)arg0 + 0x28));
  parentEntity = *((void **)((s8 *)parent + 0x3C));
  parentState = *((void **)((s8 *)parent + 0x4C));
  if (sub_08013B5C(work, entity) == 0)
  {
    s32 byteOffset;
    u8 *scriptData;
    u8 handlerIndex;
    void (**handlers)(void *);

    *((void **)((s8 *)arg0 + 0x14)) = (void *)0x086706B0;
    *((u16 *)((s8 *)arg0 + 0x22)) = *((u16 *)((s8 *)arg0 + 0x22)) + 1;
    stepIdx = (s16)*((s16 *)((s8 *)arg0 + 0x22));
    *((u8 *)((s8 *)arg0 + stepIdx * 2 + 0x19)) = *((u8 *)((s8 *)arg0 + stepIdx * 2 + 0x19)) + 1;
    stepIdx = (s16)*((s16 *)((s8 *)arg0 + 0x22));
    byteOffset = stepIdx * 2;
    scriptData = (u8 *)arg0;
    scriptData = scriptData + 0x18;
    handlerIndex = scriptData[byteOffset];
    handlers = *((void (***)(void *))((s8 *)arg0 + 0x14));
    handlers[handlerIndex](arg0);
    *((u16 *)((s8 *)arg0 + 0x22)) = *((u16 *)((s8 *)arg0 + 0x22)) - 1;
  }
  if (*((u8 *)((s8 *)work + 0x2A)) & 0x40)
  {
    s8 direction = *((s8 *)((s8 *)parentState + 0x35));
    *((s32 *)((s8 *)entity + 0x08)) = *((s32 *)((s8 *)parentEntity + 0x08)) + (direction * 0xE0000);
    *((s32 *)((s8 *)entity + 0x0C)) = *((s32 *)((s8 *)parentEntity + 0x0C)) + 0xFFEB0000;
    sub_08014668(work, *((s8 *)((s8 *)parentState + 0x35)));
  }
  sub_08013C8C(arg0, work);
}
