extern u8 D_020278D0[];
extern u8 gGameStatus[];
extern u8 D_0863E89C[];
void _call_via_r1(void *, void *);
void sub_0806DD94(void);
void sub_080C2E68(void *, void *, u32);
void sub_0806D930(void *);
void *sub_08001480(s32, s32);

/* Dispatch the handler at object+0x24 for each of the five tracked objects. */
void sub_0800D320(void) {
    u32 i = 0;
    u8 *state = D_020278D0;
    void **objPtr = (void **)(state + 0x48);
    void *obj;
    do {
        obj = *objPtr;
        if (obj != 0)
            _call_via_r1(obj, *(void **)((u8 *)obj + 0x24));
        objPtr++;
        i++;
    } while (i <= 4);
}

/* Dispatch the first two tracked objects, start a screen transition if the
 * scene id changed, then save a 0x48-byte snapshot of the state. */
void sub_0800E328(void) {
    u32 i = 0;
    u8 *workspace = gGameStatus;
    u8 *state = D_020278D0;
    void **objPtr = (void **)(state + 0x48);
    void *obj;
    do {
        obj = *objPtr;
        if (obj != 0)
            _call_via_r1(obj, *(void **)((u8 *)obj + 0x24));
        objPtr++;
        i++;
    } while (i <= 1);
    if (*(u16 *)(state + 0x40) != *(u16 *)(workspace + 0x304))
        sub_0806DD94();
    sub_080C2E68(workspace + 0x2C4, state, 0x48);
    sub_0806D930(workspace + 0x2C4);
}

inline s8 *asBytePtr(void *arg0)
{
  return (s8 *) arg0;
}

inline u8 firstByte(s8 *arg0)
{
  return *((u8 *) arg0);
}

/* Reposition this actor's sprite for the linked object: set (state 2 or 4) or
 * clear the sprite's X-flip bit 0x40, install gfx descriptor 0x0863E89C, and
 * place the sprite at X = linked[0x58] (signed) * 12 pixels, Y = 0. */
void sub_0800C2C8(void *arg0)
{
  u8 *attr;
  s32 value;
  s8 linkedState;
  void *sprite;
  sprite = *((void **) (((s8 *) arg0) + 0x38));
  linkedState = (s8) firstByte(((s8 *) (*((void **) (asBytePtr(arg0) + 0x28)))) + 0x4C);
  if ((linkedState == 2) || (linkedState == 4))
  {
    attr = (u8 *)((s8 *)sprite + 0x2A);
    value = 0x40 | *attr;
    *attr = value;
  }
  else
  {
    attr = (u8 *)((s8 *)sprite + 0x2A);
    value = 0xBF & *attr;
    *attr = value;
  }
  *((s32 *) (((s8 *) sprite) + 0x24)) = 0x0863E89C;
  *((s32 *) (asBytePtr(sprite) + 0x14)) = (s32) ((*asBytePtr(asBytePtr(*((void **) (asBytePtr(arg0) + 0x28))) + 0x58)) * 0xC0000);
  *((s32 *) (((s8 *) sprite) + 0x18)) = 0;
}

/* Allocate four tracked objects of kind 0x1B, tagging them 8 with a 0..3 slot,
 * then allocate one more tagged 7 as the last tracked object. */
void sub_0800E8B0(s32 kind) {
    s32 i = 0;
    u8 *state = D_020278D0;
    void **objPtr = (void **)(state + 0x48);
    void *newObj;
    void *cur;
    void *lastObj;
    do {
        newObj = sub_08001480(kind, 0x1B);
        *objPtr = newObj;
        *(u8 *)((u8 *)newObj + 0x3C) = 8;
        cur = *objPtr++;
        *(u8 *)((u8 *)cur + 0x44) = (u8)i;
        i++;
    } while (i <= 3);
    lastObj = sub_08001480(kind, 0x1B);
    *(void **)(state + 0x58) = lastObj;
    *(u8 *)((u8 *)*objPtr + 0x3C) = 7;
}
