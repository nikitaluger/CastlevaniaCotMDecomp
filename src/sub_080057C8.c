extern vu32 D_0200A260; /* PRNG state, advanced by sub_080057F8 */
#define gRngState D_0200A260

/* Seed the game's pseudo-random number generator. */
void sub_080057C8(s32 seed) {
    gRngState = (u32)seed;
}
