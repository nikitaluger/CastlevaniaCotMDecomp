extern const u32 D_080C001C;
volatile short sub_080BFD7C(void)
{
  struct S_BFD7C
  {
    u32 f0;
    u8 f4;
    u8 _5[6];
    u8 fB;
  };
  struct S_BFD7C *p = *((struct S_BFD7C **) 0x03007FF0);
  u32 temp;
  temp = p->f0;
  if (((u32) (temp - D_080C001C)) <= 1)
  {
    char v = (*((struct S_BFD7C **) 0x03007FF0))->f4 - 1;
    (*((struct S_BFD7C **) 0x03007FF0))->f4 = v;
    {
      (*((struct S_BFD7C **) 0x03007FF0))->f4 = (*((struct S_BFD7C **) 0x03007FF0))->fB;
      do
      {
      }
      while (0);
      *((vu16 *) 0x040000C6) = 0;
      *((vu16 *) 0x040000D2) = 0;
      *((vu16 *) 0x040000C6) = 0xB600;
      *((vu16 *) 0x040000D2) = 0xB600;
    }
  }
}
