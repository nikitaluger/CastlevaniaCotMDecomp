/* Update an effect entity: advance its animation and movement, lazily initialise
 * its one-shot flag, then switch pose/action and restart the script when flagged
 * or when the player comes within a distance threshold. */
void sub_080410C0(void *self)
{
  int nearActionTable;
  s32 *farActionTable;
  void *r5 = self;
  void *owner = *((void **) (((u8 *) r5) + 0x38));
  void *params = *((void **) (((u8 *) r5) + 0x3C));
  void *animState = ((u8 *) params) + 0x34;
  void *stateFlag = ((u8 *) params) + 0x48;
  s32 *switchScriptTable;
  sub_08011EE8(params, 0x16C1, 0);
  stepAnimationTrack(owner, animState);
  if ((*((u16 *) (((u8 *) params) + 0x02))) & 1)
  {
    if ((*((u8 *) stateFlag)) == 0)
    {
      *((s32 *) (((u8 *) params) + 0x14)) = 0;
      *((s32 *) (((u8 *) params) + 0x10)) = 0;
      *((u8 *) stateFlag) = 1;
    }
    if ((*((u16 *) (((u8 *) params) + 0x02))) & 4)
    {
      sub_080415D4(2, owner, params, animState);
      *((u8 *) stateFlag) = 0;
      *((u8 *) (((((u32) (*((s16 *) (((u8 *) r5) + 0x22)))) * 2) + ((u32) r5)) + 0x19)) = 0;
      nearActionTable = 0x08671BD0;
      sub_080C31E8(((u8 *) r5) + 0x18, ((u8 *) r5) + 0x22, 6, *((s32 *) nearActionTable));
      goto done;
    }
  }
  if (sub_0801459C(params, 0x300000) != 0)   /* player within near range */
  {
    sub_080415D4(2, owner, params, animState);
    *((u8 *) stateFlag) = 0;
    *((u8 *) (((((u32) (*((s16 *) (((u8 *) r5) + 0x22)))) * 2) + ((u32) r5)) + 0x19)) = 0;
    switchScriptTable = (s32 *) 0x08671BB0;
    sub_080C31E4(((u8 *) r5) + 0x18, ((u8 *) r5) + 0x22, *switchScriptTable);
    goto done;
  }
  if ((sub_0801459C(params, 0x700000) == 0) && ((*((u16 *) (((u8 *) params) + 0x02))) & 4))
  {
    sub_080415D4(0, owner, params, animState);
    *((u8 *) (((((u32) (*((s16 *) (((u8 *) r5) + 0x22)))) * 2) + ((u32) r5)) + 0x19)) = 0;
    farActionTable = (s32 *) 0x08671BD0;
    sub_080C31E8(((u8 *) r5) + 0x18, ((u8 *) r5) + 0x22, 6, *farActionTable);
  }
  done:
  return;
}
