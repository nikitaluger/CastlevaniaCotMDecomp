struct MusicTrack {
    u8 pad[0x2F];
    u8 arg;                     /* +0x2F: current command argument */
    u8 pad2[0x40 - 0x30];
    u8 *cmdPtr;                 /* +0x40: command cursor */
};

/* Copy the next music-track command argument byte into the track's +0x2F field
 * and advance the command cursor. */
void sub_080C170C(void *unused, struct MusicTrack *track)
{
    u8 val = *track->cmdPtr;
    track->arg = val;
    track->cmdPtr++;
}
