void sub_080113A8(void *, void *);
void sub_080409FC(void *, void *, void *, u16);
void sub_080C31E8(void *, void *, s32, s32);
extern u16 D_080CF470[];
extern s32 D_08671BD0;

/* Updates the entity's animation; when the animation ends it plays the part's
 * animation for the entity's variant, raises the work object by one unit,
 * clears the step byte and restarts the script step with argument 1. */
void sub_0803FEB0(void *arg0)
{
    u8 *self = arg0;
    void *sprite;
    u8 *work;
    u8 *animator;
    u8 *part;

    sprite = *(void **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    animator = work + 0x34;
    part = work + 0x48;
    sub_080113A8(sprite, animator);
    if (*animator & 2) {
        u16 frame;
        frame = D_080CF470[*(u8 *)(self + 0x4C)];
        sub_080409FC(sprite, animator, part, frame);
        *(s32 *)(work + 0x0C) += 0x10000;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *scriptHandlers = &D_08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptHandlers);
        }
    }
}
