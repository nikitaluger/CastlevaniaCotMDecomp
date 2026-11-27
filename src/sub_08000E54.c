extern const u32 D_080C420C[];
void sub_08000DF8(void *a, void *b, void *c, u32 d);
u32 divInt32(u32 a, u32 b);

/* Queue a VRAM transfer as a pool node: build the control word
 * 0x81000000 | D_080C420C[unit >> 5] (size-class bits) | size / (unit >> 3)
 * and hand it, with the node type, payload word and destination, to the
 * node allocator. */
volatile int sub_08000E54(void *type, void *payload, void *dst, u32 size, u32 unit)
{
  u32 control;
  s32 sunit;
  sunit = (s32) unit;
  control = 0x81000000U;
  control |= D_080C420C[sunit >> 5];
  control |= divInt32(size, (u32) (sunit >> 3));
  sub_08000DF8(type, payload, dst, control);
}
