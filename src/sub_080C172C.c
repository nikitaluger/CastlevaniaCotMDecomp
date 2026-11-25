/* Command-stream reader: copy the next byte from the track's cursor at +0x40
 * into its field at +0x1F, then advance the cursor. */
struct Track {
    u8 pad[0x1F];
    u8 field1F;
    u8 pad2[0x40 - 0x20];
    u8 *cursor;
};

void sub_080C172C(void *unused, struct Track *track) {
    u8 *cursor = track->cursor;
    u8 value = cursor[0];
    track->field1F = value;
    cursor = cursor + 1;
    track->cursor = cursor;
}
