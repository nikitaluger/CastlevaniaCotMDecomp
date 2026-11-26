void setAnimationFrame(s32, void *, s32, s32);
void sub_0802D2E8(s32, void *, s32);
void sub_080C31E0(void *, s32);

/* Plays animation frame 0x1A and spawns effects around the entity at fixed
 * points in the animation; at animation end it spawns the last two effects and
 * switches to the next script state. */
void sub_0802D238(void *entity)
{
    u8 *animFlags;
    s32 frameCode;
    s32 sprite;
    void *work;
    void *animator;

    sprite = *(s32 *)((s8 *)entity + 0x38);
    work = *(void **)((s8 *)entity + 0x3C);
    animFlags = (u8 *)((s8 *)work + 0x34);
    animator = (s8 *)work + 0x34;
    *(s32 *)((s8 *)work + 0x14) = 0;
    *(s32 *)((s8 *)work + 0x10) = 0;
    setAnimationFrame(sprite, animator, 0x1A, 0);
    if (*(s32 *)((s8 *)animator + 4) == 1) {
        frameCode = *(u8 *)((s8 *)animator + 1) - 1;
        switch (frameCode) {
        case 2:
            sub_0802D2E8(sprite, work, 0);
            break;
        case 3:
            sub_0802D2E8(sprite, work, 1);
            sub_0802D2E8(sprite, work, 2);
            break;
        }
    }
    if (2 & (*animFlags)) {
        sub_0802D2E8(sprite, work, 3);
        sub_0802D2E8(sprite, work, 4);
        sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
    }
}
