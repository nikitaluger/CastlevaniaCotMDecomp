extern u32 D_08671BC0[];
extern u8 D_08102BBC[];
extern u8 D_08102CAC[];
void sub_08011528(void *arg0, void *arg1);
void sub_08014588(void *arg0, void *arg1);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
inline void *inline_fn(u8 *arg0)
{
  return *((void **) (arg0 + 0x04));
}

void sub_080B54E4(void *arg0)
{
  u8 *e = arg0;
  s32 sel = 0;
  void *v38 = *((void **) (e + 0x38));
  u8 *p = *((u8 **) (e + 0x3C));
  u8 *p34 = p + 0x34;
  u8 *p48 = p + 0x48;
  s16 idx;
  u8 byte;
  u32 val;
  s16 s;
  u32 *new_var;
  u32 *baseptr;
  u32 addr;
  u8 *sp;
  if (e[0x4C] == 0)
  {
    idx = *((s16 *) (e + 0x22));
    *((u8 *) ((e + (idx * 2)) + 0x19)) = sel;
    new_var = D_08671BC0;
    sp = e + 0x18;
    sub_080C31E4((void *) sp, (void *) (e + 0x22), (s32) new_var[0]);
    idx = *((s16 *) (e + 0x22));
    *((u8 *) ((e + (idx * 2)) + 0x19)) = (*((u8 *) ((e + (idx * 2)) + 0x19))) + 1;
    idx = *((s16 *) (e + 0x22));
    sp = sp + (idx * 2);
    byte = *((u8 *) sp);
    sub_080C31E0((void *) e, (s32) (*((u32 **) (e + 0x14)))[byte]);
    return;
  }
  sub_08011528(v38, (void *) p34);
  baseptr = *((u32 **) (p34 + 0x08));
  s = *((s16 *) (p34 + 0x0E));
  byte = *((u8 *) (p34 + 0x01));
  {
    u32 sum = (u32) (s + byte);
    u32 tabval = *baseptr;
    addr = sum * 4;
    addr = (tabval + addr) - 4;
  }
  val = (*((u16 *) (((u8 *) addr) + 2))) - 0x65;
  if (((u32) val) <= 0x0E)
  {
    switch (val)
    {
      case 0:
        sel = 1;
        break;
      case 1:
        sel = 2;
        break;
      case 2:
        sel = 3;
        break;
      case 4:
        sel = 4;
        break;
      case 6:
        sel = 5;
        break;
      case 8:
        sel = 6;
        break;
      case 10:
        sel = 7;
        break;
      case 12:
        sel = 8;
        break;
      case 14:
        sel = 9;
        break;
    }
  }
  sub_08014588(*((void **) (p + 0x28)), (void *) (D_08102BBC + sel * 24));
  sub_08014588(*((void **) (p + 0x48)), (void *) ((D_08102BBC + 8) + sel * 24));
  sub_08014588(inline_fn(p48), (void *) ((D_08102BBC + 0x10) + sel * 24));
  *((u8 *) (((u8 *) (*((void **) (p + 0x28)))) + 1)) = D_08102CAC[sel * 3 + 0];
  *((u8 *) (((u8 *) (*((void **) (p + 0x48)))) + 1)) = D_08102CAC[sel * 3 + 1];
  *((u8 *) (((u8 *) inline_fn(p48)) + 1)) = D_08102CAC[sel * 3 + 2];
  if ((*((u8 *) p34)) & 0x02)
  {
    e[0x4C] = 0;
    idx = *((s16 *) (e + 0x22));
    *((u8 *) ((e + (idx * 2)) + 0x19)) = 0;
    new_var = D_08671BC0;
    sub_080C31E4((void *) (e + 0x18), (void *) (e + 0x22), (s32) new_var[0]);
  }
}
