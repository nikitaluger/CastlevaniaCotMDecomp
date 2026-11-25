long long sub_080C2F34(void)
{
  *((volatile u8 *) 0x04000208) = 0;
  *((volatile u32 *) 0x03007FFC) = 0;
}

void sub_080C2F50(u8 *src, u8 *dst, s32 n);
void *sub_080C2EC8(void *dst, u32 val, u32 n);
extern void sub_080C25B8(s32 *src, void *dst);
extern void _080C2634(void *a, void *b, void *c);
extern s32 sub_080C2500(void);
s32 sub_080C27DC(s32 arg0, s32 arg1);
