/* Look up an entry whose id lies in [loId, hiId] in the object table: pass
 * the table's end pointer (stored at 0x02025B7C), biased back one record. */
extern s32 D_02025B7C;
s32 sub_08001588(s32 loId, s32 hiId, s32 base);

volatile unsigned short sub_080015CC(s32 loId, s32 hiId) {
    sub_08001588(loId, hiId, D_02025B7C - 0xBC);
}
