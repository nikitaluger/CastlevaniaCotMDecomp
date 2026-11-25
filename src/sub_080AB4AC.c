void sub_080AC908(s32, void *, void *, void *);
void sub_080146D0(void *, s32, s32);
void sub_0801165C(void *, s32);
void sub_080AC9B4(u8, void *);
void sub_080C31E4(void *, void *, s32);
extern s32 D_08671BB0;

/* Wind down a moving effect: advance its aim/step sequence, lower its speed by
 * 0x800 a frame down to zero, turn angle+speed into velocity, integrate the
 * position, tick the effect's sub-timer, and once the speed is zero clear the
 * phase byte and move on to the next script step. */
void sub_080AB4AC(void *arg0) {
    u8 *entity = (u8 *)arg0;
    s32 sprite = *(s32 *)(entity + 0x38);
    u8 *work = *(u8 **)(entity + 0x3C);
    u8 *animator;
    u8 *aim;
    s32 speed;
    s32 *lit;

    animator = work + 0x34;
    aim = work + 0x48;
    sub_080AC908(sprite, animator, work, aim);
    speed = *(s32 *)(aim + 0x18) + 0xFFFFF800;
    *(s32 *)(aim + 0x18) = speed;
    if (speed < 0) {
        *(s32 *)(aim + 0x18) = 0;
    }
    sub_080146D0(work, *(s32 *)(aim + 0x14), *(s32 *)(aim + 0x18));
    sub_0801165C(work, 0);
    sub_080AC9B4(*(u8 *)(work + 0x244), work + 0x68);
    if (*(s32 *)(aim + 0x18) == 0) {
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        lit = &D_08671BB0;
        sub_080C31E4(entity + 0x18, entity + 0x22, *lit);
    }
}
