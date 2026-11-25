/* Highlight/flash script step: counts the timer at work+0x18 down by 2 each frame,
 * drives the global gfx highlight color (D_03000830[2]) and crossfade weight ([3]),
 * and on expiry releases the two linked objects and advances the script. */
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

extern u16 D_03000830[];

void sub_080089EC(u8 *self) {
    u8 *work;
    s32 timer;

    work = *(u8 **)(self + 0x3C);
    timer = *(s32 *)(work + 0x18);
    timer -= 2;
    *(s32 *)(work + 0x18) = timer;
    if (timer < 0) {
        *(s32 *)(work + 0x18) = 0;
    }
    D_03000830[2] = 0x3F40;
    {
        s32 fade = *(s32 *)(work + 0x18);
        D_03000830[3] = (u16)(fade | ((0x10 - fade) << 8));
    }
    if (*(s32 *)(work + 0x18) == 0) {
        void *linked0 = *(void **)work;
        if (linked0 != 0) {
            sub_080C31E0(linked0, *(void **)((u8 *)linked0 + 0x24));
        }
        {
            void *linked1 = *(void **)(work + 4);
            if (linked1 != 0) {
                sub_080C31E0(linked1, *(void **)((u8 *)linked1 + 0x24));
            }
        }
        D_03000830[2] = 0xBF;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
        }
    }
}
