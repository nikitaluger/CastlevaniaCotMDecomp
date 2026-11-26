struct H_02004000
{
  u32 unk;
  s32 start;
  s32 end;
};
extern struct H_02004000 D_02004000[];
inline int inline_fn(s32 arg0, int arg1)
{
  return arg0 + arg1;
}

s32 sub_08000A70(s32 arg0, s32 arg1, s32 arg2)
{
  s8 *cur;
  s8 *end;
  s32 new_var;
  s32 align;
  s8 *first;
  s8 *data;
  s8 *p;
  s32 mask;
  int new_var4;
  s32 new_var5;
  s32 hdr;
  s32 size;
  s32 avail;
  s32 pad;
  s32 ff;
  int new_var2;
  s32 new_var3;
  align = arg2;

  arg1 = (s32) ((((u32) inline_fn(arg1, 3)) >> 2) * 4);
  cur = (s8 *) D_02004000[arg0].end;
  end = cur + D_02004000[arg0].start;
  mask = align - 1;
  first = cur;
  new_var4 = 4;
  if (cur == end)
  {
    return 0;
  }
  ff = 0xFF;
  hdr = *((u32 *) cur);
loop_2:

  if ((*((s8 *) cur)) != 0)
  {
    goto advance;
  }
  { { do { data = cur + 4; } while (0); } }
  new_var2 = 0;
  goto align_loop;
coalesce:
  p = cur + (size + new_var4);
  if (((u32) p) >= ((u32) end))
  {
    goto split;
  }
  if ((*((s8 *) p)) != 0)
  {
    goto split;
  }
  pad = *((u32 *) p);
  do { do { do { new_var3 = (inline_fn(inline_fn(size, 4), pad >> 8) << 8); } while (0); } while (0); } while (0); *((u32 *) cur) = new_var3 | (pad & ff);
align_loop:
  if ((((s32) data) & mask) != 0)
  {
    pad = align - (((s32) data) & mask);
  }
  else
  {
    pad = new_var2;
  }
  hdr = *((u32 *) cur);
  size = hdr >> 8;
  avail = size - pad;
  if (arg1 > avail)
  {
    goto coalesce;
  }
  hdr = pad - 4;
  p = cur + pad;
  if (hdr > new_var2)
  {
    *((u32 *) p) = ((*((u32 *) p)) & ff) | (avail << 8);
    do { new_var3 = hdr << 8; } while (0);
    *((u32 *) cur) = ((*((u32 *) cur)) & ff) | new_var3;
  }
  else
  {
    { if (first != cur) {
                          s32 hdr_a1; new_var3 = (avail << 8); *((u32 *) p) = ((*((u32 *) p)) & ff) | new_var3; new_var5 = pad; hdr_a1 = *((u32 *) first); *((u32 *) first) = (inline_fn(hdr_a1 >> 8, new_var5) << 8) | (hdr_a1 & ff); } else { goto b46; } }
  }
  cur = p;
  b46:
  p = NULL;

  hdr = *((u32 *) cur);
  split:
  if (p != NULL)
  {
    goto advance;
  }

  {
    s32 leftover;
    leftover = ((hdr >> 8) - arg1) - 4;
    if (leftover > new_var2)
    {
      p = cur + (arg1 + new_var4);
      *((u8 *) p) = 0;
      size = leftover << 8;
      *((u32 *) p) = ((*((u32 *) p)) & ff) | size;
      *((u32 *) cur) = (arg1 << 8) | ((*((u32 *) cur)) & ff);
    }
    *((u8 *) cur) = 0x80;
    return (s32) (p + 4);
  }
  advance:
  first = cur;

  cur = cur + inline_fn(hdr >> 8, 4);
  if (cur == end)
  {
    return new_var2;
  }
  hdr = *((u32 *) cur); goto loop_2;
}
