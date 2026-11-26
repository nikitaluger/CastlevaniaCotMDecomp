extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u32 gTilemapPages[];
extern u16 D_020232FE;
extern u8 D_080E4764[];
extern u8 D_080E47E8[];
extern u32 D_0866EB64[];
extern void sub_08005E80(u32);
extern u16 sub_08007B3C(u32, u32, u32);
extern void sub_08061B90(u32, u32);
extern void sub_0806CD80(u8 *, u8 *, u8 *, u32 *);
extern void sub_0806D044(u8 *, u8 *, u32 *);
extern void sub_0806D7F4(void);
extern void sub_0806D81C(void);
extern void sub_0806D844(void);
extern void sub_0806D860(u32);
extern void sub_0806D894(void);
extern void sub_0806D8C0(void);
extern void sub_0806D930(u8 *);
extern void sub_0806DD94(void);
extern void sub_0808E3B8(u32, u32, u32);
extern void sub_0808E408(u32, u32, u32);
extern void sub_080C364C(u32, u32);
extern void sub_08085158(u8 *, u8 *, u32 *);
inline int inline_fn(u32 arg0, int arg1) { return arg0 & arg1; }
inline u16 inline_fn2(u16 *arg0) { return arg0[3]; }
inline u16 inline_fn23(u16 *arg0) { return arg0[6]; }
void sub_0806C6B0(u8 *a, u8 *b, u8 *c, u32 *d)
{
  u8 *g = gGameStatus;
  u8 *h = gMainWorkspace;
  u8 v18;
  u32 i;
  u32 j;
  u32 old;
u32 __repair_phase_old;
  u32 val;
  
  u32 idx2;
u32 __repair_phase_idx2;
  u32 idx2_1;
  u8 *tab;
  u16 *ph;
  u32 *ploop;
  u32 *pq;
  u32 *pr;
  v18 = a[0x18];
  { u32 *p = (u32 *)(c + 0x8C); if (*p) (*p)--; }
  switch (*((u32 *)(c + 0x9C))) {
    case 2: if ((--(*((u32 *)(c + 0xA0)))) == 0) sub_0806D894(); break;
    case 4: if ((--(*((u32 *)(c + 0xA0)))) == 0) sub_0806D8C0(); break;
  }
  { u32 *p = (u32 *)(c + 0x5C); if (*p) (*p)--; }
  sub_08061B90(d[0], d[1]);
  if (c[0x120] < g[0x3C4]) { c[0x120] = g[0x3C4]; sub_0806D930(g + 0x2C4); sub_0806D860(6); }
  if (c[0x121] < g[0x3C5]) { c[0x121] = g[0x3C5]; sub_0806D930(g + 0x2C4); *((u32 *)(c + 0x110)) = 100; }
  if (c[0x122] < g[0x3C6]) { c[0x122] = g[0x3C6]; sub_0806D930(g + 0x2C4); *((u32 *)(c + 0x114)) = 100; }
  idx2 = g[0x305];
  tab = (u8 *)(D_080E4764 + idx2 * 120);
  __repair_phase_old = g[0x304];
  tab += __repair_phase_old * 12;
  if ((h[0x14ED] != 0) && (v18 != 0x30)) {
    old = *((u32 *)(g + 0x2CC)); val = *((u32 *)tab);
    if (old >= val) *((u32 *)(g + 0x2CC)) = old - val;
    else { *((u32 *)(g + 0x2CC)) = 0; sub_0806DD94(); }
  }
  if ((v18 != 0x1C) && (v18 != 0x30)) { sub_080C364C((u32)((*((s16 *)(g + 0x2F0))) << 16), 0x1770); sub_0806D81C(); }
  { u32 *p = (u32 *)(c + 0x110); if (*p) { sub_080C364C(*((u32 *)(g + 0x2C8)), 100); sub_0806D7F4(); (*p)--; } }
  { u32 *p = (u32 *)(c + 0x114); if (*p) { sub_080C364C(*((u32 *)(g + 0x2D0)), 100); sub_0806D81C(); (*p)--; } }
  if (((g[0x94] == 0x0E) && (g[0x95] != 0)) && (v18 != 0x1C)) { sub_080C364C(*((u32 *)(g + 0x2D0)), 100); sub_0806D844(); }
  {
    int flag = 0;
    s32 x = ((s32)(*((u32 *)(g + 0x2C4)))) >> 8;
    u16 y;
    if ((x * 100) <= ((((s32)(*((u32 *)(g + 0x2C8)))) >> 8) * 25)) flag = 1;
    g[0x2DA] = flag;
    y = 0x2DB;
    idx2 = g[0x305] - 1; __repair_phase_idx2 = g[0x304] - 1;
    if (g[0x316 + idx2] == 0 || g[0x30C + __repair_phase_idx2] == 0) goto skip2;
    __repair_phase_old = *((u32 *)(g + 0x2CC)); val = *((u32 *)(tab = (u8 *)(D_080E47E8 + (4 + (__repair_phase_idx2 * 12 + idx2 * 120)))));
    if (val > __repair_phase_old) goto set1;
skip2:
    if (!(((s32)(*((u32 *)(g + 0x2CC)))) > 0xFFFF))
    {
set1:
    g[0x2DB] = 1; sub_0806DD94();
;
    }
    else
    { g[y] = 0;
      ;
    }
  }
  *((u32 *)(c + 0x44)) = 0;
  *(c + 0xAC) = 0;
  { u16 r = sub_08007B3C((u32)(gTilemapPages + h[0x18A8] * 0x10), d[0], d[1] - 0x40000);
    s32 v = r & 0x3F;
    if (v == 0x0A) *((u32 *)(c + 0x44)) = 1;
    if ((g[0x3CF] == 0) && (g[0x3CC] != 0)) g[0x3CF] = 1;
    if ((h[0x14ED] != 0xA9) && ((j = g[0x3CC]) == 0)) *((u32 *)(c + 0xAC)) = 1; }
  if (h[0x14ED] == 0xA7) *((u32 *)(c + 0x44)) = 4;
  if (*((s16 *)(h + 0x18BC)) != 0) *((u32 *)(c + 0x44)) = 2;
  { u16 r = sub_08007B3C((u32)(gTilemapPages + h[0x18A8] * 0x10), d[0], d[1] - 0x40000);
    u32 v = r & 0x3F;
    if (v == 0x16) {
      if (((((u8)(v18 - 6)) <= 1) || (v18 == 0x25)) || (v18 == 0x2A)) {
        if (inline_fn(*((u32 *)(c + 0x118)), 7) == 0) sub_0808E3B8(d[0], inline_fn(d[1], 0xFFF80000), 0);
        if ((v18 == 6) || (a[0x18] == 0x25)) { if (((*((u32 *)(c + 0x118))) & 0x1F) == 0) sub_08005E80(0x1BD); }
        if ((a[0x18] == 7) || (a[0x18] == 0x2A)) { if (((*((u32 *)(c + 0x118))) & 0x0F) == 0) sub_08005E80(0x1BD); }
        (*((u32 *)(c + 0x118)))++;
      } else *((u32 *)(c + 0x118)) = 0;
    } else *((u32 *)(c + 0x118)) = 0; }
  { u16 r = sub_08007B3C((u32)(gTilemapPages + h[0x18A8] * 0x10), d[0], d[1] - (*((u32 *)(c + 0x3C))));
    u32 *p11C = (u32 *)(c + 0x11C);
    if ((r & 0x3F) == 0x17) {
      if ((*p11C) == 0) { u32 v2 = (d[1] - (*((u32 *)(c + 0x3C)))) & 0xFFF80000;
        if (g[0x3CF] == 0) sub_0808E408(d[0], v2, 0x1000); else sub_0808E408(d[0], v2, 0);
        *p11C = 1;
        if (((s32)d[3]) >= 0) sub_08005E80(0x1BC); }
    } else *p11C = 0; }
  ploop = (u32 *)(c + 0xE0); pq = (u32 *)(c + 0xD0); pr = (u32 *)(c + 0xF0);
  for (i = 0; ploop <= ((u32 *)(c + 0xEC)); ploop++, pq++, pr++, i += 4) {
    u16 mask = inline_fn(D_020232FE, 0xF0);
    u16 *ap = (u16 *)((u32)(((*ploop) << 1) + (u32)*((u32 **)((u8 *)D_0866EB64 + i))));
    if ((*ap) == mask) {
      *ploop = (*ploop) + 1; *pr = 13;
      if ((*((u16 *)((u32)(((*ploop) << 1) + (u32)*((u32 **)((u8 *)D_0866EB64 + i)))))) == 0) *pq = 13;
    }
    if (*pr) { if ((--(*pr)) == 0) *ploop = 0; }
    if (*pq) (*pq)--;
  }
  sub_08085158(a, c, d);
  { u16 v = *((u16 *)(h + 0x14E2));
    if (v == 0) { *((u32 *)(h + 0x14E4)) = 0; *((u32 *)(h + 0x14E8)) = 0; }
    else { u32 *pE8 = (u32 *)(h + 0x14E8);
      if ((*pE8) == 0) { sub_08005E80(v); *((u32 *)(h + 0x14E8)) = 0; *pE8 = *((u32 *)(h + 0x14E4)); }
      else (*pE8)--; } }
  *((u16 *)(h + 0x14E2)) = 0;
  sub_0806CD80(a, b, c, d);
  if (*((u32 *)(h + 0x14BC))) sub_0806D044(a, c, d);
  *((u32 *)(h + 0x1728)) = d[0];
  *((u32 *)(h + 0x172C)) = d[1];
  ph = (u16 *)(*((u32 *)(c + 0x12C)));
  *((u16 *)(h + 0x1730)) = inline_fn2(ph);
  *((u16 *)(h + 0x1732)) = ph[4];
  *((u16 *)(h + 0x1734)) = ph[5];
  *((u16 *)(h + (val = 0x1736))) = inline_fn23(ph);
  *((u16 *)(h + 0x1738)) = *(b + 2);
  *((u8 *)(h + 0x173A)) = a[0x18];
  *((u32 *)(h + 0x173C)) = *((u32 *)(c + 0x70));
  *((u32 *)(h + 0x1740)) = *((u32 *)(c + 0x40));
  *((u32 *)(h + 0x1508)) = *((u32 *)(g + 0x300));
  idx2_1 = (u32)(inline_fn23(ph) << 16);
  *((u32 *)(h + 0x174C)) = d[0];
  *((u32 *)(h + 0x1750)) = d[1] + idx2_1;
  j = *((u32 *)(h + 0x1718));
  *((u32 *)((h + 0x1518) + (j * 4))) = d[0];
  *((u32 *)((h + 0x1618) + (j * 4))) = d[1];
  *((u32 *)(h + 0x1718)) = 1;
  *((u32 *)(h + 0x1718)) = (j + (*((u32 *)(h + 0x1718)))) & 0x3F;
}
