extern s32 sub_0801459C(void *, s32);
extern s32 sub_08014900(s32);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E8(void *, void *, u16, s32);
extern u16 D_08102B7C[];

/* Script-step handler: choose a reaction index from the entity's distance to the
 * shared position and a body timer, run that indirect script branch, then
 * dispatch the next step. */
void sub_080B4074(u8 *arg0)
{
  u8 *entity = *((u8 **) (arg0 + 0x3C));
  u8 *body = entity + 0x48;
  u8 *scriptData;
  s32 reaction;
  s32 timer;
  u8 stateByte;
  if (sub_08014900(*((s32 *) (entity + 8))) <= 0x1FFFFF)
  {
    reaction = 1;
  }
  else
  {
    s32 distance = sub_0801459C(entity, 0x400000);
    reaction = (((-distance) | distance) >> 31) & 2;
  }
  timer = (*((u8 *) (body + 0x1F))) + 1;
  *((u8 *) (body + 0x1F)) = timer;
  stateByte = *((u8 *) (body + 0x21));
  if ((stateByte == 1) && (timer & stateByte))
  {
    reaction = 3;
  }
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) = 0;
  {
    s32 *lit = (s32 *) 0x08671BD0;
    scriptData = arg0 + 0x18;
    sub_080C31E8(scriptData, arg0 + 0x22, D_08102B7C[reaction], *lit);
  }
  *((u8 *) ((arg0 + ((*((s16 *) (arg0 + 0x22))) * 2)) + 0x19)) += 1;
  scriptData = scriptData + ((*((s16 *) (arg0 + 0x22))) * 2);
  sub_080C31E0(arg0, *((s32 *) ((*((u32 *) (arg0 + 0x14))) + ((*scriptData) * 4))));
}
