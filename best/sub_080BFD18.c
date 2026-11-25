extern void *sub_080BFBEC();
typedef struct S_080BFD18
{
  u8 b[0x10];
} S_080BFD18;
void sub_080BFD18()
{
  S_080BFD18 *new_var;
  u8 r3;
  new_var = new_var;
  r3 = 0xAA;
  new_var->b[0x0F] = r3;
  r3 = new_var->b[0x00];
  r3 |= 0x0C;
  new_var->b[0x00] = r3;
}

