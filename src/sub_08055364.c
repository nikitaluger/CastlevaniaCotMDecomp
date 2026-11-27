/*
 * Actor script step: play animation 0 and, once the actor is inside the room
 * bounds and close to the player (within 96 units horizontally, 64 vertically),
 * clear the step counter and advance the script.
 */
void setAnimationFrame(s32, s32, s32, s32);
s32 sub_08014114(s32, s32, s32, s32, s32, s32);  /* is a box inside the room bounds */
s32 absXFromFocus(s32);  /* |player X - x| */
s32 absYFromFocus(s32);  /* |player Y - y| */
void sub_080C31E4(void *, void *, s32);

void sub_08055364(void *arg0)
{
    void *work;
    s32 sprite;
    s32 *stepCallback;
    sprite = *(s32 *)((s8 *)arg0 + 0x38);
    work = *(void **)((s8 *)arg0 + 0x3C);
    setAnimationFrame(sprite, (s32)((s8 *)work + 0x34), 0, 0);
    if ((sub_08014114(*(s32 *)((s8 *)work + 8), *(s32 *)((s8 *)work + 0xC), 0, 0, 0, 0) == 1) && (absXFromFocus(*(s32 *)((s8 *)work + 8)) <= 0x600000) && (absYFromFocus(*(s32 *)((s8 *)work + 0xC)) <= 0x400000))
    {
        *(s8 *)((s8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + arg0) + 0x19) = 0;
        stepCallback = (s32 *)0x08671BB0;
        sub_080C31E4((s8 *)arg0 + 0x18, (s8 *)arg0 + 0x22, *stepCallback);
    }
}
