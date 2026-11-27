extern s32 updateObjectDisplayState(void *, void *);
extern void syncSpriteToWorldPosition(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 sScriptStepCallbacks[];

/*
 * Entity script update: copy the actor's animation params into its state,
 * clear a script flag for a certain animation state, run one script step
 * (dispatching commands from the table installed at self+0x14) when the
 * display frame was not handled, then finish the update.
 */
void sub_0809ECD4(u8 *self)
{
  u8 *pScriptIndex;
  u8 *actor = *((u8 **) (self + 0x38));
  u8 *enemy = *((u8 **) (self + 0x3C));
  u32 *cmdParam;

  *((s32 *) (enemy + 8)) = *((s32 *) (self + 0x4C));
  *((s32 *) (enemy + 0x0C)) = *((s32 *) (self + 0x5C));

  if ((*((u8 *) (self + 0x6C))) == 4)
  {
    u8 *p = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    u8 cmdKind = *((u8 *) (p + 0x1A));
    if (cmdKind == 5) {}
    else if (cmdKind == 6) {}
    else
    {
      *((u8 *) (p + 0x1B)) = 0;
      cmdParam = sScriptStepCallbacks;
      sub_080C31E8(self + 0x18, self + 0x22, 5, *cmdParam);
    }
  }

  if (updateObjectDisplayState(actor, enemy) == 0)
  {
    int cmdArrayOff = 0x18;
    s32 scriptIdx;
    s32 cmdOffset;
    *((u32 *) (self + 0x14)) = 0x0866FD54;
    *((u16 *) (self + 0x22)) += 1;
    pScriptIndex = self + 0x22;
    ((u8 *) (self + ((*((s16 *) pScriptIndex)) * 2)))[0x19]++;
    scriptIdx = *((s16 *) pScriptIndex);
    cmdOffset = scriptIdx << 1;
    sub_080C31E0(self, *((void **) ((*((u32 *) (self + 0x14))) + ((*((u8 *) ((self + cmdArrayOff) + cmdOffset))) * 4))));
    *((u16 *) pScriptIndex) -= 1;
  }
  syncSpriteToWorldPosition(self, actor);
}
