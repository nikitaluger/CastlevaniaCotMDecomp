extern u32 gMainWorkspace[];
extern u32 gMainObjTimerCallbacks;

void stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Refresh an entity's display: redraw it from its sprite in the normal mode,
 * or update only its render object's screen position in the special mode. */
void sub_0808968C(void *entity)
{
    void *pos = *(u8 **)((u8 *)entity + 0x6C) + 4;
    void *screenObj = *(void **)((u8 *)entity + 0x38);

    if (gMainWorkspace[4] == 0)
        sub_080C31E0(entity, *(void **)((u8 *)entity + 0x24));
    else
        sub_0806D588(screenObj, pos);
}

/* In special state 0x19, raise the entity's 0x10 flag, start the global timer,
 * clear the current step byte and dispatch its handler; then run the animation
 * state's delay timer and refresh the screen position. */
void sub_08089630(void *entity)
{
    u8 *e = entity;
    u8 *animState = *(u8 **)(e + 0x6C);
    u8 *pos = animState + 4;
    u8 *screenObj = *(u8 **)(e + 0x38);

    if (gMainWorkspace[5] == 0x19)
    {
        u32 zero = 0;
        *(u16 *)(screenObj + 2) |= 0x10;
        gMainWorkspace[7] = 4;
        *(u8 *)(e + *(s16 *)(e + 0x22) * 2 + 0x19) = zero;
        sub_080C31E4(e + 0x18, e + 0x22, gMainObjTimerCallbacks);
    }
    stepDelayTimer(animState + 0x20, screenObj);
    sub_0806D588(screenObj, pos);
}

/* In special state 0x10, clear the current step byte and dispatch the entity's
 * handler; always refresh its screen position afterwards. */
void sub_080897EC(void *entity)
{
    u8 *e = entity;
    void *pos = *(u8 **)(e + 0x6C) + 4;
    void *screenObj = *(void **)(e + 0x38);

    if (gMainWorkspace[5] == 0x10)
    {
        gMainWorkspace[7] = 4;
        *(u8 *)(e + *(s16 *)(e + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(e + 0x18, e + 0x22, gMainObjTimerCallbacks);
    }
    sub_0806D588(screenObj, pos);
}

/* Set or clear the entity's 0x10 flag against its threshold, then redraw it
 * normally or just refresh its screen position. */
void sub_08089834(void *entity)
{
    u8 *e = entity;
    void *pos = *(u8 **)(e + 0x6C) + 4;
    void *screenObj = *(void **)(e + 0x38);
    u16 v;

    if ((s32)gMainWorkspace[14] < *(s32 *)((u8 *)screenObj + 0x14))
        v = 0x10 | *(u16 *)((u8 *)screenObj + 2);
    else
        v = *(u16 *)((u8 *)screenObj + 2) & 0xFFEF;

    *(u16 *)((u8 *)screenObj + 2) = v;

    if (gMainWorkspace[4] == 0)
        sub_080C31E0(e, *(void **)(e + 0x24));
    else
        sub_0806D588(screenObj, pos);
}
