extern volatile s32 gGameStatus[];
extern volatile s32 gSpriteKindTable[];

/* Add the score value (s32 at +8 of the 20-byte actor record selected by the
 * s16 at arg0+0x1C) to the player's score, capping it at 99,999,999. */
void sub_08013EEC(void *arg0) {
    u32 scoreOff = 0xC0 << 2;
    u32 kindOff = 0x1C;
    s32 *score = gGameStatus + scoreOff / 4;
    s32 *records = gSpriteKindTable;
    s16 kind = *(s16 *)((u8 *)arg0 + kindOff);
    s32 recOff = kind * 20;
    s32 *scoreField;
    s32 total;
    scoreField = (s32 *)((u8 *)records + 8);
    total = *score + *(s32 *)((u8 *)scoreField + recOff);
    *score = total;
    if (total > 0x05F5E0FF)
        *score = 0x05F5E0FF;
}
