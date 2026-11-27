s32 updateObjectDisplayState(void *, void *);
void sub_080B7550(u8, s32, s32, s32, s32);
void sub_080C31E0(void *, void *);

/* gfx/effect state at 0x03000830: u16 colors at +4/+6 */
struct EffectGfxState { u8 _0[4]; u16 colorA; u16 colorB; };

struct S_080B6170
{
  u8 _0x00[0x14];
  u32 cmdTable;
  u8 _0x18[0x0A];
  s16 stepIndex;
  u8 _0x24[0x04];
  u32 coordObj;
  u8 _0x2C[0x0C];
  u32 sprite;
  u32 work;
  u8 _0x40[0x0C];
  u8 active;
  u8 _0x4D[0x0F];
  u32 coordParam0;
  u8 _0x60[0x0C];
  u32 coordParam1;
};

/* Actor update: apply the display state; if the frame was not handled, peek at
 * the next script step (bump its flag and dispatch its command handler), then
 * optionally set effect colors; finally run the coordinate transform using the
 * target object's x/y. */
void sub_080B6170(struct S_080B6170 *self)
{
  int dataOff;
  int indexOff;
  void *spriteAttrs;
  void *workState;
  void *coordObjPtr;
  u8 *objWork;
  u8 *flagPtr;
  s32 srcX;
  s32 srcY;
  u8 flag;

  spriteAttrs = (void *)self->sprite;
  workState = (void *)self->work;
  coordObjPtr = (void *)self->coordObj;
  objWork = *(u8 **)((u8 *)coordObjPtr + 0x3C);
  flagPtr = (u8 *)self + 0x4C;

  if (*flagPtr != 0) {
    struct EffectGfxState *fx = (struct EffectGfxState *)0x03000830;
    fx->colorA = 0x3F44;
    fx->colorB = 0xA06;
  }

  if (updateObjectDisplayState(spriteAttrs, workState) == 0) {
    self->cmdTable = 0x08670454;
    self->stepIndex += 1;
    *((u8 *)(((u8 *)self) + (self->stepIndex * 2) + 0x19)) += 1;
    dataOff = 0x18;
    indexOff = self->stepIndex * 2;
    sub_080C31E0(self, *((void **)((((u32)(*((u8 *)(((u8 *)self) + dataOff + indexOff)))) * 4) + self->cmdTable)));
    self->stepIndex -= 1;
  }

  srcX = *(s32 *)(objWork + 8);
  srcY = *(s32 *)(objWork + 0xC) + (s32)0xFFF00000;
  flag = *flagPtr;
  sub_080B7550(flag, srcX, srcY, self->coordParam0, self->coordParam1);
}
