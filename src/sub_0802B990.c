void sub_08011368(s32, void *, s32, s32);
void sub_0802BA40(s32, void *, s32);
void sub_080C31E0(void *, s32);

/* Plays animation frame 0x12 and spawns effects around the entity at fixed
 * points in the animation; at animation end it spawns the last two effects and
 * switches to the next script state. */
void sub_0802B990(void *entity)
{
    s32 frameCode;
    int handlerOffset;
    s32 sprite;
    void *work;
    void *animator;
    s32 *handler;
    u8 *animFlags;

    sprite = *(s32 *)((s8 *)entity + 0x38);
    work = *(void **)((s8 *)entity + 0x3C);
    animFlags = (u8 *)((s8 *)work + 0x34);
    animator = work + 0x34;
    *(s32 *)((s8 *)work + 0x14) = 0;
    *(s32 *)((s8 *)work + 0x10) = 0;
    sub_08011368(sprite, animator, 0x12, 0);
    if (*(s32 *)((s8 *)animator + 4) == 1) {
        frameCode = *(u8 *)((s8 *)animator + 1) - 1;
        switch (frameCode) {
        case 2:
            sub_0802BA40(sprite, work, 0);
            break;
        case 3:
            sub_0802BA40(sprite, work, 1);
            sub_0802BA40(sprite, work, 2);
            break;
        }
    }
    if (2 & (*animFlags)) {
        sub_0802BA40(sprite, work, 3);
        handlerOffset = 0x24;
        handler = (s32 *)((s8 *)entity + handlerOffset);
        sub_0802BA40(sprite, work, 4);
        sub_080C31E0(entity, *handler);
    }
}
