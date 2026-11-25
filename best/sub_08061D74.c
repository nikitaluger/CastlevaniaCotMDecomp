struct S_02025368_61 { u8 pad[0xB0]; u32 words[8]; };
extern struct S_02025368_61 D_02025368;

s32 sub_08061D74(u32 arg0) {
    u32 *words = D_02025368.words;
    u32 mask = 1u << (arg0 & 0x1F);
    if (words[arg0 >> 5] & mask) return 1;
    return 0;
}
