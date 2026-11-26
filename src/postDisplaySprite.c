extern const u32 D_080C420C[];
void sub_08000DF8(void *a, void *b, void *c, u32 d);
u32 sub_080C364C(u32 a, u32 b);

/* Post a pooled display effect: build the attribute word from the base flag,
 * the category-table entry and value/(category>>3), then store it together
 * with the two coordinate words in the pool list selected by listKey. */
volatile int postDisplaySprite(void *listKey, void *x, void *y, u32 value, u32 category)
{
  u32 attr;
  s32 cat;
  cat = (s32) category;
  attr = 0x80000000U;
  attr |= D_080C420C[cat >> 5];
  attr |= sub_080C364C(value, (u32) (cat >> 3));
  sub_08000DF8(listKey, x, y, attr);
}
