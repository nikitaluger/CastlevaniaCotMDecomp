extern u16 gCrossfadeGfxState;

/* Clear bit 12 of the global display/fade state word. */
void sub_08003520(void) {
    gCrossfadeGfxState &= 0xEFFF;
}
