extern s32 setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_08014990(s32);
extern void sub_08043320(s32, s32, s32, s32, s32);
extern void sub_080435EC(s32, s32, s32, s32, s32);
extern void sub_080438BC(s32, s32, s16, s16);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Per-object movement state stored at mainObj+0x3C. */
struct ObjState {
    u8 pad_0x00[8];
    s32 x;              /* 0x08: fixed-point world x */
    s32 y;              /* 0x0C: fixed-point world y */
    u8 pad_0x10[0x0C];
    s16 z;              /* 0x1C */
};

/* Frame state for the current action, stored at ObjState+0x34. */
struct ActionAnim {
    u8 flags;           /* 0x00: bit 1 set once the action finishes */
    u8 frame;           /* 0x01: current frame (1 and 3 spawn effects) */
    u8 pad_0x02[2];
    s32 counter;        /* 0x04: 1 on frames that spawn an effect */
};

/* Advance the main object's action (animation 3). On frames 1 and 3 it creates
 * effect objects ahead of or behind the object according to its facing, then
 * when the action finishes it clears the frame counter and calls the action
 * callback from the table at 0x08671BD0. */
void sub_08042E80(u8 *mainObj)
{
  s32 handle = *((s32 *) (mainObj + 0x38));
  s32 *callbackSlot;
  struct ObjState *st = *((struct ObjState **) (mainObj + 0x3C));
  struct ActionAnim *anim = (struct ActionAnim *) ((u8 *) st + 0x34);
  s32 effectY;
  s32 velX;
  s32 velX2;
  s32 baseX;
  s32 velX3;
  u16 facing16;
  s32 facing;
  u8 flags;
  u32 mask;
  setAnimationFrame(handle, (u8 *) anim, 3, 0);
  if ((anim->frame == 1) && (anim->counter == 1))
  {
    facing16 = (u16) sub_08014990(handle);
    if (((s32) (facing16 << 0x10)) > 0)
    {
      baseX = st->x + 0x120000;
      velX = 0x80000;
    }
    else
    {
      baseX = st->x + ((s32) 0xFFEE0000);
      velX = (s32) 0xFFF80000;
    }
    effectY = st->y + ((s32) 0xFFF20000);
    sub_08043320(baseX, effectY, velX, 0, st->z);
    sub_080438BC(baseX, effectY, (s16) facing16, st->z);
  }
  if ((anim->frame == 3) && (anim->counter == 1))
  {
    facing = sub_08014990(handle);
    if (facing > 0)
    {
      velX2 = st->x + 0x80000;
      velX3 = 0x4000;
    }
    else
    {
      velX2 = st->x + ((s32) 0xFFF80000);
      velX3 = (s32) 0xFFFFC000;
    }
    sub_080435EC(velX2, st->y + ((s32) 0xFFF70000), velX3, (s32) 0xFFFF0000, st->z);
  }
  flags = anim->flags;
  mask = 2;
  mask &= flags;
  if (mask != 0)
  {
    *((u8 *) (((((u32) ((s16) (*((s16 *) (mainObj + 0x22))))) * 2) + ((u32) mainObj)) + 0x19)) = 0;
    callbackSlot = &(*((s32 *) 0x08671BD0));
    sub_080C31E8(mainObj + 0x18, mainObj + 0x22, 0, *callbackSlot);
  }
}
