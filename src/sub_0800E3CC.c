/* Per-frame update of the DSS card-combination menu: up/down changes the card
 * selected in the active slot (wrapping 1..10), left/right switches the active
 * slot, redraws both card slots and their combination result, and closes the
 * menu on A/B. */
extern void sub_08005E80(s32);                 /* play sound */
extern void sub_0800F4D4(s32, u8, s32);        /* draw one card slot */
extern void sub_0800F584(u8, u8);              /* draw the combination result */
extern void sub_080C31E8(u8 *, u8 *, s32, s32); /* state machine dispatch */
extern u8 D_020278D0[];   /* DSS menu state: 0x40 card A, 0x41 card B,
                             0xF8 active slot, 0x64, 0x48 sub-object */
extern u8 gCameraState[];   /* shared video state (key repeat + pressed keys) */
extern u32 D_08671BD8[];

void sub_0800E3CC(u8 *entity)
{
  s32 changed = 0;
  u8 prevCardA = D_020278D0[0x40];
  u8 prevCardB = D_020278D0[0x41];
  int activeSlot;
  u8 *cardPtr;
  u8 cardValue;
  if (D_020278D0[0xF8] != 0)
  {
    cardPtr = D_020278D0 + 0x40;
  }
  else
  {
    cardPtr = D_020278D0 + 0x41;
  }
  {
    u8 *video = gCameraState;
    u16 dirMask = (*((u16 *) (video + 0x1470))) & 0x30;
    u8 *videoKeep = video;
    if (dirMask != 0x30)
    {
      if ((*((u16 *) (video + 0x1470))) & 0x20)   /* up */
      {
        sub_08005E80(0x139);
        *cardPtr = ((*cardPtr) > 1) ? ((*cardPtr) - 1) : (10);
      }
      if ((*((u16 *) (videoKeep + 0x1470))) & 0x10)   /* down */
      {
        sub_08005E80(0x139);
        *cardPtr = ((*cardPtr) == 10) ? (1) : ((*cardPtr) + 1);
      }
    }
  }
  {
    u8 *video = gCameraState;
    if (((*((u16 *) (video + 0x1470))) & 0xC0) != 0xC0)   /* left/right */
    {
      if ((*((u16 *) (video + 0x1470))) & 0x40)
      {
        if (D_020278D0[0xF8] == 1)
        {
          sub_08005E80(0x140);
          D_020278D0[0xF8] = 0;
        }
      }
      activeSlot = 1;
      {
        u8 *video2 = gCameraState;
        if ((*((u16 *) (video2 + 0x1470))) & 0x80)
        {
          if (D_020278D0[0xF8] == 0)
          {
            sub_08005E80(0x140);
            D_020278D0[0xF8] = activeSlot;
          }
        }
      }
    }
  }
  cardValue = D_020278D0[0x40];
  if (prevCardA != cardValue)
  {
    changed = 1;
    sub_0800F4D4(1, cardValue, 0x200);
  }
  cardValue = D_020278D0[0x41];
  if (prevCardB != cardValue)
  {
    changed = 1;
    sub_0800F4D4(0, cardValue, 0x208);
  }
  if (changed != 0)
  {
    sub_0800F584(D_020278D0[0x41], D_020278D0[0x40]);
  }
  {
    u8 *video = gCameraState;
    if ((*((u16 *) (video + 0x146C))) & 3)   /* A or B */
    {
      sub_08005E80(0x14F);
      D_020278D0[0x64] = 0;
      *((u8 *) ((entity + ((*((s16 *) (entity + 0x22))) * 2)) + 0x17)) = 0;
      {
        u32 *stateTable = D_08671BD8;
        sub_080C31E8(entity + 0x18, entity + 0x22, 0x0E, stateTable[0]);
      }
    }
  }
}
