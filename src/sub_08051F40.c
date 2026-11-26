s32 divideInt(s32, s32); /* BIOS Div: signed division */

/* Per-axis motion path: nine points, each with a start/end position and step. */
struct MotionPath {
    u8 p10[0x10];
    s32 xStep[9];   /* 0x10 */
    s32 yStep[9];   /* 0x34 */
    u8 p58[8];
    s32 xStart[9];  /* 0x60 */
    s32 yStart[9];  /* 0x84 */
    u8 pA8[8];
    s32 xEnd[9];    /* 0xB0 */
    s32 yEnd[9];    /* 0xD4 */
};

/* Precompute each point's x/y step as (end - start) / duration. */
void sub_08051F40(struct MotionPath *path, s32 duration) {
    u32 i;
    for (i = 0; i <= 8; i++) {
        path->xStep[i] = divideInt(path->xEnd[i] - path->xStart[i], duration);
        path->yStep[i] = divideInt(path->yEnd[i] - path->yStart[i], duration);
    }
}
