extern s32 sub_0806D518(void *, void *, void *);
extern void sub_080719EC(void *, void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_08005E80(s32);
extern void sub_0806D588(void *, void *);
extern void sub_0806D2F8(void *, void *);
extern u8 D_02025FF0[];

struct StatePair { u32 unused; s32 posX; };

/* Updates one object: checks it against the view's bounds (killing it if it
 * has left the active area), advances its position/velocity and timers, then
 * refreshes its contact state and parent. */
void sub_0806FCA8(void *arg0)
{
    struct StatePair *state = *(struct StatePair **)((u8 *)arg0 + 0x6C);
    u8 *object = (u8 *)state + 4;
    u8 *parent = *(u8 **)((u8 *)arg0 + 0x38);
    u8 *objectData = object;

    if (sub_0806D518(arg0, parent, objectData) != 0)
        return;
    sub_080719EC(arg0, objectData, objectData);

    if (*(s32 *)(objectData + 0x10) == 0) {
        u8 *base = D_02025FF0;
        s32 *centerXPtr = (s32 *)(base + 0x1728);
        s16 hx = *(s16 *)(base + 0x1734);
        s32 minX = *centerXPtr + ((s32)(hx - *(s16 *)(base + 0x1730)) << 16);
        s32 maxX = *centerXPtr + ((s32)(hx + *(s16 *)(base + 0x1730)) << 16);
        s32 *centerYPtr = (s32 *)(base + 0x172C);
        s16 hy = *(s16 *)(base + 0x1736);
        s32 minY = *centerYPtr + ((s32)(hy - *(s16 *)(base + 0x1732)) << 16);
        s32 maxY = *centerYPtr + ((s32)(hy + *(s16 *)(base + 0x1732)) << 16);
        if (minX < state->posX && maxX > state->posX &&
            minY < *(s32 *)(objectData + 4) && maxY > *(s32 *)(objectData + 4)) {
            sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
            return;
        }
    } else {
        *(s32 *)(objectData + 0x10) -= 1;
    }
    {
        s32 velocity = *(s32 *)(objectData + 8) + *(s32 *)(object + 0x48);
        *(s32 *)(objectData + 8) = velocity;
        *(s32 *)(objectData + 0) += velocity;
    }
    sub_08003740(object + 0x2C, parent);
    {
        s32 remaining = *(s32 *)(objectData + 0x14) - 1;
        *(s32 *)(objectData + 0x14) = remaining;
        if (remaining == 0) { sub_08005E80(0x91); *(s32 *)(objectData + 0x14) = 10; }
    }
    sub_0806D588(parent, objectData);
    sub_0806D2F8(arg0, parent);
}
