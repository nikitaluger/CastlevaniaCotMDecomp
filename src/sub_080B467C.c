/*
 * Actor script step: choose animation frame 0x37 or 0x39 from the script
 * action byte and tick the animation; once the byte passes its upper
 * threshold while the animation reports "busy", clear the byte and advance
 * the script through the step callback.
 */
extern s32 sub_080114DC(void *, void *, s32, s32);
extern s32 sub_08011528(void *, void *);
extern s32 sub_080C31E4(void *, void *, s32);

#define ACTION_LOW_MAX  0x1D
#define ACTION_HIGH_MIN 0x1E
#define FRAME_LOW       0x37
#define FRAME_HIGH      0x39
#define ANIM_FLAG_BUSY  2

void sub_080B467C(void *arg0)
{
    s32 *stepCallback;
    s32 sprite;
    s32 animState;
    void *work;
    s32 actionEntry;

    sprite = *(s32 *)((s8 *)arg0 + 0x38);
    work = *(void **)((s8 *)arg0 + 0x3C);
    animState = (s32)((s8 *)work + 0x34);
    if (*(u8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + (u32)arg0) + 0x19) <= ACTION_LOW_MAX) {
        sub_080114DC(sprite, animState, FRAME_LOW, 0);
    } else {
        sub_080114DC(sprite, animState, FRAME_HIGH, 0);
    }
    sub_08011528(sprite, animState);
    actionEntry = (*(s16 *)((s8 *)arg0 + 0x22) * 2) + (u32)arg0;
    if ((*(u8 *)((s8 *)actionEntry + 0x19) > ACTION_HIGH_MIN) && (*(u8 *)(s8 *)animState & ANIM_FLAG_BUSY)) {
        *(u8 *)((s8 *)actionEntry + 0x19) = 0;
        stepCallback = &(*(s32 *)0x08671BB0);
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *stepCallback);
    }
}
