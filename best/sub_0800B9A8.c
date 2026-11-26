extern s32 sub_080103F0(u8);
extern void sub_0800B824(u16, u16, s32);
extern void sub_0800BDBC(const void *, void *, s32);
extern void drawDecimal(s32, s32, s16 *);
extern void drawPaddedDecimal(s32, s32, s32, s16 *);
extern u32 formatPlayTime(u32);
extern s32 divideInt(s32, s32);
extern s32 moduloInt(s32, s32);
extern void sub_08000E54(s32, s32, s32, s32, s32);
extern void postDisplaySprite(s32, const void *, s32, s32, s32);
extern u8 gGameStatus[];
extern u16 D_02023132;
extern u8 D_080CAAC6[];
extern u8 D_080CAADE[];
extern u16 D_080CAAF6[];
extern u8 D_080CAB14[];
extern const void *D_0866CC04[];
extern const void *D_0863C084;
void sub_0800B9A8(u8 arg0, u8 arg1, void *arg2)
{
  int new_var;
  vu32 *dma;
  u16 sp4;
  void *spC = gGameStatus;
  s32 sp10 = 0;
  u32 off;
  u32 t;
  u32 vramOff;
  u32 vramBase;
  s32 sign;
  u32 a, b, c, d, e, f;
  u32 temp;
  u32 temp2;
  u32 temp3;
  u32 temp4;
  t = 2;
  if (arg1 == t)
    sp10 = 1;
  sp4 = 0;
  dma = (vu32 *)0x040000D4;
  dma[0] = (u32)&sp4;
  vramOff = (D_02023132 & 0xC) << 12;
  temp = (u32)arg1 * 8;
  off = temp;
  t = *(u16 *)(D_080CAAC6 + off);
  temp2 = vramOff + ((t + 0x100) << 5);
  vramBase = 0x06000000;
  dma[1] = temp2 + vramBase;
  dma[2] = 0x81000500;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  temp3 = ((D_02023132 & 0x1F00) << 3) + vramBase;
  a = (u32)D_080CAADE[off + 1] << 6;
  b = D_080CAADE[off];
  temp4 = a + (b - 1) * 2;
  dma[1] = temp3 + temp4;
  dma[2] = 0x81000002;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  c = (u32)D_080CAADE[off + 3] << 6;
  d = D_080CAADE[off + 2];
  dma[1] = (((D_02023132 & 0x1F00) << 3) + vramBase) + c + d * 2;
  dma[2] = 0x81000001;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  dma[1] = (((D_02023132 & 0x1F00) << 3) + vramBase) + c + (d - 4) * 2;
  dma[2] = 0x81000003;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  e = (u32)D_080CAADE[off + 5] << 6;
  f = D_080CAADE[off + 4];
  dma[1] = (((D_02023132 & 0x1F00) << 3) + vramBase) + e + (f - 1) * 2;
  dma[2] = 0x81000002;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  dma[1] = (((D_02023132 & 0x1F00) << 3) + vramBase) + e + (f - 4) * 2;
  dma[2] = 0x81000002;
  (void)dma[2];
  sp4 = 0;
  dma[0] = (u32)&sp4;
  dma[1] = (((D_02023132 & 0x1F00) << 3) + vramBase) + e + (f - 7) * 2;
  dma[2] = 0x81000002;
  (void)dma[2];
  sign = (s8)arg0;
  if (sub_080103F0(arg0) == 0 || sign < 0)
  {
    do { sub_0800BDBC(D_080CAB14, ((u8 *)arg2) + (sp10 * 0x300), (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)t) << 5)); } while (0);
    new_var = 0x10;
    if (sign >= 0)
      sub_0800B824((((u8 *)arg2)[0x635] == 1) ? 0x81DF : 0x81DE, *((u16 *)((D_080CAAC6 + off) + 2)), 0x300);
    else
      sub_08000E54(1, 0, (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)(*((u16 *)((D_080CAAC6 + off) + 2)))) << 5), 0x300, new_var);
    sub_08000E54(1, 0, (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)(*((u16 *)((D_080CAAC6 + off) + 4)))) << 5), 0x1A0, new_var);
    sub_08000E54(1, 0, (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)(*((u16 *)((D_080CAAC6 + ((u32)arg1 * 8)) + 6)))) << 5), 0x120, new_var);
  }
  else
  {
    sub_0800B824(D_080CAAF6[*((u8 *)(((u8 *)spC) + 0x94))], *((u16 *)((D_080CAAC6 + off) + 2)), 0x300);
    postDisplaySprite(1, D_0866CC04[*((s16 *)(((u8 *)spC) + 0x8C))], (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)(*((u16 *)((D_080CAAC6 + off) + 4)))) << 5), 0x1A0, 0x10);
    postDisplaySprite(1, (const void *)D_0863C084, (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)(*((u16 *)((D_080CAAC6 + off) + 6)))) << 5), 0x120, 0x10);
    drawDecimal(*((s16 *)(((u8 *)spC) + 0x2FC)), 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + a) + (b * 2));
    {
      s32 w = divideInt((*((u16 *)(((u8 *)spC) + 0xAC))) * 1000, 0x3D4);
      drawDecimal(moduloInt(w, 10), 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + c) + (d * 2));
      drawDecimal(divideInt(w, 10), 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + c) + ((d - 2) * 2));
      {
        u32 z = formatPlayTime(*((u32 *)(((u8 *)spC) + 0x90)));
        drawDecimal((z >> 16) & 0xFF, 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + e) + ((f - 6) * 2));
        drawPaddedDecimal((z >> 8) & 0xFF, 2, 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + e) + ((f - 3) * 2));
        drawPaddedDecimal(z & 0xFF, 2, 0x5157, ((((D_02023132 & 0x1F00) << 3) + vramBase) + e) + (f * 2));
      }
    }
    sub_0800BDBC(((u8 *)spC) + 1, ((u8 *)arg2) + (sp10 * 0x300), (vramBase + ((D_02023132 & 0xC) << 12)) + (((u32)t) << 5));
  }
}
