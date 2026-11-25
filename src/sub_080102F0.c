extern void *D_02021E80;
extern u8 D_02025368[];
extern void sub_080C2F88(s32, s32, s32);

/* Copy a 0x3D0-byte record from the template at D_02025368 into slot index
 * of the block pointed to by D_02021E80 (records start at +0x10). */
void sub_080102F0(u8 index) {
    void **pp = &D_02021E80;
    u32 r = index;
    u32 off;
    off = r << 4;
    off -= r;
    off <<= 2;
    off += r;
    off <<= 4;
    off += 0x10;
    sub_080C2F88((s32)((u8 *)*pp + off), (s32)D_02025368, 0x3D0);
}
