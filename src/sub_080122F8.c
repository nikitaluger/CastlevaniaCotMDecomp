s32 sub_08005910(s32, s32);
void sub_0801235C(s32, s32 *, s32 *, s32 *);

/* A segment's two endpoints step along their paths; store the midpoint and
 * the direction angle pointing back from the second endpoint to the first. */
struct Segment {
    s32 mode;
    s32 angle;
    s32 x0;
    s32 y0;
    s32 x1;
    s32 y1;
    s32 step0;
    s32 step1;
};

void sub_080122F8(struct Segment *arg0, struct Segment *arg1) {
    sub_0801235C(arg1->mode, &arg1->step0, &arg1->x0, &arg1->y0);
    sub_0801235C(arg1->mode, &arg1->step1, &arg1->x1, &arg1->y1);
    arg0->x0 = (arg1->x0 + arg1->x1) / 2;
    arg0->y0 = (arg1->y0 + arg1->y1) / 2;
    arg1->angle = (sub_08005910(arg1->y1 - arg1->y0, arg1->x1 - arg1->x0) + 0xC000) & 0xFFFF;
}
