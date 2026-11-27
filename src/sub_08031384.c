s32 absXFromFocus(s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Script-step setup with a distance gate: when the owner requests it and the
 * entity is within range of the camera target, give it a forward speed; then
 * clear the step byte, run the script interpreter, advance the step byte and
 * dispatch the handler for the new step. */
void sub_08031384(void *arg0)
{
    u8 *self = arg0;
    u8 *work;
    u32 *owner;
    u32 *ownerData;

    owner = *(u32 **)(self + 0xAC);
    work = *(u8 **)(self + 0x3C);
    ownerData = *(u32 **)((u8 *)owner + 4);
    if (*(u16 *)((u8 *)ownerData + 6) & 0x100) {
        if (absXFromFocus(*(s32 *)(work + 8)) <= 0x400000) {
            *(s32 *)(work + 0x14) = 0x40000;
        } else {
            return;
        }
    }

    {
        u8 *stepBase;
        s32 *scriptHandlers;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptHandlers = (s32 *)0x08671BB0;
        stepBase = self + 0x18;
        sub_080C31E4(stepBase, self + 0x22, *scriptHandlers);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        stepBase = stepBase + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(void **)((u32)*stepBase * 4 + *(u32 *)(self + 0x14)));
    }
}
