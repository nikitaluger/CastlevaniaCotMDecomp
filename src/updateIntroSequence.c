/* Per-frame update of the scripted intro/cutscene sequence: advances the event
 * script timeline (running the handlers whose time has come), animates the
 * background scroll and the palette fade, and ends the sequence when the script
 * finishes or START is held. */
extern u8 gGameStatus[];      /* game/player data; +0x0A = intro-skip allowed */
extern u8 gCameraState[];      /* shared video state (BG scroll buffers, fades) */
extern u16 D_080CAA00[];     /* event script: time / handler index pairs */
extern s32 D_0866CB98[];     /* event script step handlers (thumb pointers) */
extern u32 gScriptStepCallbackTable;
void sub_08000EDC(s32, u8 *, u32, s32, s32);        /* post display-effect block */
void sub_080060C4(s32, s32, s32, void *);           /* apply to every sound player */
void sub_080C31E4(u8 *, u8 *, u32);                 /* indirect call */
void sub_080C31E0(void *, s32);                     /* indirect call */
s32 sub_0805FEC8(u16);                              /* start palette fade effect */
void sub_0800942C(void *);                          /* build scroll wipe row */
void sub_080C0384(void);                            /* sound player volume */
void updateIntroSequence(u8 *entity)
{
  u8 *gameData = gGameStatus;
  u8 *script = *((u8 **) (entity + 0x3C));   /* script state: frame/pos/fade/scroll */
  s32 scriptPos;
  u8 *fadePtr;
  u8 *video;
  u8 skipFlag;
  *((s32 *) script) = (*((s32 *) script)) + 1;   /* frame counter */
  if (D_080CAA00[*((s32 *) (script + 4))] == (*((s32 *) script)))
  {
    scriptPos = *((s32 *) (script + 4));
    do
    {
      *((s32 *) (script + 4)) = scriptPos + 1;
      sub_080C31E0(script, D_0866CB98[D_080CAA00[scriptPos + 1]]);
      scriptPos = *((s32 *) (script + 4));
    }
    while (D_080CAA00[scriptPos] == (*((s32 *) script)));
  }
  if (D_080CAA00[*((s32 *) (script + 4))] == 0) goto fail;
  skipFlag = gameData[0x0A];
  video = gCameraState;
  if (skipFlag != 0 && (((*((u16 *) (video + 0x146C))) & 8) != 0)) goto fail;
  goto cont;
fail:
  sub_080060C4(0, 3, 0, sub_080C0384);
  entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] = 0;
  {
    u32 *fp = &gScriptStepCallbackTable;
    sub_080C31E4(entity + 0x18, entity + 0x22, *fp);
  }
  return;
cont:
  *((s32 *) (video + 0x127C)) = (*((s32 *) (video + 0x127C))) + 0xFFFFD70B;  /* pan BG scroll */
  if ((*((s32 *) (video + 0x127C))) < 0)
  {
    *((s32 *) (video + 0x127C)) = 0;
  }
  if ((*((s32 *) (script + 8))) != 0)   /* palette fade effect */
  {
    if (sub_0805FEC8((u16) (*((s32 *) (script + 8)))) == 0)
    {
      *((s32 *) (script + 8)) = 0;
    }
  }
  if (((*((s32 *) (script + 0x0C))) != 0) && ((entity[((*((s16 *) (entity + 0x22))) * 2) + 0x19] & 7) == 0))
  {
    s32 t;
    t = (*((s32 *) (script + 0x10))) - 1;   /* fade level */
    *((s32 *) (script + 0x10)) = t;
    *((s32 *) (script + 0x14)) = (*((s32 *) (script + 0x14))) + 1;  /* fade step */
    if (t == 0)
    {
      *((s32 *) (script + 0x0C)) = 0;
    }
    {
      u8 *blendRegs = (u8 *) 0x03000830;
      fadePtr = script + 0x10;
      *((u16 *) (blendRegs + 6)) = (u16) (((*((s32 *) (script + 0x14))) << 8) | (*((s32 *) fadePtr)));
    }
  }
  if ((*((s32 *) (script + 0x98))) != 0)   /* background scroll wipe */
  {
    s32 t;
    t = (*((s32 *) (script + 0x9C))) - 1;
    *((s32 *) (script + 0x9C)) = t;
    if (t == 0)
    {
      s32 t2;
      s32 v;
      *((s32 *) (script + 0x9C)) = 3;
      sub_0800942C(script);
      sub_08000EDC(0, script + (((*((s32 *) (script + 0xA4))) * 0x140) + 0xA8), 0x04000016, 2, 0x10);
      {
        u8 *base2 = gCameraState;
        v = *((s32 *) (script + 0xA0));
        *((u8 *) (base2 + 0x1364)) = (u8) v;
        *((u8 *) (base2 + 0x1360)) = 8;
      }
      t2 = (*((s32 *) (script + 0xA0))) - 1;
      *((s32 *) (script + 0xA0)) = t2;
      if (t2 <= 0x17)
      {
        *((s32 *) (script + 0x98)) = t;
      }
      *((s32 *) (script + 0xA4)) = ((*((s32 *) (script + 0xA4))) + 1) & 1;
    }
  }
}
