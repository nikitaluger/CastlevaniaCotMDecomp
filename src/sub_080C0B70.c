extern void sub_080C0020(void *, s32);

/* Sound player stop: set the player's stop flag and silence the note chains of
 * every track (0x50 bytes apart), then re-arm the 0x68736D53 magic that marks
 * a valid, initialised player. */
void sub_080C0B70(void *arg0) {
    s32 ident = *(s32 *)((u8 *)arg0 + 0x34);
    if (ident == 0x68736D53) {
        s32 tracksLeft;
        s32 track;
        *(s32 *)((u8 *)arg0 + 0x34) = ident + 1;
        *(s32 *)((u8 *)arg0 + 4) |= 0x80000000;
        tracksLeft = *(u8 *)((u8 *)arg0 + 8);
        track = *(s32 *)((u8 *)arg0 + 0x2C);
        if (tracksLeft > 0) {
            do {
                sub_080C0020(arg0, track);
                tracksLeft--;
                track += 0x50;
            } while (tracksLeft > 0);
        }
        *(s32 *)((u8 *)arg0 + 0x34) = 0x68736D53;
    }
}
