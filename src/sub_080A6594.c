extern s32 refreshMotionTrail(void *, void *);
extern s32 decelerateTargetX(s32, void *);
extern s32 sub_080C31E0(s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* Behaviour callback: advance the owner's animation frame, set its tracking
 * offsets from the base angle, map the script state to a pose, and dispatch
 * the next command when the script reaches the dispatch state. */
void sub_080A6594(void *behav)
{
    u8 *self = (u8 *)behav;
    s32 *target = *((s32 **)(self + 0x38));
    s32 *owner = *((s32 **)(self + 0x3C));
    u8 *ownerData = ((u8 *)owner) + 0x48;
    s32 *frame = (s32 *)(((u8 *)owner) + 0x134);
    s32 *angleTable;
    s32 *baseAngle;
    s32 *cmdTable;
    u8 *flag;
    u8 stateByte;
    u32 zero;

    *frame = (*frame) + 2;
    angleTable = (s32 *)0x08671BFC;
    baseAngle = (s32 *)(((u8 *)owner) + 0x130);
    *((s32 *)(((u8 *)owner) + 0xFC)) = (s32)(((s32)(sub_080C31E0((*baseAngle) + 0x4000, *angleTable) * (*frame))) >> 7);
    *((s32 *)(((u8 *)owner) + 0x100)) = (s32)(((s32)(sub_080C31E0(*baseAngle, *((s32 *)0x08671BFC)) * (*frame))) >> 7);
    stateByte = *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19));
    if (stateByte == 6)
    {
        *((u8 *)(((u8 *)owner) + 0xEE)) = 1;
    }
    else
        if (stateByte == 0xC)
    {
        *((u8 *)(((u8 *)owner) + 0xEE)) = 2;
    }
    decelerateTargetX((s32)target, ownerData);
    refreshMotionTrail(self, ownerData);
    if ((*((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19))) == 0x28)
    {
        flag = ownerData + 0xA7;
        zero = 0;
        *flag = 1;
        *((u8 *)((self + ((*((s16 *)(self + 0x22))) * 2)) + 0x19)) = zero;
        cmdTable = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *cmdTable);
    }
}
