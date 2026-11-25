extern void sub_08013C5C(void *self, void *actor);
extern s32 sub_08016238(void *animState);
extern s32 sub_08013B5C(void *actor, void *enemy);
extern void sub_080C31E8(void *cmdArray, void *pIndex, s32 kind, u32 param);
extern void sub_080C31E0(void *self, void *cmd);
extern void sub_08013C8C(void *self, void *actor);
extern u32 D_08671BDC[];
extern u8 D_0866DCF0[];

inline int orAnimFlag(u8 *state)
{
  return (*((u16 *) state)) | 1;
}

/*
 * Entity script update: sync the actor, mark the enemy's animation active,
 * run one script step (dispatching commands from the table installed at
 * self+0x14) when its display frame was not handled, then finish the update.
 */
void sub_08032C84(u8 *self)
{
  u8 *pScriptIndex;
  u8 *actor = *((u8 **) (self + 0x38));
  u8 *enemy = *((u8 **) (self + 0x3C));
  u32 *cmdParam;
  sub_08013C5C(self, actor);
  if (sub_08016238(*((void **) (enemy + 0x28))) != 0)
  {
    *((u16 *) enemy) = orAnimFlag(enemy);
  }
  if ((*((u16 *) enemy)) & 1)
  {
    u8 *p = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    if ((*((u8 *) (p + 0x1A))) != 2)
    {
      *((u8 *) (p + 0x1B)) = 0;
      cmdParam = D_08671BDC;
      sub_080C31E8(self + 0x18, self + 0x22, 2, *cmdParam);
    }
  }
  if (sub_08013B5C(actor, enemy) == 0)
  {
    int cmdArrayOff = 0x18;
    s32 scriptIdx;
    s32 cmdOffset;
    *((u32 *) (self + 0x14)) = (u32) D_0866DCF0;
    *((u16 *) (self + 0x22)) += 1;
    pScriptIndex = self + 0x22;
    ((u8 *) (self + ((*((s16 *) pScriptIndex)) * 2)))[0x19]++;
    scriptIdx = *((s16 *) pScriptIndex);
    cmdOffset = scriptIdx << 1;
    sub_080C31E0(self, *((void **) ((*((u32 *) (self + 0x14))) + ((*((u8 *) ((self + cmdArrayOff) + cmdOffset))) * 4))));
    *((u16 *) pScriptIndex) -= 1;
  }
  sub_08013C8C(self, actor);
}
