extern s32 getAngleFromDelta(s32, s32);
extern s32 fixedPointDistance(s32, s32);
extern void setPolarOffset(void *, s32, s32);
extern s32 sub_08014CA0(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 divInt32(s32);
struct MoveA { u8 pad[8]; s32 x, y, vx, vy; };
struct MoveB { s32 cur, prev, min, max, step, speed, pad, unused; };

void sub_08014B1C(struct MoveA *a, struct MoveB *b, s32 c, s32 d)
{
    s32 angle = getAngleFromDelta(d - a->y, c - a->x);
    s32 dist = fixedPointDistance(c - a->x, d - a->y);
    s32 delta = (angle - b->prev) & 0xFFFF;
    s32 v;
    if (b->speed == 0) return;
    if (delta == 0) v = 0;
    else {
        s16 s = (s16)delta;
        s32 t = s < 0 ? -((s16)delta) : s;
        v = divInt32(t - 1) + 1;
    }
    if (v == 1) {
do { b->prev = angle; delta = 0;
} while (0);
}
    if (delta == 0) {
        s32 lim = b->cur + b->step;
        if (lim > b->max) lim = b->max;
        if (dist > lim) {
            setPolarOffset(a, b->prev, lim);
            b->cur = fixedPointDistance(a->vx, a->vy);
            return;
        }
        if (dist >= b->cur) {
            a->vx = c - a->x;
            a->vy = d - a->y;
        } else {
            s32 low = b->cur - b->step;
            if (low < b->min) low = b->min;
            if (dist < b->min) {
                setPolarOffset(a, b->prev, low);
                b->cur = fixedPointDistance(a->vx, a->vy);
                return;
            }
            a->vx = c - a->x;
            a->vy = d - a->y;
        }
    } else {
        s32 target;
        if (delta <= 0x7FFF) angle = b->prev + b->speed;
        else angle = b->prev - b->speed;
        if (sub_08014CA0(a->x, a->y, b->cur, b->speed, b->prev, c, d, delta) == 1) {
            s32 lim = b->cur + b->step;
            if (lim > b->max) lim = b->max;
            if (sub_08014CA0(a->x, a->y, lim, b->speed, b->prev, c, d, delta) == 1) {
                target = lim;
                setPolarOffset(a, angle, target);
            } else setPolarOffset(a, angle, b->cur);
        } else {
            s32 target;
            target = b->cur - b->step;
            if (target < b->min) target = b->min;
            setPolarOffset(a, angle, target);
        }
        b->prev = angle;
    }
    b->cur = fixedPointDistance(a->vx, a->vy);
}
