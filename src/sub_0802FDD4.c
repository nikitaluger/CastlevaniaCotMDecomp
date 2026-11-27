extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *gScriptStepCallbacks;
struct Counter { u8 _0[8]; u16 value; };
struct SCounter { u8 _0[8]; s16 value; };
struct Flags { u8 _0[0x6C]; u16 flags; };

/* Advance the actor's sprite and animation countdown; when it expires and
 * both related objects are clear, reroll the countdown and, if the target is
 * near the view, reset its script step and fire the callback. */
void sub_0802FDD4(u8 *arg0) {
    void *r7 = *(void **)(arg0 + 0x38);
    void *tmp = *(void **)(arg0 + 0xAC);
    u8 *r4 = *(u8 **)(arg0 + 0x3C);
    u8 *r8 = r4 + 0x34;
    u8 *r6 = r4 + 0x48;
    s32 v;
    if (*(u16 *)((u8 *)*(void **)((u8 *)tmp + 4) + 6) & 2) {
        sub_080149A4((s32)r7, r4, r4 + 0x52, 0x3C, 0x5A);
    }
    setAnimationFrame((s32)r7, r8, 0, 1);
    v = ((struct Counter *)r6)->value - 1;
    ((struct Counter *)r6)->value = v;
    if ((v << 0x10) < 0) {
        if ((((struct Flags *)*(void **)(r4 + 0x48))->flags & 4) == 0 &&
            (((struct Flags *)*(void **)(r6 + 4))->flags & 4) == 0) {
            ((struct Counter *)r6)->value = scaleByRandom(0x1F) + 0x50;
            if (absXFromFocus(*(s32 *)(r4 + 8)) <= 0x600000 &&
                absYFromFocus(*(s32 *)(r4 + 0xC)) <= 0x400000) {
                u8 *q = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
                s32 *g;
                *(u8 *)(q + 0x19) = 0;
                g = (s32 *)0x08671BD0;
                sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, *g);
                return;
            }
            v = ((struct SCounter *)r6)->value;
            if (v < 0) v += 3;
            ((struct Counter *)r6)->value = (u16)(v >> 2);
        }
    }
}
