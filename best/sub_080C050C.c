extern u8 D_08106DCC[];
extern u8 D_08106E38[];
extern void sub_080C0B70(s32 *);

inline u8 *inline_fn(u8 **arg0, u32 arg1) { return (*arg0) + arg1; }

void sub_080C050C(u32 arg0)
{
  u32 off;
  u8 *t;
  u8 *e;
  s32 new_var;
  off = arg0 << 16;
  t = D_08106DCC;
  e = D_08106E38;
  off >>= 13;
  new_var = *(u16 *)((off + e) + 4);
  new_var = *(s32 *)(t + new_var * 12);
  if (*(s32 *)new_var == *(s32 *)inline_fn(&e, off))
    sub_080C0B70((s32 *)new_var);
}
