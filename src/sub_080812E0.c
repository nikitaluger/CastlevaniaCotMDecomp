extern u8 gMainWorkspace[];

s32 sub_0806D450(void *, void *, void *);
s32 stepDelayTimer(void *, void *);
void sub_080C31E0(void *, void *);

/* Decide whether to hand an actor back to its default handler: apply any
 * area-specific behavior (which may reposition the sprite), tick the work
 * block's AI script, then check global state for the switch conditions. */
void sub_080812E0(void *actor)
{
    void *actorRef = actor;
    u8 *position;
    u16 *sprite;
    u8 *work;
    u8 *state;

    work = *(u8 **)((u8 *)actorRef + 0x6C);
    position = work + 4;
    sprite = *(u16 **)((u8 *)actorRef + 0x38);

    if (sub_0806D450(actorRef, sprite, position) > 0)
        goto call;

    *(u16 *)(*(u8 **)(position + 0x2C) + 0x14) = 0;
    state = gMainWorkspace;
    *sprite = *(u16 *)(state + 0x18C2);
    if (stepDelayTimer(work + 0x20, sprite) != 0)
        goto check;

call:
    sub_080C31E0(actorRef, *(void **)((u8 *)actorRef + 0x24));
    goto end;

check:
    if (*(u8 *)(state + 0x173A) == 0x1C)
        goto call2;
    if (*(u8 *)(state + 0x14ED) != 0)
        goto end;
    if (*(u32 *)(state + 0x10) == 0)
        goto end;

call2:
    sub_080C31E0(actorRef, *(void **)((u8 *)actorRef + 0x24));

end:
    ;
}
