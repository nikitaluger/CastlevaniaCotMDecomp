extern void sub_0805F0C8(u16);
extern void sub_080C31E0(void *, s32);
struct GameState
{
  u8 _0[0xF0 * 4];
  u16 mode;
};
extern struct GameState D_02025368;
extern u8 D_08100A7E[];

// Script step: clear a sprite flag and a work byte, spawn the effect whose
// graphics id is looked up from D_08100A7E by game mode and animation variant,
// then dispatch the entity's next script state.
void sub_08095C68(u8 *entity)
{
  u8 *sprite = *((u8 **) (entity + 0x38));
  u8 *variantSrc = *((u8 **) (entity + 0xAC));
  u8 *work = *((u8 **) (entity + 0x3C));
  u8 flags;
  s32 tableOffset;
  u16 variant;
  u8 *effectTable;
  u32 variantIndex;
  flags = (*((u8 *) (sprite + 0x2A))) & 0xBF;
  variant = 0;
  *((u8 *) (sprite + 0x2A)) = flags;
  *((u8 *) ((*((u8 **) (work + 0x28))) + 1)) = variant;
  switch (D_02025368.mode)
  {
    case 1:
      tableOffset = 0;
      effectTable = D_08100A7E;
      break;

    case 2:
      tableOffset = 1;
      effectTable = D_08100A7E;
      break;

    case 0x200:
      tableOffset = 2;
      effectTable = D_08100A7E;
      break;

    default:
      tableOffset = 3;
      effectTable = D_08100A7E;
      break;

  }
  tableOffset <<= 1;
  variant = *((u16 *) ((*((u8 **) (variantSrc + 4))) + 6));
  variantIndex = 0xF;
  variantIndex &= variant;
  tableOffset += variantIndex * 8;
  tableOffset = tableOffset + (s32)effectTable;
  sub_0805F0C8(*(u16 *)tableOffset);
  sub_080C31E0(entity, *((s32 *) (entity + 0x24)));
}
