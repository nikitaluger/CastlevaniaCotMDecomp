/* Per-frame update of the pause-menu status/item panel: moves the category
 * cursor on left/right, redraws the panel when it changes, and on A applies the
 * selected item (loading its graphics and spawning its sub-object) or on B
 * closes the menu. */
extern u8 D_020278D0[];   /* menu state: 0x69 toggle, 0x6A category cursor,
                             0x6B/0x73/0xF3 per-category item tables, 0x48 sub-object */
extern u8 D_02025368[];   /* game/player data */
extern u8 D_02021E90[];   /* shared video state (key repeat + pressed keys) */
extern u32 D_08671BD8;
extern u32 D_08671BB0;
void sub_08005E80(u32);                    /* play sound */
void sub_0800F1D8(u32, u32);               /* draw category */
void sub_0800F3C8(u32, u32);               /* draw category footer */
void sub_0800EF3C(u32);                    /* load item graphics */
void sub_0800EDAC(u32);                    /* redraw stat values */
void sub_0806D930(void *);                 /* reset panel buffer */
void *sub_08001480(void *, u32);           /* spawn sub-object */
void sub_080C2E68(void *, void *, u32);    /* memcpy */
void sub_080C31E8(void *, void *, u32, u32); /* state machine dispatch */
void sub_080C31E4(void *, void *, u32);    /* indirect call */

/* The two AND helpers keep the mask in the destination register (see and-result wall). */
static inline u32 and80(u16 v)
{
  u32 m = 0x80;
  m &= v;
  return m;
}
static inline u32 and1(u16 v)
{
  u32 m = 1;
  m &= v;
  return m;
}

void sub_0800D6BC(u8 *entity)
{
  u8 *playerData = D_02025368;
  int prevCategory = (s8) D_020278D0[0x6A];
  {
    u8 *video = D_02021E90;
    u16 *repeatKeys = (u16 *) (video + 0x1470);
    u16 dirMask = (*repeatKeys) & 0xC0;
    if (dirMask != 0xC0)
    {
      u16 heldKeys;
      if (dirMask != 0)
      {
        sub_08005E80(0xA7 << 1);
      }
      heldKeys = *repeatKeys;
      if (0x40 & heldKeys)
      {
        D_020278D0[0x6A] = D_020278D0[0x6A] - 1;
      }
      if (and80(heldKeys))
      {
        D_020278D0[0x6A] = D_020278D0[0x6A] + 1;
      }
      if (((s8) D_020278D0[0x6A]) < 0)
      {
        D_020278D0[0x6A] = 3;
      }
      if (((s8) D_020278D0[0x6A]) > 3)
      {
        D_020278D0[0x6A] = 0;
      }
    }
  }
  if (prevCategory != ((s8) D_020278D0[0x6A]))
  {
    D_020278D0[0x69] = (D_020278D0[0x69] + 1) & 1;
    sub_0800F1D8(D_020278D0[0x6A], D_020278D0[0x69]);
    sub_0800F3C8(D_020278D0[0x69], 0);
  }
  {
    u8 *video = D_02021E90;
    u16 keys = *((u16 *) (video + 0x146C));
    u16 cancelMask = keys & 2;
    if (cancelMask != 0)
    {
      sub_08005E80(0x14F);
      D_020278D0[0x64] = 0;
      entity[((*((s16 *) (entity + 0x22))) * 2) + 0x17] = 0;
      {
        u32 *stateTable = &D_08671BD8;
        sub_080C31E8(entity + 0x18, entity + 0x22, 0x0E, stateTable[0]);
      }
      return;
    }
    if (and1(keys) == 0)
    {
      return;
    }
    if ((*((u8 *) ((D_020278D0 + 0xF3) + ((s8) D_020278D0[0x6A])))) == 0)
    {
      return;
    }
    sub_08005E80(0x13B);
    sub_080C2E68(D_020278D0, playerData + 0x2C4, 0x48);
    sub_0806D930(D_020278D0);
    sub_0800EDAC(0);
    sub_0800F1D8(D_020278D0[0x6A], (D_020278D0[0x69] + 1) & 1);
    {
      void *subObject = sub_08001480(entity, 0x1B);
      *((void **) (D_020278D0 + 0x48)) = subObject;
      *((u8 *) (((u8 *) subObject) + 0x3C)) = 2;
    }
    {
      s32 category = (s8) D_020278D0[0x6A];
      s32 itemOffset = (s8) (*((u8 *) ((D_020278D0 + 0x6B) + category)));
      itemOffset += category * 32;
      sub_0800EF3C(*((u8 *) ((D_020278D0 + 0x73) + itemOffset)));
    }
    entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] = (u8) cancelMask;
    {
      u32 *dispatchTable = &D_08671BB0;
      sub_080C31E4(entity + 0x18, entity + 0x22, dispatchTable[0]);
    }
  }
}
