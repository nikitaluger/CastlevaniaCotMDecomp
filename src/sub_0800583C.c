extern s32 scaleByRandom(s32);

/* Return a pseudo-random signed offset in [-range, range): scale the next
 * random fraction over 2*range, then subtract range to centre it on zero. */
s32 sub_0800583C(s32 range) {
    return scaleByRandom(range * 2) - range;
}
