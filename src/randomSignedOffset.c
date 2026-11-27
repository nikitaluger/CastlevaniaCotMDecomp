extern s32 scaleByRandom(s32);

/* Return a pseudo-random signed offset in [-range, range): scale the next
 * random fraction over 2*range, then subtract range to centre it on zero. */
s32 randomSignedOffset(s32 range) {
    return scaleByRandom(range * 2) - range;
}
