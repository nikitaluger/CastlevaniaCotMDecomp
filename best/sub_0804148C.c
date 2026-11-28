extern u8 gCameraState[];
extern u8 gMainWorkspace[];
inline static u8 *inline_fn(u8 *arg0, int arg1)
{
  return arg0 + arg1;
}

void sub_0804148C(void *arg0)
{
  u8 *__base_gCameraState;
  unsigned short sum_1;
  s32 sum_2;
  u8 *self = (u8 *) arg0;
  u8 *anim = *((u8 **) inline_fn((u8 *) arg0, 0x38));
  u8 *work = *((u8 **) inline_fn((u8 *) arg0, 0x3C));
  u32 v;
  s32 idx;
  s32 __repair_idx_1;
  s32 camword;
  u8 *camPtr;
  u8 upd2;
  s32 temp;
  do
  {
    do
    {
      (void) (&v);
      v = work[0];
      work[0] = v + 1;
      if ((((s32) ((work[0] + 1) << 24)) >> 24) == 2)
      {
        work[0] = 0;
      }
      idx = ((s32) (v << 24)) >> 22;
      sum_1 = inline_fn(inline_fn(work, 4), idx);
      *((s32 *) sum_1) = *((s32 *) inline_fn(*((u8 **) inline_fn((u8 *) arg0, 0x28)), 0x4C));
    }
    while (0);
  }
  while (0);
  sum_2 = inline_fn(work, 0xC);
  *((s32 *) (sum_2 + idx)) = *((s32 *) inline_fn(*((u8 **) inline_fn((u8 *) arg0, 0x28)), 0x5C));
  do
  {
    do
    {
      do
      {
        if ((*((u8 *) inline_fn(*((u8 **) inline_fn(self, 0x28)), 0x70))) != 0)
        {
          s32 idx_a1;
          if (work[1] & 1)
          {
            *((u8 *) inline_fn(anim, 0x2A)) |= 0x40;
            idx_a1 = ((s8) work[0]) * 4;
          }
          else
          {
            upd2 = (*((u8 *) inline_fn(anim, 0x2A))) & 0xBF;
            *((u8 *) inline_fn(anim, 0x2A)) = upd2;
            work[1]++;
            idx_a1 = ((s8) work[0]) * 4;
          }
          __repair_idx_1 = *((s32 *) inline_fn(inline_fn(__base_gCameraState = gCameraState, 0x1278), (gMainWorkspace[0x18A8] + 1) * 0x40));
          sum_2 = inline_fn(work, 4);
          temp = __repair_idx_1 + 0x8000;
          *((s32 *) inline_fn(anim, 0x14)) = (*((s32 *) (sum_2 + idx_a1))) - (temp & 0xFFFF0000);
          sum_2 = inline_fn(inline_fn(work, 0xC), idx_a1);
          camPtr = inline_fn(inline_fn(__base_gCameraState, 0x127C), (gMainWorkspace[0x18A8] + 1) * 0x40);
          camword = *((s32 *) camPtr);
          *((s32 *) inline_fn(anim, 0x18)) = (*((s32 *) sum_2)) - (camword & 0xFFFF8000);
          if ((*((u8 *) inline_fn(*((u8 **) inline_fn((u8 *) arg0, 0x28)), 0x6C))) != 0)
          {
            *((u16 *) inline_fn(anim, 2)) |= 0x10;
          }
          else
          {
            *((u16 *) inline_fn(anim, 2)) &= 0xFFEF;
          }
        }
        else
        {
          *((u8 *) inline_fn(anim, 0x2A)) &= 0xBF;
        }
      }
      while (0);
    }
    while (0);
  }
  while (0);
  *((s32 *) inline_fn((u8 *) arg0, 0x4C)) = *((s32 *) inline_fn(inline_fn(work, 4), ((s8) work[0]) * 4));
  *((s32 *) inline_fn((u8 *) arg0, 0x5C)) = *((s32 *) inline_fn(inline_fn(work, 0xC), ((s8) work[0]) * 4));
  *((u8 *) inline_fn((u8 *) arg0, 0x6C)) = *((u8 *) inline_fn(*((u8 **) inline_fn((u8 *) arg0, 0x28)), 0x6C));
}

