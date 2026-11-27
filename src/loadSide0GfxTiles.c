extern u8 gCameraState[];
extern u8 gGfxTileBuffer[];
extern u8 gGfxTileBufferShifted[];
extern u32 gTileSourceTable[];
extern void decode2bppTiles(u8, u8, u8, u8 *, u8 *);
extern void uploadGfxTilesToVram(void);
inline u8 *inline_fn(int arg0)
{
  return gCameraState + arg0;
}

static inline u32 and1(u32 b)
{
  u32 m = 1;
  m &= b;
  return m;
}

void loadSide0GfxTiles(u16 arg0)
{
  u32 r6 = arg0;
  u8 *base = gCameraState;
  u32 r7;
  u32 i;
  if (and1(gCameraState[0x1443]))
  {
    u8 *src;
    u8 *dst;
    i = 0;
    src = inline_fn(0x13F8);
    dst = inline_fn(0x13B8);
    for (; i <= 15; i++)
    {
      dst[0] = src[0];
      dst[1] = src[1];
      src += 4;
      dst += 4;
    }

    r7 = 0x80;
    {
      s32 sr6 = (s32) r6;
      if (sr6 > 1)
      {
        goto set_calls;
      }
      if (sr6 < 0)
      {
        goto set_calls;
      }
    }
    {
      u8 *d1;
      u8 *d2;
      u8 *valp;
      i = 0;
      valp = inline_fn(0x1439);
      d1 = inline_fn(0x13F8);
      d2 = inline_fn(0x13BA);
      for (; i <= 15; i++)
      {
        d2[0] = ((*valp) << 4) | (*valp);
        d2[1] = ((*valp) << 4) | (*valp);
        d1[0] = ((*valp) << 4) | (*valp);
        d1[1] = ((*valp) << 4) | (*valp);
        d1[2] = ((*valp) << 4) | (*valp);
        d1[3] = ((*valp) << 4) | (*valp);
        d1 += 4;
        d2 += 4;
      }

    }
    goto after_inner;
    set_calls:
    {
      u32 *table = gTileSourceTable;
      s32 idx = r6 - 2;
      u32 *tbl = table + idx;
      decode2bppTiles(2, 0x10, 0, (u8 *) tbl[0], gGfxTileBufferShifted);
      decode2bppTiles(2, 0x10, 4, (u8 *) tbl[0], gGfxTileBufferShifted + 0x3E);
      decode2bppTiles(2, 0x10, 0, (u8 *) (tbl[0] + 0x10), gGfxTileBufferShifted + 0x40);
    }
  }
  else
  {
    u8 *valp;
    u8 *dst;
    i = 0;
    valp = base + 0x1439;
    dst = base + 0x13FA;
    {
      for (; i <= 15; i++)
      {
        dst[0] = ((*valp) << 4) | (*valp);
        dst[1] = ((*valp) << 4) | (*valp);
        dst += 4;
      }
    }
    r7 = 0x40;
    {
      s32 sr6 = (s32) r6;
      if (sr6 > 1)
      {
        goto clr_calls;
      }
      if (sr6 < 0)
      {
        goto clr_calls;
      }
    }
    {
      u8 *d;
      u8 *valp2;
      i = 0;
      d = gGfxTileBuffer;
      valp2 = d + 0x81;
      for (; i <= 0x7F; i++)
      {
        *((u8 *)(i + (u32)d)) = ((*valp2) << 4) | (*valp2);
      }

    }
    goto after_inner;
    clr_calls:
    {
      u32 *table = gTileSourceTable;
      s32 idx = r6 - 2;
      u32 *tbl = table + idx;
      u8 *dest;
      decode2bppTiles(4, 0x10, 0, (u8 *) tbl[0], dest = gGfxTileBuffer);
      decode2bppTiles(2, 0x10, 0, (u8 *) (tbl[0] + 0x10), dest + 0x40);
    }

  }
  after_inner:
  if (r6 != 0)
  {
    uploadGfxTilesToVram();
  }

  gCameraState[0x1443]++;
  {
    u32 *counter = (u32 *)inline_fn(0x1448);
    u32 value = *counter;
    value += r7;
    *counter = value;
  }
}
