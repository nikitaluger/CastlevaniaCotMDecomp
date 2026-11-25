extern s32 sub_08003740(u8 *, u8 *);
extern void sub_08005E80(s32);
extern void sub_0806A7AC(u8 *, u8 *, s32);
extern void sub_0806A884(u8 *, u8 *);
extern s32 sub_0806B104(u8 *, u8 *, u8 *);
extern s32 sub_0806B3E8(u8 *, u8 *, u8 *, u8 *);
extern s32 sub_0806B820(u8 *, u8 *, u8 *, u8 *);
extern s32 sub_0806BA98(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806C49C(u8 *, u8 *);
extern s32 sub_0806C4B4(u8 *, u8 *);
extern void sub_0806C5EC(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806C6B0(u8 *, u8 *, u8 *, u8 *);
extern void sub_0806E114(u8 *, s32, u32, u32);
extern void sub_080C31E8(u8 *, u8 *, s32, s32);
extern s32 sub_0806AB04(u8 *, u8 *, u8 *, u8 *);
extern u16 sub_0806BCD8(u8 *, u8 *, u8 *, u8 *);
struct GameState { u8 unk0[0x10]; u32 mode; };
extern struct GameState D_02025FF0;
extern u8 D_02025368[];
struct ScriptedObject
{
  u8 unk0[0x22];
  s16 index;
  u8 unk24[0x38 - 0x24];
  u8 *target;
  u8 unk3C[0x6C - 0x3C];
  u8 *data;
};
struct BossData
{
  u8 unk0[4];
  u32 gfxId;
  u8 unk8[0xD0 - 8];
  u16 flags;
  u16 flags2;
};
/* Update a scripted boss: run its behavior callbacks, handle attack and state
 * transitions, then dispatch the resulting script action. */
void sub_080635F4(struct ScriptedObject *arg0)
{
  struct BossData *data;
  u8 *work;
  int offset;
  u8 *workState;
  u8 *target;
  u8 *gameFlags;
  u16 flags16;
  u16 result16;
  s32 count;
  data = (struct BossData *) arg0->data;
  work = ((u8 *) data) + 4;
  target = arg0->target;
  workState = work;
  gameFlags = D_02025368;
  if (sub_0806C4B4(work, workState) != 0)
  {
    goto end;
  }
  sub_0806C5EC((u8 *) arg0, target, workState, workState);
  if (((*((u32 *) (workState + 0x60))) & 0xF) == 0)
  {
    sub_08005E80(0x69);
  }
  *((u32 *) (workState + 0x60)) = (*((u32 *) (workState + 0x60))) + 1;
  if (sub_0806B3E8((u8 *) arg0, target, workState, workState) != 0) goto mid;
  if (sub_0806B820((u8 *) arg0, target, workState, workState) != 0) goto mid;
  if (sub_0806BA98((u8 *) arg0, target, workState, workState) != 0) goto mid;
  if ((sub_0806B104(target, workState, workState) == 0) || ((*((u32 *) (workState + 0x68))) != 0))
  {
    if (((*((s32 *) (workState + 0x60))) > 0x1F) && (D_02025FF0.mode != 1))
    {
      sub_0806A7AC(target, workState, 9);
      sub_0806E114((u8 *) arg0, 4, data->gfxId, *((u32 *) (workState + 4)));
    }
    else
    {
      sub_0806C49C(target, work);
    }
    *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
    {
      s32 *scriptOps = (s32 *) 0x08671BD0;
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 4, *scriptOps);
    }
  }
  else
  {
    s32 zero = 0;
    flags16 = (*((u16 *) (((u8 *) data) + 0xD0))) | 0xC | zero;
    *((u16 *) (((u8 *) data) + 0xD0)) = flags16;
    if (gameFlags[0x3CB] != 0)
    {
      flags16 |= 1;
      *((u16 *) (((u8 *) data) + 0xD0)) = flags16;
    }
    if (((*((u16 *) (((u8 *) data) + 0xD2))) & 0x100) != 0)
    {
      *((u32 *) (workState + 0x68)) = 2;
      sub_0806A7AC(target, workState, 0x1E);
      *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = zero;
      {
        s32 *scriptOps = (s32 *) 0x08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 6, *scriptOps);
      }
    }
  }
  mid:
  sub_0806AB04((u8 *) arg0, target, work, workState);
  if ((*((u32 *) (work + 0x40))) == 0)
  {
    count = *((u32 *) (work + 0x4C));
    if (count == 0)
    {
      sub_0806A7AC(target, work, 0x10);
      *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = count;
      {
        s32 *scriptOps = (s32 *) 0x08671BD0;
        sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, 3, *scriptOps);
      }
    }
  }
  sub_0806A884(target, workState);
  result16 = (*((u32 *) (work + 0xC4)) = sub_0806BCD8((u8 *) arg0, target, work, workState));
  if (result16 != 0)
  {
    *((u8 *) ((((u8 *) arg0) + (2 * arg0->index)) + 0x19)) = 0;
    {
      s32 *scriptOps = (s32 *) 0x08671BD0;
      sub_080C31E8(((u8 *) arg0) + 0x18, ((u8 *) arg0) + 0x22, *((u32 *) (work + 0xC4)), *scriptOps);
    }
  }
  offset = 0x28;
  sub_08003740(work + offset, target);
  sub_0806C6B0((u8 *) arg0, target, work, workState);
  end:
  ;
}
