struct MusicTrack {
    u8 pad[0x2C];
    u8 arg;                     /* +0x2C: last command argument */
    u8 pad2[0x40 - 0x2D];
    u8 *cmdPtr;                 /* +0x40: script command cursor */
};

/* Read the next command argument byte into the track's +0x2C field and advance
 * the command cursor. */
void sub_080C16D0(void *unused, struct MusicTrack *track)
{
    u8 val = *track->cmdPtr;
    track->arg = val;
    track->cmdPtr++;
}
