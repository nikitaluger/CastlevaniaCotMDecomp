struct S_020279D0
{
  u8 _pad[4];
  s32 f4;
  s32 f8;
};
extern struct S_020279D0 D_020279D0;
extern u32 D_02020BC0;
extern s32 D_02020BC4;
extern u32 D_02020BC8;
extern s32 D_02020BCC;
s32 sub_080168E0(void)
{
  void *p = (void *) D_02020BC0;
  s32 result;
 do { if (p != NULL) { p = ((u8 *) p) + 4; D_02020BC0 = (u32) (*((void **) p)); result = *((s32 *) p); } else { result = 0; } } while (0);
  return result;
}

void sub_080168C4(void);
void sub_080168A8(void);
void sub_080168A8(void);
s32 sub_080168E0(void);
void sub_08016910(void);
