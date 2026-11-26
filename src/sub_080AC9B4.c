s32 moduloInt(s32, s32);
void sub_080B0778(void);

struct S3 { u32 a, b, c; };

/* Every N frames (N from the interval table indexed by kind), spawn a random on-screen effect. */
void sub_080AC9B4(u32 kind, u32 *state) {
    struct S3 intervals;
    u32 indexShifted = kind << 24;
    u32 count;
    intervals = *(struct S3 *)0x0810224C;
    count = ++state[5];
    if (moduloInt(count, *(u32 *)((u8 *)&intervals + (indexShifted >> 22))) == 0) {
        sub_080B0778();
    }
}
