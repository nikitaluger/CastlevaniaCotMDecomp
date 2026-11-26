extern u8 gGameStatus[];
u8 sub_0808CB58(void)
{
  volatile unsigned int pad;
  u8 r2;
  s32 r1;
  s32 r0;
  r2 = gGameStatus[0x94];
  r1 = r2 << 8;
  r0 = gGameStatus[0x95];
  r1 = r1 + r0;
  r0 = 0x711;
  if (r1 == r0)
  {
    goto set3;
  }
  if (r1 > r0)
  {
    goto big;
  }
  r0 = 0x504;
  if (r1 < r0)
  {
    goto end;
  }
  r0 = r0 + 1;
  if (r1 <= r0)
  {
    goto set3;
  }
  r0 = r0 + 0x11;
  if (r1 > r0)
  {
    goto end;
  }
  r0 = r0 - 2;
  if (r1 < r0)
  {
    goto end;
  }
  goto set3;
  big:
  r0 = 0x90F;

  if (r1 == r0)
  {
    goto set2;
  }
  if (r1 > r0)
  {
    goto bigger;
  }
  r0 = r0 - 1;
  if (r1 == r0)
  {
    goto set6;
  }
  goto end;
  bigger:
  r0 = 0xA1;

  r0 = r0 << 4;
  if (r1 == r0)
  {
    goto set2;
  }
  r0 = r0 + 0xF0;
  if (r1 != r0)
  {
    goto end;
  }
  set3:
  r2 = 3;

  goto end;
  set6:
  r2 = 6;

  goto end;
  set2:
  r2 = 2;

  end:
  return r2;

}

