extern u8 gGameStatus[];
void sub_080102F0(u8);
u8 sub_08010490(u8 *);

/* Load save slot `slot` into the save buffer and report whether it is valid:
 * non-empty and its stored checksum byte (block[9]) matches the computed one. */
s32 sub_080103F0(u8 slot) {
    u8 *saveBlock = gGameStatus;
    sub_080102F0(slot);
    if (*saveBlock != 0) {
        u8 checksum = sub_08010490(saveBlock);
        if (checksum == saveBlock[9]) return 1;
    }
    return 0;
}
