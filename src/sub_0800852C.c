/* Load sequence: each u16 of D_080CA8D0 packs two resource ids — the low byte
 * indexes D_0866CA98, the high byte indexes D_0866CAF8. Each 8-byte table entry
 * holds two descriptor pairs that are handed to decompressToVram. */
extern u16 D_080CA8D0[];
extern u8 D_0866CA98[];
extern u8 D_0866CAF8[];
extern void decompressToVram(void *, void *);

/* Advances the load cursor in state[1] and performs both resource loads for
 * that step. */
void sub_0800852C(u32 *state)
{
  u32 step;
  u16 packedIds;
  u32 idA;
  u32 idB;
  u32 offA;
  u32 offB;
  u8 *tableA;
  u8 *tableB;
  void *srcA;
  void *srcB;

  step = state[1] + 1;
  state[1] = step;
  packedIds = D_080CA8D0[step];
  idA = (u8) packedIds;
  idB = packedIds >> 8;
  step++;
  state[1] = step;
  tableA = D_0866CA98;
  offA = idA << 3;
  srcA = *((void **) (tableA + offA));
  tableB = D_0866CAF8;
  offB = idB << 3;
  srcB = *((void **) (tableB + offB));
  decompressToVram(srcA, srcB);
  decompressToVram(*((void **) ((D_0866CA98 + offA) + 4)), *((void **) ((D_0866CAF8 + offB) + 4)));
}
