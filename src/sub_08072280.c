extern u8 D_0866EE14[];
extern u8 D_0866EE18[];

/* Approximate the 64-step angle of the vector from (x0,y0) to (x1,y1): fold the
 * deltas into a 4-bit direction index, look up the 16x16 octant table, mirror
 * it for the left half-plane, and add the quadrant base. */
u8 sub_08072280(s32 x0, s32 y0, s32 x1, s32 y1) {
  s32 dx;
  s32 dy;
  u8 quad;
  u16 idx;
  u8 t;
  quad = 0;
  dx = x1 - x0;
  if (dx < 0) {
    dx = -dx;
    quad = 1;
  }
  dy = y1 - y0;
  if (dy < 0) {
    dy = -dy;
    quad += 2;
  }
  while ((dx > 0xF) || (dy > 0xF)) {
    dx >>= 1;
    dy >>= 1;
  }

  idx = D_0866EE18[dx + (dy * 0x10)];
  t = quad - 1;
  if (t <= 1) {
    idx = 0x40 - idx;
  }
  return D_0866EE14[quad] + (u8)idx;
}
