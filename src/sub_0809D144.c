void setObjectAnimation(s32, s32, s32, s32);
void sub_0809E278(s32, s32, void *, s32);
void sub_080A01CC(s32, s32);
s32 sub_080A01D4(s32);
void sub_080C31E4(void *, void *, s32);

/* Enemy actor step: advance animation frame 7 and its wobble offset, then
 * interpret the script step byte: steps 8/0x5A set a target's status to 1/2;
 * a zero status resets the step to 0 and dispatches the script handler. */
void sub_0809D144(void *actor)
{
    u8 *self = (u8 *)actor;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    u8 *state = work + 0x48;

    setObjectAnimation(sprite, (s32)anim, 7, 1);
    sub_0809E278(sprite, (s32)anim, work, (s32)state);

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 7)
    {
        switch (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))
        {
        case 8:
            sub_080A01CC(*(s32 *)(state + 0x1C), 1);
            break;
        case 0x5A:
            sub_080A01CC(*(s32 *)(state + 0x1C), 2);
            break;
        }

        {
            s32 status = sub_080A01D4(*(s32 *)(state + 0x1C));
            if (status == 0)
            {
                *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = status;
                {
                    s32 *handlerTable = (s32 *)0x08671BB0;
                    sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
                }
            }
        }
    }
}
