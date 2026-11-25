/* Find an entry by its id in the object table: pass the table's end pointer
 * (stored at 0x02025B7C), biased back by one record, to the search helper. */
extern s32 D_02025B7C;
s32 sub_08001534(s32 id, s32 base);

volatile unsigned char sub_08001574(s32 id) {
    sub_08001534(id, D_02025B7C - 0xBC);
}
