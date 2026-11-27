extern void sub_080C31E8(void *base, void *index, u16 value, s32 table);
extern u8 gMenuState[];
extern u16 D_080CAFC0[];

/* Clear the current script step's flag byte and advance the script with the
 * song id for the current area (area id at EWRAM 0x020278D0+0x64, looked up in
 * the area-to-song table D_080CAFC0). */
void sub_0800D030(void *actor) {
    u8 *self = (u8 *)actor;
    s32 *stepTable;
    u8 *script, *stepIndex;
    u8 *state;
    u16 *areaSongs;
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    stepTable = (s32 *)0x08671BD0;
    script = self + 0x18;
    stepIndex = self + 0x22;
    areaSongs = D_080CAFC0;
    state = gMenuState;
    state += 0x64;
    sub_080C31E8(script, stepIndex, areaSongs[*state], *stepTable);
}
