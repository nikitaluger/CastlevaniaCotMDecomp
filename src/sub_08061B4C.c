extern s32 createChildObject(void *, s32);
extern u8 gGameStatus[];
extern u8 D_02027A00[];
extern u32 D_0866EB08[];

/* Convert the fixed-point map position (posX, posY) into a tile coordinate
 * using the active decoration pattern, store it as the room transition's
 * scroll destination (D_02027A00+0x12/+0x13) and spawn the transition object
 * as a child of `parent`. */
void sub_08061B4C(void *parent, s32 posX, s32 posY) {
    u8 *state = gGameStatus;
    u8 *patterns = (u8 *)D_0866EB08;
    u8 *scroll;
    u8 *tilePair;
    s32 tileX, tileY;
    u32 patternIdx = state[0x94] << 2;
    tilePair = *(u8 **)(patterns + patternIdx) + (state[0x95] << 1);
    tileX = (s8)((posX >> 24) + tilePair[0]);
    tileY = (s8)((posY >> 24) + tilePair[1]);
    scroll = D_02027A00;
    scroll[0x12] = tileX;
    scroll[0x13] = tileY;
    createChildObject(parent, 0x12);
}
