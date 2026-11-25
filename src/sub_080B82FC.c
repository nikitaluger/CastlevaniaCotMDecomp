s32 sub_08011368(s32, void *, s32, s32);
void sub_0808D0A4(s32);
void sub_080B9818(s32, s32);
void sub_080B9874(void);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

extern s32 D_08671BB0;

/* Death cleanup for a multi-part entity: reset the animator to frame 0, remove
 * child objects of id 0x1CF from the +0x30 list, clear related global flags,
 * mark the pose, play sound 0x13, then reset the step byte and advance the
 * script. */
void sub_080B82FC(void *entity)
{
    void *work;
    void *self;
    void *workRef;
    void *child;
    s32 sprite;
    void *pose;
    void *animState;
    s32 *scriptCb;

    sprite = *(s32 *)((s8 *)entity + 0x38);
    work = *(void **)((s8 *)entity + 0x3C);
    self = entity;
    workRef = work;
    animState = (s8 *)work + 0x34;
    pose = (s8 *)work + 0x48;
    sub_08011368(sprite, animState, 0, 0);
    child = *(void **)((s8 *)entity + 0x30);
    if (child != NULL) {
        do {
            if (*(s16 *)child == 0x1CF) {
                sub_080C31E0(child, *(s32 *)((s8 *)child + 0x24));
            }
            child = *(void **)((s8 *)child + 0x2C);
        } while (child != NULL);
    }
    sub_080B9874();
    sub_080B9818(*(s32 *)pose, *(s32 *)((s8 *)workRef + 0x08));
    sub_0808D0A4(0x13);
    *(s8 *)(((s8 *)(((*(s16 *)((s8 *)entity + 0x22)) * 2) + entity)) + 0x19) = 0;
    scriptCb = &D_08671BB0;
    sub_080C31E4((s8 *)entity + 0x18, (s8 *)entity + 0x22, *scriptCb);
}
