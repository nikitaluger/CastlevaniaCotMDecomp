/* Enemy patrol AI driven by two countdown timers: one governs the action
 * animation, the other the direction changes. It uses the player's position
 * to decide when to turn around and when to end the current action. */
extern s32 scaleByRandom(s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 absXFromFocus(s32);
extern s32 absYFromFocus(s32);
extern void sub_080149A4(s32, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u32 gScriptStepCallbacks;
struct GlobalCoord { u8 _[0x174C]; s32 field174C; };
extern struct GlobalCoord gMainWorkspace;

/* Enemy patrol AI step: two countdown timers drive the action animation and facing changes, using the player's position to decide when to turn around and when to end the current action. */ void updatePatrolAI(u8 *self)
{
    s32 work = *(s32 *)(self + 0x38);
    u8 *state = *(u8 **)(self + 0xAC);
    u8 *entity = *(u8 **)(self + 0x3C);
    u8 *anim = entity + 0x34;
    u8 *body = entity + 0x48;

    if ((*(u16 *)(*(u8 **)(state + 4) + 6) & 0x12) != 0x10)
    {
        sub_080149A4(work, entity, body, 0x5A, 0x78);
    }

    setAnimationFrame(work, anim, 0, 1);

    *(s16 *)(body + 4) = *(s16 *)(body + 4) - 1;
    if (*(s16 *)(body + 4) <= 0)
    {
        *(u16 *)(body + 4) = (u16)(scaleByRandom(0x3D) + 0x96);
        if (absXFromFocus(*(s32 *)(entity + 8)) <= 0x880000 &&
            absYFromFocus(*(s32 *)(entity + 0xC)) <= 0x700000)
        {
            s16 actionIndex = *(s16 *)(self + 0x22);
            u32 *cbTable;
            *(u8 *)(self + actionIndex * 2 + 0x19) = 0;
            cbTable = (u32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *cbTable);
            return;
        }
        {
            s32 timer = *(s16 *)(body + 4);
            if (timer < 0) timer += 3;
            *(s16 *)(body + 4) = (s16)(timer >> 2);
        }
    }

    if ((*(u16 *)(*(u8 **)(state + 4) + 6) & 0x10) == 0)
    {
        if (*(u16 *)(entity + 2) & 2)
        {
            *(s32 *)(entity + 0x10) = -*(s32 *)(entity + 0x10);
            *(u16 *)(body + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
        }

        *(s16 *)(body + 2) = *(s16 *)(body + 2) - 1;
        if (*(s16 *)(body + 2) <= 0)
        {
            s32 forceLong = 0;
            s32 farX = 0;
            s32 toPlayerX;

            if (absXFromFocus(*(s32 *)(entity + 8)) > 0x300000)
                farX = 1;

            toPlayerX = gMainWorkspace.field174C - *(s32 *)(entity + 8);
            if ((toPlayerX < 0 && *(s32 *)(entity + 0x10) < 0) ||
                (toPlayerX > 0 && *(s32 *)(entity + 0x10) > 0))
            {
                if (farX != 0)
                    goto checkForce;
                goto block25;
            }
            else
            {
                if (farX == 1)
                    forceLong = 1;
            }

checkForce:
            if (forceLong != 0)
                goto block25;

            *(u16 *)(body + 2) = (u16)(scaleByRandom(6) + 0x0A);
            goto afterSet;

block25:
            *(u16 *)(body + 2) = (u16)(scaleByRandom(0x0B) + 0x1E);
afterSet:
            *(s32 *)(entity + 0x10) = -*(s32 *)(entity + 0x10);
        }
    }
}
