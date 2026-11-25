extern u8 D_02025368[];

/* Read one byte from the 10x10 tile grid at D_02025368+0x320; row and column
 * are 1-based byte coordinates. */
u8 sub_08086E78(u32 row, u32 col) {
    u32 rowIndex;
    u32 columnIndex;
    u32 index;
    u32 base;

    rowIndex = (row << 24) >> 24;
    columnIndex = (col << 24) >> 24;
    base = (u32)D_02025368;
    rowIndex -= 1;
    index = rowIndex << 2;
    index = index + rowIndex;
    index = index << 1;
    index = index - 1;
    columnIndex = columnIndex + index;
    rowIndex = 0xC8;
    rowIndex = rowIndex << 2;
    base = base + rowIndex;
    columnIndex = columnIndex + base;
    return *(u8 *)columnIndex;
}
