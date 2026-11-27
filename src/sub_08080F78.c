extern s32 sub_0806D450(void *, void *, void *);
extern s32 divInt32(s32, s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_0808BB54(void);
extern void sub_080C31E0(void *, s32);
extern void stepDelayTimer(void *, void *);
extern void sub_08005E80(s32);

/* Counts down a timer that scales a value into a graphics object, drives a
 * hardware effect register, spawns periodic effects, and fires the entity
 * callback when the timer ends or state flags request it. */
void sub_08080F78(void *obj)
{
    void *extra = (void *)(*(u32 *)((u8 *)obj + 0x6C) + 4);
    void *gfx = *(void **)((u8 *)obj + 0x38);
    void *data = extra;
    u32 *words = (u32 *)data;
    s32 count;
    s32 divisor;
    s32 scaled;
    u16 *reg;
    u16 *reg2;
    void *spawned;
    u8 *state;

    if (sub_0806D450(obj, gfx, data) > 0) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    count = (s32)words[4] - 1;
    words[4] = count;
    divisor = 0x64;
    if (0x100 - count <= 0x31)
        divisor = (0x100 - count) * 2;
    if (count <= 0x13)
        divisor = (0x14 - count) * 5 + 0x64;
    scaled = divInt32(0x6400, divisor);
    *(u16 *)((u8 *)gfx + 4) = scaled;
    *(u16 *)((u8 *)gfx + 6) = scaled;
    if ((s32)words[4] > 0xE0) {
        divisor = ((s32)words[4] - 0xE0) >> 1;
        reg = (u16 *)0x03000830;
        reg[3] = (divisor << 8) | (0x10 - divisor);
    }
    if ((s32)words[4] <= 0x1F) {
        divisor = (s32)words[4] >> 1;
        reg2 = (u16 *)0x03000830;
        reg2[3] = ((0x10 - divisor) << 8) | divisor;
    }
    if ((words[4] & 7) == 0) {
        spawned = sub_0806D2A0(*(s32 *)((u8 *)obj + 0x28), 0x69, 0x0A, 0x12);
        if (spawned != 0)
            *(u32 *)((u8 *)spawned + 0x9C) = ((s32)words[4]) >> 3;
    }
    if (words[4] == 0) {
        sub_0808BB54();
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    state = (u8 *)0x02025FF0;
    *(u16 *)gfx = *(u16 *)(state + 0x18C2);
    stepDelayTimer((u8 *)extra + 0x1C, gfx);
    if (--words[5] == 0) {
        sub_08005E80(0x160);
        words[5] = 0x14;
    }
    if (*(u8 *)(state + 0x173A) == 0x1C || (*(u8 *)(state + 0x14ED) == 0 && *(u32 *)(state + 0x10) != 0))
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
}
