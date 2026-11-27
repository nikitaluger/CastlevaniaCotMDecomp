/* Previews entity forms: fixes the preview sprite at screen centre, cycles the
 * form index with L/R, reapplies it with A, nudges the work coordinates with the
 * D-pad, then runs the sprite overlay and delay timer. */
extern void setEntityForm(u8 *, u8 *, s32);
extern void sub_0806A884(u8 *, u8 *);
extern s32 stepDelayTimer(u8 *, s32);

/* Input/state words of the main workspace. */
struct PreviewWorkspace
{
  u8 _0[0x24];
  u32 mode;      /* 0x24: non-zero selects workspace input over camera input */
  u16 pressed;   /* 0x28 */
  u16 held;      /* 0x2A */
};
extern struct PreviewWorkspace gMainWorkspace;

/* Input words of the camera state. */
struct PreviewCamera
{
  u8 _0[0x146C];
  u16 pressed;   /* 0x146C */
  u16 held;      /* 0x146E */
};
extern struct PreviewCamera gCameraState;

void updateFormPreviewController(u8 *actor)
{
  u8 *workPtr;
  u8 *work;
  u8 *coords;       /* same address as work, viewed as the coordinate pair */
  u8 *sprite;
  s32 newForm;

  workPtr = *((u8 **) (actor + 0x6C));
  work = workPtr + 4;
  sprite = *((u8 **) (actor + 0x38));
  coords = work;
  *((u32 *) (sprite + 0x14)) = FORM_PREVIEW_CENTER_X;
  *((u32 *) (sprite + 0x18)) = FORM_PREVIEW_CENTER_Y;
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.pressed & BUTTON_R))
    {
    }
    else
    {
      goto b1;
    }
  }
  else
    if (gCameraState.pressed & BUTTON_R)
  {
    b1:
    newForm = (*((s32 *) (work + 0x1C))) + 1;

    *((s32 *) (work + 0x1C)) = newForm;
    if (newForm > FORM_PREVIEW_MAX_FORM)
    {
      *((s32 *) (work + 0x1C)) = 0;
    }
    setEntityForm(sprite, work, *((s32 *) (work + 0x1C)));
  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.pressed & BUTTON_L))
    {
    }
    else
    {
      goto b2;
    }
  }
  else
    if (gCameraState.pressed & BUTTON_L)
  {
    b2:
    newForm = (*((s32 *) (work + 0x1C))) - 1;

    *((s32 *) (work + 0x1C)) = newForm;
    if (newForm < 0)
    {
      *((s32 *) (work + 0x1C)) = FORM_PREVIEW_MAX_FORM;
    }
    setEntityForm(sprite, work, *((s32 *) (work + 0x1C)));
  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.pressed & BUTTON_A))
    {
    }
    else
    {
      goto b3;
    }
  }
  else
    if (gCameraState.pressed & BUTTON_A)
  {
    b3:
    setEntityForm(sprite, work, *((s32 *) (work + 0x1C)));

  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.held & BUTTON_RIGHT))
    {
    }
    else
    {
      goto b4;
    }
  }
  else
    if (gCameraState.held & BUTTON_RIGHT)
  {
    b4:
    *((u32 *) coords) += FORM_PREVIEW_MOVE_STEP;

  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.held & BUTTON_LEFT))
    {
    }
    else
    {
      goto b5;
    }
  }
  else
    if (gCameraState.held & BUTTON_LEFT)
  {
    b5:
    *((u32 *) coords) += 0xFFFE0000;

  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.held & BUTTON_UP))
    {
    }
    else
    {
      goto b6;
    }
  }
  else
    if (gCameraState.held & BUTTON_UP)
  {
    b6:
    *((u32 *) (coords + 4)) += 0xFFFE0000;

  }
  if (gMainWorkspace.mode != 0)
  {
    if (!(gMainWorkspace.held & BUTTON_DOWN))
    {
    }
    else
    {
      goto b7;
    }
  }
  else
    if (gCameraState.held & BUTTON_DOWN)
  {
    b7:
    *((u32 *) (coords + 4)) += FORM_PREVIEW_MOVE_STEP;

  }
  sub_0806A884(sprite, coords);
  stepDelayTimer(work + 0x28, (s32) sprite);
}
