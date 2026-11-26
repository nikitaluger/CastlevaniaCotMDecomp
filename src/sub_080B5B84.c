/*
 * Actor script step: play the idle animation, advance the actor's physics,
 * set the sprite's animation delay to 0x1000 divided by the step number, and
 * when the step number reaches 0x10 restart the countdown, hand the work
 * object's motion vector to the actor and advance the script.
 */
extern s32 sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern u16 divideInt(s32, u8);
extern void sub_080C31E4(void *, void *, s32);

struct Sprite {
    u8 _pad[4];
    u16 frameDelay;  /* duration of the current animation frame */
    u16 frameTimer;  /* countdown for the current frame */
};

void sub_080B5B84(void *arg0) {
    void *work;
    struct Sprite *sprite;
    s32 *stepCallback;

    sprite = *(struct Sprite **)((s8 *)arg0 + 0x38);
    work = *(void **)((s8 *)arg0 + 0x3C);
    sub_080113A8(sprite, (s8 *)work + 0x34);
    sub_0801165C(work, 0);
    sprite->frameDelay = divideInt(0x1000, *(u8 *)((s8 *)arg0 + *(s16 *)((s8 *)arg0 + 0x22) * 2 + 0x19));
    if (*(u8 *)((s8 *)arg0 + *(s16 *)((s8 *)arg0 + 0x22) * 2 + 0x19) == 0x10) {
        sprite->frameDelay = 0x100;
        *(s32 *)((s8 *)arg0 + 0x8C) = *(s32 *)((s8 *)work + 0xC);
        *(u8 *)((s8 *)arg0 + *(s16 *)((s8 *)arg0 + 0x22) * 2 + 0x19) = 0;
        stepCallback = &(*(s32 *)0x08671BB0);
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *stepCallback);
    }
    sprite->frameTimer = sprite->frameDelay;
}
