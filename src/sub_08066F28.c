extern s32 setEntityForm(s32, s32, s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);
inline int addGfxOffset(int value)
{
  return (*((s32 *) value)) + 0x00600000;
}

/* Initialize an object's graphics from a sprite definition, copy a graphics
 * block into VRAM, then run the next step of its behavior script. */
void sub_08066F28(void *arg0)
{
  u8 *obj = (u8 *) arg0;
  s32 *posField;
  s16 pc;
  s32 gfx = *((s32 *) (obj + 0x6C));
  s32 gfxData = gfx + 4;
  s32 sprite = *((s32 *) (obj + 0x38));
  setEntityForm(sprite, gfxData, 0x57);
  *((s32 *) (gfx + 0x108)) = *((s32 *) (gfxData + 4));
  posField = (s32 *) (gfx + 0x110);
  *posField = addGfxOffset(gfxData + 4) - (*((s32 *) (sprite + 0x18)));
  {
    void *allocated = sub_0806D2A0(arg0, 0x34, 0x0A, 0x12);
    if (allocated != 0)
    {
      *((u16 *) (((u8 *) allocated) + 0x7C)) = 0;
    }
  }
  {
    volatile u32 *dma = (volatile u32 *) 0x040000D4;
    dma[0] = 0x084733D4;
    dma[1] = 0x06013000;
    dma[2] = 0x80000200;
    (void) dma[2];
  }
  *((u8 *) (obj + ((*((s16 *) (obj + 0x22))) * 2) + 0x19)) = 0;
  {
    const u32 *table = (const u32 *) 0x08671BB0;
    void *script = obj + 0x18;
    sub_080C31E4(script, obj + 0x22, *table);
    *((u8 *) (obj + ((*((s16 *) (obj + 0x22))) * 2) + 0x19)) += 1;
    gfxData = 2;
    pc = *((s16 *) (obj + 0x22));
    script = ((u8 *) script) + (pc * gfxData);
    sub_080C31E0(arg0, *((u32 *) ((*((u32 *) (obj + 0x14))) + ((*((u8 *) script)) * 4))));
  }
}
