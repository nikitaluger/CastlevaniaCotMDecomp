extern s32 sub_08005910(s32, s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
struct S_02025FF0_174C { u8 _0[0x174C]; u32 x; u32 y; };
extern struct S_02025FF0_174C gMainWorkspace;
extern void *gMainObjTimerCallback;
struct Z { u32 w; u8 b; };

/* Drives the sprite's animation and, when flag 1 is set, computes an angle to a
 * tracked point, fills a spawned-effect parameter block and ends the step. */
void sub_08022620(u8 *obj)
{
  u8 *sprite = *((u8 **) (obj + 0x38));
  u8 *scriptState = *((u8 **) (obj + 0x3C));
  u8 *stateArg = scriptState + 0x34;
  u8 *control = scriptState + 0x48;
  u16 *flags;
  s32 angle;
  s16 stepIndex;
  u8 *params;
  if ((*((s16 *) (control + 2))) == 0)
  {
    setAnimationFrame(sprite, stateArg, 0x0B, 0);
    if ((*((u8 *) stateArg)) & 2)
    {
      *((u16 *) (control + 2)) = 1;
    }
  }
  else
  {
    setAnimationFrame(sprite, stateArg, 0x0E, 1);
  }
  flags = (u16 *) (obj + 0x6C);
  if ((*flags) & 1)
  {
    angle = sub_08005910(((s32) gMainWorkspace.y) - (*((s32 *) (scriptState + 0x0C))), ((s32) gMainWorkspace.x) - (*((s32 *) (scriptState + 8))));
    if ((*flags) & 0x20)
    {
      angle += 0xC0 << 7;
    }
    else if ((*flags) & 0x40)
    {
      angle += 0xFFFFA000;
    }
    else
    {
      goto skip_mask;
    }
    angle &= 0xFFFF;
    skip_mask:
    {
      struct Z z = {0, 0};
      u8 zeroByte;
      params = control + 8;
      *((u32 *) (control + 8)) = 0xA0 << 10;
      *((u32 *) (params + 4)) = angle;
      *((u32 *) (params + 8)) = 0xA0 << 10;
      *((u32 *) (params + 0xC)) = 0xA0 << 10;
      *((u32 *) (params + 0x10)) = z.w;
      *((u32 *) (params + 0x14)) = 0xD0 << 1;
      *((u32 *) (params + 0x1C)) = 0x5A;
      zeroByte = z.b;
      *((u16 *) (params + 0x1A)) = 0x0C;
      stepIndex = *((s16 *) (obj + 0x22));
      *((obj + (stepIndex * 2)) + 0x19) = zeroByte;
    }
    {
      void **fn = &gMainObjTimerCallback;
      sub_080C31E4(obj + 0x18, obj + 0x22, (s32) (*fn));
    }
  }
}
