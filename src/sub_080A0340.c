extern void sub_08097EF4(s32, s32, s32, s32);
extern void sub_08097F70(s32, s32);
extern u16 D_0866FDE4[];
extern u8 D_080CDAA8[];
extern u8 D_020279F0[];

/* Select the actor's appearance variant: store its asset index, publish it in
 * the global palette state and load the variant's palette and graphics pair. */
void sub_080A0340(void *arg0, s32 variant) {
    u8 *self;
    u8 *assets;
    u8 *assets2;
    u16 *entry;
    u16 *palState;
    u16 assetIndex;
    u32 table;

    self = (u8 *)arg0;
    self[0x6C] = (u8)variant;
    palState = (u16 *)D_020279F0;
    table = (u32)D_0866FDE4;
    entry = (u16 *)(table + (u32)(variant << 1));
    assetIndex = *entry;
    palState[3] = assetIndex;
    assets = D_080CDAA8;
    sub_08097EF4(0, *(s32 *)(assets + (u32)((*entry) << 4)), 3, 1);
    {
        u16 assetIndex2;
        u32 assetOffset;
        assetIndex2 = *entry;
        assetOffset = (u32)(assetIndex2 << 4);
        assets2 = assets + 4;
        sub_08097F70(*(s32 *)(assets2 + assetOffset), 3);
    }
}
