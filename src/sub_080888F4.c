extern u32 D_02025FF0[];
struct S_02025FF0_14B8 { u8 _0[0x14B8]; u32 v; };
extern struct S_02025FF0_14B8 D_02025FF0_14B8;
s32 sub_08003740(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E4(void *, void *, u32);
void sub_080C31E0(void *, void *);
void sub_08003A6C(void *, u32, u32);

/* Actor step: tick the mover; when it finishes (sub_08003740 returns 0), set
 * global state D_02025FF0[7] to 2, clear the script step byte and advance, then
 * copy the mover's position to the sprite. */
void sub_080888F4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *mover = *(u8 **)(self + 0x6C);
    u8 *pos = mover + 4;
    u8 *sprite = *(u8 **)(self + 0x38);
    u32 *callback;
    s32 result = sub_08003740(mover + 0x20, sprite);
    if (result == 0) {
        D_02025FF0[7] = 2;
        *(u8*)(self + *(s16*)(self + 0x22) * 2 + 0x19) = result;
        callback = (u32*)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *callback);
    }
    sub_0806D588(sprite, pos);
}
