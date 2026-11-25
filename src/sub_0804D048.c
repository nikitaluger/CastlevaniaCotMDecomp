extern u8 D_080CF9BC[];
extern u32 D_08671BD0[];

void sub_080113A8(s32, void *);
void sub_08011368(s32, void *, u16, u8);
void sub_08014668(void *, s32);
void sub_08014588(void *, void *);
void sub_080C31E8(void *, void *, s32, s32);

/* Bounce reaction: update the sprite, and on the 8th frame reverse the target's
 * x velocity, flip the sprite horizontally, restart its animation, apply the
 * bounce size table, set the bounce-state word, clear the part's frame counter
 * and run the next animation step. */
void sub_0804D048(u8 *arg0) {
    u8 *sprite = *(u8 **)(arg0 + 0x38);
    u8 *target = *(u8 **)(arg0 + 0x3C);
    u8 *anim = target + 0x34;
    s32 zero;
    u16 *bounceState;
    s32 one;
    sub_080113A8((s32)sprite, anim);
    if (*(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) == 8) {
        s32 velocity = -*(s32 *)(target + 0x10);
        *(s32 *)(target + 0x10) = velocity;
        sub_08014668(sprite, velocity);
        sub_08011368((s32)sprite, anim, 0, 1);
        sub_08014588(*(void **)(target + 0x28), D_080CF9BC);
        bounceState = (u16 *)(arg0 + 0x4C);
        zero = 0;
        one = 0x100;
        *bounceState = one;
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = zero;
        {
            u32 *stepTable = D_08671BD0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0, *stepTable);
        }
    }
}
