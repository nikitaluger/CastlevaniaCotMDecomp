extern u8 gMainWorkspace[];

extern s32 sub_08005820(s32);
extern s32 sub_0800583C(s32);
extern s32 sub_080C36E4(u32, s32);
extern void *sub_080918B0(s32, s32, s32, s32, s32, s16);
extern void sub_0808DC40(s32, s32, s32);
extern void _call_via_r1(void *, void *);

/* Randomizes a spawn position from the entity's field array, looks up a motion value
 * from the global table, spawns an effect, and once the script step passes 3 performs
 * a cleanup action and dispatches the entity's callback.
 */
void sub_0809153C(void *arg0) {
    s32 *fields = *(s32 **)((u8 *)arg0 + 0x3C);
    s32 spread = 0xC0000;
    s32 spawnX = fields[1] + sub_0800583C(spread);
    s32 spawnY = fields[2] + sub_0800583C(spread) + 0xFFF00000;

    u32 stateOff = 0x1898;
    u32 *stateVal = (u32 *)(gMainWorkspace + stateOff);
    s32 motion = (sub_080C36E4(*stateVal, 5) - 2) << 14;

    sub_080918B0(spawnX, spawnY, motion, 0x8000 - sub_08005820(0x20000), 0x16C1,
        (s16)((*stateVal - ((((s32)(*stateVal + (*stateVal >> 31)) >> 1) << 1))) + 1));

    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) > 3) {
        sub_0808DC40(fields[1], fields[2], 8);
        _call_via_r1(arg0, *(void **)((u8 *)arg0 + 0x24));
    }
}
