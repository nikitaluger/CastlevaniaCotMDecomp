/* Clear bit 29 (0x20000000) of the global game-state flags word at 0x02021E90. */
#define GAME_STATE_FLAG_CLEAR_MASK 0xDFFFFFFF

void sub_08000F50(void) {
    *(s32 *)0x02021E90 &= GAME_STATE_FLAG_CLEAR_MASK;
}
