extern u8 gCameraState[];
inline u8 *inline_fn(s32 arg0)
{
  return ((u8 *) arg0) + 0x39;
}

void sub_0808D6C4(s32 a, s32 b)
{
  u8 *p;
  u8 *p3d;
  u8 *p3b;
  u8 sum;
  u8 *p39;
  s32 idx;
  int temp;
  do { do { p3d = ((p = ((u8 *) b) + 0x3B) + 2) + a; } while (0); } while (0);
  do { do { do { p3b = p + a; } while (0); } while (0); } while (0);
  temp = (*p3d) + (*p3b);
  sum = temp;
  p39 = inline_fn(b) + a;
  p++;
  p--;
  if ((*p39) >= sum)
  {
 do { } while (0);
    *p39 = 0;
  }
  if ((*p39) < (*p3b))
  {
    gCameraState[0x1460 + a] = *((volatile s16 *) ((((u8 *) b) + (a * 4)) + 6));
    p3d = (u8 *) b;
    (*(u8 *)((0x1464 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((p3d + (a * 4)) + 0x16));
    (*(u8 *)((0x1462 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((((u8 *) b) + (a * 4)) + 0x0E));
    (*(u8 *)((0x1466 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((p3d + (a * 4)) + 0x1E));
    do { do { do { gCameraState[0x1468 + a] = 0x31; } while (0); } while (0); } while (0);
  }
  else
  {
    gCameraState[0x1460 + a] = *((volatile s16 *) ((((u8 *) b) - (-(a * 4))) + 6));
    {
      (*(u8 *)((0x1462 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((((u8 *) b) + ((a << 2))) + 0x0E));
      (*(u8 *)((0x1464 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((p3d + (a * 4)) + 0x16));
      (*(u8 *)((0x1466 + a) + (u8 *)gCameraState)) = *((volatile s16 *) ((p3d + (a * 4)) + 0x1E));
    }
    do { do { do { gCameraState[0x1468 + a] = *((u8 *) (p3d + 0x38)); } while (0); } while (0); } while (0);
  }
}
