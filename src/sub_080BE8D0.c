struct FadeChannel {
    u8 pad[0x5C];
    s32 level;
};

/* Apply the current fade level (0 .. 0x10000) to a fade channel at +0x5C. */
void sub_080BE8D0(struct FadeChannel *channel, s32 level) {
    channel->level = level;
}
