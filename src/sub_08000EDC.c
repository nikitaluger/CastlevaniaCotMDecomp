s32 divInt32(s32, s32);

/* Large shared work area; +0x00 is its state word and 0x53C..0x548 a 4-word
 * parameter block for a posted display effect. */
extern u32 gCameraState[];
/* Per-category attribute bits, indexed with (arg4 >> 5). */
extern u32 D_080C420C[];

/* Post a display-effect parameter block into the shared work area: flag the
 * area active, compose its attribute word from the fixed base, the category
 * table entry and the quotient of value/scale (arg3 / (arg4 >> 3)), and store
 * the id, x and y arguments alongside it. */
s32 sub_08000EDC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    u32 *work;
    u32 attr;
    s32 quotient;

    work = gCameraState;
    work[0] |= 0x20000000;
    attr = 0xA2600000;
    attr |= D_080C420C[arg4 >> 5];
    quotient = divInt32(arg3, arg4 >> 3);
    attr |= quotient;
    *(u32 *)((u8 *)work + 0x53C) = arg1;
    *(u32 *)((u8 *)work + 0x540) = arg2;
    *(u32 *)((u8 *)work + 0x544) = attr;
    *(u32 *)((u8 *)work + 0x548) = arg0;
    return 0;
}
