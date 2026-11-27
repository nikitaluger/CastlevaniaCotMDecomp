/* Per-frame update of the pause-menu status/item panel: move the category
 * cursor on left/right, redraw the panel when it changes, then on A apply the
 * highlighted item (snapshot player stats, load its graphics and spawn its
 * preview object) or on B close the menu. */
extern u8 gMenuState[];        /* shared menu work buffer; see the MENU_* offsets */
extern u8 gGameStatus[];       /* game/player data */
extern u8 gCameraState[];      /* shared video/input state */
extern u32 gMenuScriptCallback;
extern u32 gScriptStepCallbackTable;
void playSound(u32);                       /* play sound */
void sub_0800F1D8(u32, u32);               /* draw the category's item list */
void sub_0800F3C8(u32, u32);               /* set up the status-screen background */
void sub_0800EF3C(u32);                    /* load the selected item's graphics */
void sub_0800EDAC(u32);                    /* redraw the stat values */
void sub_0806D930(void *);                 /* recompute the panel's stat values */
void *createChildObject(void *, u32);           /* allocate and link a child object */
void sub_080C2E68(void *, void *, u32);    /* memcpy */
void sub_080C31E8(void *, void *, u32, u32); /* state-machine dispatch */
void sub_080C31E4(void *, void *, u32);    /* indirect call through a callback */

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

void updateStatusMenu(u8 *entity)
{
  u8 *playerState = gGameStatus;
  int prevCategory = (s8) gMenuState[MENU_CATEGORY];
  {
    u8 *video = gCameraState;
    u16 *repeatKeys = (u16 *) (video + 0x1470);
    u16 dirMask = (*repeatKeys) & MENU_INPUT_DIR_BOTH;
    if (dirMask != MENU_INPUT_DIR_BOTH)
    {
      u16 heldKeys;
      if (dirMask != 0)
      {
        playSound(SFX_MENU_MOVE);
      }
      heldKeys = *repeatKeys;
      if (MENU_INPUT_PREV & heldKeys)
      {
        gMenuState[MENU_CATEGORY] = gMenuState[MENU_CATEGORY] - 1;
      }
      if (and80(heldKeys))
      {
        gMenuState[MENU_CATEGORY] = gMenuState[MENU_CATEGORY] + 1;
      }
      if (((s8) gMenuState[MENU_CATEGORY]) < 0)
      {
        gMenuState[MENU_CATEGORY] = MENU_CATEGORY_MAX;
      }
      if (((s8) gMenuState[MENU_CATEGORY]) > MENU_CATEGORY_MAX)
      {
        gMenuState[MENU_CATEGORY] = 0;
      }
    }
  }
  if (prevCategory != ((s8) gMenuState[MENU_CATEGORY]))
  {
    gMenuState[MENU_REDRAW_FLAG] = (gMenuState[MENU_REDRAW_FLAG] + 1) & 1;
    sub_0800F1D8(gMenuState[MENU_CATEGORY], gMenuState[MENU_REDRAW_FLAG]);
    sub_0800F3C8(gMenuState[MENU_REDRAW_FLAG], 0);
  }
  {
    u8 *video = gCameraState;
    u16 keys = *((u16 *) (video + 0x146C));
    u16 cancelMask = keys & MENU_INPUT_CANCEL;
    if (cancelMask != 0)
    {
      playSound(SFX_MENU_CANCEL);
      gMenuState[MENU_CANCEL_STATE] = 0;
      entity[((*((s16 *) (entity + 0x22))) * 2) + 0x17] = 0;
      {
        u32 *stateTable = &gMenuScriptCallback;
        sub_080C31E8(entity + 0x18, entity + 0x22, 0x0E, stateTable[0]);
      }
      return;
    }
    if (and1(keys) == 0)
    {
      return;
    }
    if ((*((u8 *) ((gMenuState + MENU_ENABLED_TABLE) + ((s8) gMenuState[MENU_CATEGORY])))) == 0)
    {
      return;
    }
    playSound(SFX_MENU_CONFIRM);
    sub_080C2E68(gMenuState, playerState + 0x2C4, MENU_STATE_COPY_SIZE);
    sub_0806D930(gMenuState);
    sub_0800EDAC(0);
    sub_0800F1D8(gMenuState[MENU_CATEGORY], (gMenuState[MENU_REDRAW_FLAG] + 1) & 1);
    {
      void *subObject = createChildObject(entity, MENU_SUB_OBJECT_KIND);
      *((void **) (gMenuState + MENU_SUB_OBJECT)) = subObject;
      *((u8 *) (((u8 *) subObject) + 0x3C)) = MENU_SUB_OBJECT_STEP;
    }
    {
      s32 category = (s8) gMenuState[MENU_CATEGORY];
      s32 itemOffset = (s8) (*((u8 *) ((gMenuState + MENU_ITEM_INDEX_BASE) + category)));
      itemOffset += category * 32;
      sub_0800EF3C(*((u8 *) ((gMenuState + MENU_ICON_TABLE) + itemOffset)));
    }
    entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] = (u8) cancelMask;
    {
      u32 *dispatchTable = &gScriptStepCallbackTable;
      sub_080C31E4(entity + 0x18, entity + 0x22, dispatchTable[0]);
    }
  }
}
