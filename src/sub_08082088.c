extern s32 sub_0806D450(void *, void *, void *);
extern s32 sub_080C364C(s32, s32);
extern void *sub_0806D2A0(s32, s32, s32, s32);
extern void sub_0808BB54(void);
extern void sub_080C31E0(void *, s32);
extern void sub_08003740(void *, void *);
extern void sub_08005E80(s32);

/* Counts down a timer that scales a value written into a graphics object,
 * drives the hardware colour-blend register (0x03000830 halfword 3), spawns a
 * periodic effect, and fires the entity callback when the countdown ends or the
 * state flags request it. Twin of sub_08080F78 with different constants. */
void sub_08082088(void *obj)
{
    u8 *work = (u8 *)(*(u32 *)((u8 *)obj + 0x6C) + 4);
    u8 *gfx = *(u8 **)((u8 *)obj + 0x38);
    u8 *data = work;
    s32 *words = (s32 *)data;
    s32 count;
    s32 divisor;
    s32 fade;
    s32 off;
    s32 scaled;
    void *spawned;
    u8 *state;

    if (sub_0806D450(obj, gfx, data) > 0) {
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }

    count = words[4] - 1;
    words[4] = count;
    divisor = 0x64;
    fade = 0x100 - count;
    if (fade <= 0x31) divisor = fade * 2;
    if (count <= 0x13) {
        off = 0x14 - count;
        divisor = off * 5 + 0x64;
    }
    scaled = sub_080C364C(0x6400, divisor);
    *(s16 *)(gfx + 4) = scaled;
    *(s16 *)(gfx + 6) = scaled;
    if (words[4] > 0xE0) {
        u16 *blend;
        divisor = (words[4] - 0xE0) >> 1;
        blend = (u16 *)0x03000830;
        blend[3] = (u16)((divisor << 8) | (0x10 - divisor));
    }
    if (words[4] <= 0x1F) {
        u16 *blend;
        divisor = words[4] >> 1;
        blend = (u16 *)0x03000830;
        blend[3] = (u16)(((0x10 - divisor) << 8) | divisor);
    }
    if ((words[4] & 3) == 0) {
        spawned = sub_0806D2A0(*(s32 *)((u8 *)obj + 0x28), 0x6F, 0x0A, 0x12);
        if (spawned != NULL)
            *(s32 *)((u8 *)spawned + 0x9C) = words[4] >> 2;
    }
    if (words[4] == 0) {
        sub_0808BB54();
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
        return;
    }
    state = (u8 *)0x02025FF0;
    *(u16 *)gfx = *(u16 *)(state + 0x18C2);
    sub_08003740(work + 0x1C, gfx);
    words[5] -= 1;
    if (words[5] == 0) {
        sub_08005E80(0x161);
        words[5] = 0xC;
    }
    if (*(u8 *)(state + 0x173A) == 0x1C ||
        (*(u8 *)(state + 0x14ED) == 0 && *(s32 *)(state + 0x10) != 0))
        sub_080C31E0(obj, *(s32 *)((u8 *)obj + 0x24));
}
