struct S_02025FF0 { u8 _0[0x1754]; s32 f1754; u8 _1[0x1770-0x1758]; s32 f1770; s32 f1774; s32 f1778; s32 f177C; u8 _2[0x18A8-0x1780]; u8 f18A8; };
extern struct S_02025FF0 gMainWorkspace;
extern u8 D_02023130[];

/* Write the current scroll offsets into the active half of the offset table,
 * subtract them from the entity's world position, and apply the fractional
 * correction when the scroll flag is set; then fill the other half too. */
void sub_0806AA64(void *arg0, void *arg1) {
    struct S_02025FF0 *state = &gMainWorkspace;
    u8 *page = (u8 *)(0x18A8 + (u32)state);
    u8 *offsets;
    s32 *dst;
    s32 yOff;
    s32 flag;
    u32 off;

    off = *page << 6;
    offsets = D_02023130;
    dst = (s32 *)(off + (u32)offsets);
    dst[6] = state->f1770;
    yOff = state->f1774;
    dst[7] = yOff;
    flag = state->f1754;
    if (flag != 0) {
        flag &= 2;
        dst[7] = yOff + (flag << 16);
        state->f1754--;
    }
    *(s32 *)((u8 *)arg0 + 0x14) = (*(s32 *)arg1 & 0xFFFF0000) - dst[6];
    *(s32 *)((u8 *)arg0 + 0x18) = (*(s32 *)((u8 *)arg1 + 4) & 0xFFFF0000) - dst[7];
    off = (1 ^ *page) << 6;
    dst = (s32 *)(off + (u32)offsets);
    dst[6] = state->f1778;
    dst[7] = state->f177C;
}
