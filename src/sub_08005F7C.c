extern void setSoundMode(u8 mode);
extern u8 *D_08106E38[];

/* Applies the sound-mode byte (header+3) of the song selected by `songId` from
 * the 8-byte-per-entry song table, when the song specifies a nonzero mode. */
void sub_08005F7C(u16 songId) {
    u8 *header = D_08106E38[(u32)songId * 2];
    u8 mode = header[3];
    if (mode) setSoundMode(mode);
}
