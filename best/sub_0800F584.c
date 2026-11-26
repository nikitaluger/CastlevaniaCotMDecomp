void sub_0800EB44(u16 a, s32 b, s32 c);
void sub_0800FE08(u32 a, s32 b, s32 c, void *d);
u8 sub_08086E78(u8 a, u8 b);
u32 divideInt(u32 a, u32 b);
void decompressToVram(u32 a, void *b);
void postDisplaySprite(s32 a, void *b, void *c, s32 d, s32 e);
struct S25368
{
  u8 _0[0x30C];
  u8 a[0xA];
  u8 b[0xA];
};
extern struct S25368 gGameStatus;
extern u8 D_080E47E8[];
extern u16 D_080CB082[10][10];
extern u8 D_080CB14A[10][10];
extern u32 D_0866CFDC[];
void sub_0800F584(u8 arg0, u8 arg1)
{
  u8 *new_var;
  u32 result = 0;
  if ((gGameStatus.a[arg1 - 1] == 0) || (gGameStatus.b[arg0 - 1] == 0))
  {
    sub_0800EB44(0x816A, 2, 0xFC0);
    sub_0800FE08(0, 3, 0x511C, (void *) 0x0600EB48);
  }
  else
    if (sub_08086E78(arg0, arg1) != 0)
  {
    u32 off = result = ((arg1 - 1) * 12) + ((arg0 - 1) * 120);
    if ((*((u32 *) (D_080E47E8 + off))) != 0)
    {
      result = divideInt(*((u32 *) (D_080E47E8 + off)), 0x444);
    }
    else
    {
      new_var = (D_080E47E8 + off) + 6;
      result = *((u16 *) new_var);
    }
    sub_0800EB44(D_080CB082[arg0 - 1][arg1 - 1], 2, 0xFC0);
    sub_0800FE08(result, 3, 0x511C, (void *) 0x0600EB48);
    result = D_080CB14A[arg0 - 1][arg1 - 1];
  }
  else
  {
    sub_0800EB44(0x8169, 2, 0xFC0);
    sub_0800FE08(0, 3, 0x511C, 0x0600EB48);
  }
 do { decompressToVram(D_0866CFDC[result], (void *) 0x0600B7E0); } while (0);
  postDisplaySprite(1, (void *) 0x0600B7E0, (void *) 0x0600B740, 0xA0, 0x10);
}
