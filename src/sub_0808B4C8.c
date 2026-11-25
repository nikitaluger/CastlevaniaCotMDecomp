extern void sub_080057C8(s32);
extern void sub_0806D8E4(void *);

struct Entry {
  u8 b0, b1;
  u8 pad2[0xA];
  u8 bC, bD, bE, bF, b10, b11, b12, b13, b14, b15;
  u16 h16;
  u8 b18;
};
extern u8 D_080E6988[];

struct S25368 {
  u8 _0[0x94];
  u8 f94, f95;
  u8 _96[0x2D8 - 0x96];
  u8 f2D8;
  u8 _2D9[0x2FC - 0x2D9];
  u16 f2FC;
  u8 _2FE[0x304 - 0x2FE];
  u8 f304, f305;
  u8 _306[0x3C7 - 0x306];
  u8 f3C7, f3C8, f3C9, f3CA, f3CB, f3CC, f3CD, f3CE;
};
extern struct S25368 D_02025368;

struct S_02025FF0 { u8 _0[0x0A]; u8 bA; u8 _B[5]; s32 w10; };
extern struct S_02025FF0 D_02025FF0;

/* Copies the parameter entry selected by a 4-bit index in the word just before
 * the stat block from D_080E6988 into the player's stats, recomputes derived
 * stats, then sets global flags and seeds a global value. */
void sub_0808B4C8(void)
{
  struct S25368 *stats = &D_02025368;
  u8 *header = (u8 *)stats - 0x10;
  s32 entryIndex = header[0xC] & 0xF;
  struct Entry *entry = (struct Entry *)(D_080E6988 + entryIndex * 7 * 4);

  stats->f94 = entry->b0;
  stats->f95 = entry->b1;
  stats->f3C7 = entry->bC;
  stats->f3C8 = entry->bD;
  stats->f3C9 = entry->bE;
  stats->f3CA = entry->bF;
  stats->f3CB = entry->b10;
  stats->f3CC = entry->b11;
  stats->f3CD = entry->b12;
  stats->f3CE = entry->b13;
  stats->f304 = entry->b14;
  stats->f305 = entry->b15;
  stats->f2FC = entry->h16;
  stats->f2D8 = entry->b18;

  sub_0806D8E4((u8 *)stats + 0x2C4);
  D_02025FF0.bA = 1;
  sub_080057C8(0x36F);
  D_02025FF0.w10 = 0;
}
