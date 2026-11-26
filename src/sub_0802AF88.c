extern s32 sub_08005820(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern s32 signOf(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 D_08671BD0;
struct S_02025FF0 { u8 _[0x174C]; s32 field174C; };
extern struct S_02025FF0 gMainWorkspace;

/*
 * Companion/attack controller. arg0 is a manager holding an owner handle
 * (+0x38) and the entity it drives (+0x3C). It refreshes the entity's attack
 * and turn countdown timers (entity+0x48+4 / +2), fires the attack function
 * pointed to by D_08671BD0[0] when the entity is lined up with the player, and
 * reverses the entity's horizontal direction (+0x10) on the turn timer.
 */
void sub_0802AF88(u8 *mgr)
{
    s32 owner = *(s32 *)(mgr + 0x38);
    u8 *ent = *(u8 **)(mgr + 0x3C);
    u8 *anim = ent + 0x34;
    u8 *timers = ent + 0x48;

    sub_080149A4(owner, ent, timers, 0x5A, 0x78);
    setAnimationFrame(owner, anim, 0, 1);

    /* attack countdown */
    *(s16 *)(timers + 4) = *(s16 *)(timers + 4) - 1;
    if (*(s16 *)(timers + 4) <= 0)
    {
        *(u16 *)(timers + 4) = (u16)(sub_08005820(0x1F) + 0x3C);
        if (sub_08014900(*(s32 *)(ent + 8)) <= 0x300000 &&
            sub_0801491C(*(s32 *)(ent + 0xC)) <= 0x200000)
        {
            s32 dirSign = signOf(*(s32 *)(ent + 8));
            if (dirSign == sub_08014990(owner))
            {
                s16 poseIndex = *(s16 *)(mgr + 0x22);
                u32 *attackFunc;
                *(u8 *)(mgr + poseIndex * 2 + 0x19) = 0;
                attackFunc = (u32 *)0x08671BD0;
                sub_080C31E8(mgr + 0x18, mgr + 0x22, 1, *attackFunc);
                return;
            }
        }
        *(u16 *)(timers + 4) = 0;
    }

    /* facing flag: flip direction */
    if (*(u16 *)(ent + 2) & 2)
    {
        *(s32 *)(ent + 0x10) = -*(s32 *)(ent + 0x10);
        *(u16 *)(timers + 2) = (u16)(sub_08005820(0x15) + 0x28);
    }

    /* turn countdown */
    *(s16 *)(timers + 2) = *(s16 *)(timers + 2) - 1;
    if (*(s16 *)(timers + 2) <= 0)
    {
        s32 forceLongDelay = 0;
        s32 playerFarX = 0;
        s32 deltaX;

        if (sub_08014900(*(s32 *)(ent + 8)) > 0x280000)
            playerFarX = 1;

        deltaX = gMainWorkspace.field174C - *(s32 *)(ent + 8);
        if ((deltaX < 0 && *(s32 *)(ent + 0x10) < 0) ||
            (deltaX > 0 && *(s32 *)(ent + 0x10) > 0))
        {
            if (playerFarX != 0)
                goto checkDelay;
            goto longDelay;
        }
        else
        {
            if (playerFarX == 1)
                forceLongDelay = 1;
        }

    checkDelay:
        if (forceLongDelay != 0)
            goto longDelay;

        *(u16 *)(timers + 2) = (u16)(sub_08005820(6) + 0x0F);
        goto afterDelay;

    longDelay:
        *(u16 *)(timers + 2) = (u16)(sub_08005820(0x15) + 0x28);
    afterDelay:
        *(s32 *)(ent + 0x10) = -*(s32 *)(ent + 0x10);
    }
}
