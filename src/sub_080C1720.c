struct MusicTrack {
    u8 pad[0x1E];
    u8 arg;                     /* +0x1E: current command argument */
    u8 pad1F[0x40 - 0x1F];
    u8 *cmdPtr;                 /* +0x40: command cursor */
};

/* Copy the next music-track command argument byte into the track's +0x1E field
 * and advance the command cursor. */
void sub_080C1720(void *unused, struct MusicTrack *track) {
    u8 *p = track->cmdPtr;
    u8 val = p[0];
    track->arg = val;
    p = p + 1;
    track->cmdPtr = p;
}
