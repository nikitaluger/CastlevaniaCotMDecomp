/* Applies a brief sprite tilt/scroll effect driven by the entity's counter,
   then restores the sprite and re-dispatches the entity once the counter hits
   0x20. */
extern void initCrossfadeGfxState(void);
extern void sub_0809E32C(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);
struct GfxFlags { u8 _pad[2]; u16 flags; };
void sub_0809D344(u8 *entity)
{
  u8 *gfx;
  u8 *work;
  u32 tilt;
  s32 zero;
  gfx = *((u8 **) (entity + 0x38));
  work = *((u8 **) (entity + 0x3C));
  sub_0809E32C(gfx, work + 0x34, work, work + 0x48);
  ((struct GfxFlags *)gfx)->flags |= 0x400;
  {
    u8 *io = (u8 *) 0x03000830;
    u16 mode = 0xFD << 6;
    *((u16 *) (io + 4)) = mode;
    tilt = (*((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19))) >> 1;
    *((u16 *) (io + 6)) = tilt | (((0x10 - tilt) << 5) << 3);
  }
  *((u16 *) (gfx + 4)) = (*((u16 *) (gfx + 4))) - 0x40;
  *((u16 *) (gfx + 6)) = (*((u16 *) (gfx + 6))) + 4;
  zero = 0;
  if ((*((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19))) == 0x20)
  {
    do
    {
      initCrossfadeGfxState();
      {
        u16 size = 0x100;
        *((u16 *) (gfx + 4)) = size;
        *((u16 *) (6 + gfx)) = size;
      }
      ((struct GfxFlags *)gfx)->flags &= 0xFBFF;
      *((u8 *) ((*((u8 **) (work + 0x28))) + 1)) = 5;
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x19)) = zero;
      {
        s32 *callback = (s32 *) 0x08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *callback);
      }
    }
    while (0);
  }
}
