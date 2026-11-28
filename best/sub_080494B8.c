extern s32 sub_08014090(s32 index);
extern s32 sub_080145D8(s32 centerX, s32 centerY, s32 halfW, s32 halfH);
extern unsigned long sub_08064560(s32, s32);
extern s32 sub_0805E314(s32);
extern s32 sub_08064210(s32);
inline static u8 *inline_fn()
{
  return (u8 *) 0x080CF964;
}

inline static u8 *inline_fn2(u8 *arg0)
{
  return (u8 *) (arg0 + 0x18A8);
}

void sub_080494B8(void *obj)
{
  u8 *self;
  s32 flag;
  void *ac;
  u8 *p40;
  s32 ret;
  u32 temp;
  s32 *temp2;
  s32 temp3;
  self = (u8 *) obj;
  flag = 0;
  ac = *((void **) (self + 0xAC));
  p40 = self + 0x40;
  do
  {
 do { do { ret = sub_08014090((s32) (*((s16 *) (((u8 *) 0x080CF95C) + (((s32) (*p40)) * 4))))); } while (0); if (ret == 0) { s16 *p = *((s16 **) (((u8 *) ac) + 4)); s32 x = ((s32) p[0]) << 16; s32 y = ((s32) p[1]) << 16; if (sub_080145D8(x, y, 0xF0 << 15, 0xA0 << 15) == 0) { *((u8 *) (self + 0x3C)) = 1; return; } } else { return; } { u16 val2 = *((u16 *) (inline_fn() + (((s32) (*p40)) * 2))); if (((u32) sub_08014090(val2)) > 1) { return; } { u8 *c = self + 0x3C; *c = (*c) - 1; if ((*c) != 0) { return; } *c = 0x3C; } { u8 *ws = (u8 *) 0x02025FF0; u32 base1870 = *((u32 *) (ws + 0x1870)); u8 idx = *p40; u16 v = *((u16 *) (inline_fn() + (((s32) idx) * 2))); u8 *obj2 = (u8 *) sub_08064560(base1870, (s32) v); unsigned int x; s32 hi; temp2 = (s32 *) (ws + 0x174C); temp = (*temp2) - (((*((u32 *) ((((u8 *) 0x02021E90) + 0x1278) + (((s32) ((*inline_fn2(ws)) + 1)) << 6)))) + 0x8000) & 0xFFFF0000); x = temp; if (((u32) x) <= 0x004FFFFF) { flag = -1; } if (x > 0x00A00000) { flag = 1; } if (flag == 0) { s32 r = sub_0805E314(0); flag = r & 1; if (flag == 0) { flag = 1; } else { flag = flag; } } *((u8 *) (obj2 + 0x70)) = (u8) flag; if (flag == 1) { u32 v4 = *((u32 *) ((((u8 *) 0x02021E90) + 0x1278) + (((s32) ((*inline_fn2(ws)) + 1)) << 6))); *((u32 *) (obj2 + 0x4C)) = v4 + 0xFFE88000; } else { u32 v4 = *((u32 *) ((((u8 *) 0x02021E90) + 0x1278) + (((s32) ((*inline_fn2(ws)) + 1)) << 6))); *((u32 *) (obj2 + 0x4C)) = v4 + 0x01088000; } { s32 r6ret = sub_08064210(0x60); u32 v5 = *((u32 *) ((((u8 *) 0x02021E90) + 0x127C) + (((s32) ((*inline_fn2(ws)) + 1)) << 6))); temp3 = (r6ret + 0x20) << 16; *((u32 *) (obj2 + 0x5C)) = v5 + (temp3 + 0x8000); } } } } while (0);
  }
  while (0);
}
