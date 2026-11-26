void postDisplaySprite(s32 a, void *b, void *c, s32 d, s32 e);
struct Entry
{
  u16 c0[16];
  u16 c1[16];
  s32 v40;
  u32 pad;
};
extern struct Entry D_020227EC[];
inline int inline_fn(u32 arg0)
{
  return arg0 & 0x7C00;
}

void sub_08006680(s32 arg0, s32 arg1)
{
  s32 new_var3;
  unsigned char new_var4;
  int new_var;
  int new_var5;
  u16 tmp[0x200];
  s32 i = arg0;
  ;
  new_var = 0x7C00;
  new_var5 = 8;
  if (arg0 <= arg1)
  {
    s32 new_var2 = 0x01000000;
    do
    {
      struct Entry *e = &D_020227EC[i];
      s32 v40 = e->v40;
      s32 t = v40 >> 16;
      s32 s = (0x01000000 - v40) >> 16;
      s32 j;
      new_var2 = new_var5;
      do
      {
        for (j = 0; j < 16; j++)
        {
          u16 a = e->c0[j];
          u16 b = e->c1[j];
          u32 r = (((a & 0x1F) * t) + ((b & 0x1F) * s)) >> new_var2;
          u32 g = (((a & 0x3E0) * t) + ((b & 0x3E0) * s)) >> new_var2;
          u32 bl = ((inline_fn(a) * t) + ((b & new_var) * s)) >> new_var2;
          new_var3 = j;
          new_var = r | (g & 0x3E0);
          tmp[((i * 2) * 8) + new_var3] = new_var | inline_fn(bl);
        }

        if (e->c1)
        {
          i++;
        }
        else
          if (s)
        {
          i++;
        }
        else
        {
          i++;
        }
      }
      while (0);
    }
    while (i <= arg1);
  }
  i = 5;
  postDisplaySprite(1, &tmp[arg0 * 16], (void *) (0x05000000 + (arg0 << i)), ((arg1 - arg0) + (new_var3 = 1)) << i, 0x10);
}

