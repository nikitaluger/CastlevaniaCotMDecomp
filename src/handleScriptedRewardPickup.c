extern void playSound(s32);
extern void spawnPickupEffect(s32, s32, u16);
extern void _call_via_r1(void *, void *);

extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u16 gPickupEffectTypes[];
extern u8 gPickupStates[];

/* gGameStatus fields used by the pickup script. */
#define GS_MODE             0x8C   /* s16 game-mode word */
#define GS_COLLECTED        0x2D4  /* u16 running pickup total */
#define GS_COLLECTED_TARGET 0x2D6  /* u16 cap for that total */
#define GS_PICKUP_STATE     0x2D8  /* u8 current pickup state */
#define GS_PICKUP_FLAG      0x2D9  /* u8 set only for state 1 / step 2 */

/* gMainWorkspace fields used by the pickup script. */
#define MW_EFFECT_X      0x174C /* s32 world X for spawned effects */
#define MW_EFFECT_Y      0x1750 /* s32 world Y for spawned effects */
#define MW_COLLECTED     0x1504 /* u16 mirror of the pickup total */
#define MW_ACTION_STATE  0x14ED /* action-step byte that grants bonus credit */

#define SFX_PICKUP_STEP  0x77
#define SFX_PICKUP_FINAL 0x75

/* Spawn the pickup effect at the workspace's stored world coordinates; its
 * type is chosen by the current pickup state. */
#define SPAWN_PICKUP_EFFECT() { u8 *fb = gMainWorkspace; spawnPickupEffect(*(s32 *)(fb + MW_EFFECT_X), *(s32 *)(fb + MW_EFFECT_Y), gPickupEffectTypes[*statePtr - 1]); }

/* Script handler for a scripted reward pickup. Steps 0-4 advance the pickup
 * state and spawn its effect; steps 5/6 add to the collected total (with an
 * extra credit when the action state allows it), then clamp the total to its
 * target. The script's saved cleanup callback runs last. */
void handleScriptedRewardPickup(void *arg0)
{
    u8 *gs = gGameStatus;
    u16 *params = (u16 *)((u8 *)arg0 + 0x4C);
    u8 *statePtr;
    u8 state;

    if (params[4] <= 4)
    {
        statePtr = gs + GS_PICKUP_STATE;
        state = *statePtr;
        if (state)
        {
            if (*(s16 *)(gs + GS_MODE) == 1)
            {
                if (state == 1)
                {
                    if (params[4] == 2)
                        *(u8 *)(gs + GS_PICKUP_FLAG) = state;
                    else
                    {
                        *(u8 *)(gs + GS_PICKUP_FLAG) = 0;
                        SPAWN_PICKUP_EFFECT();
                    }
                }
                else
                {
                    *(u8 *)(gs + GS_PICKUP_FLAG) = 0;
                    SPAWN_PICKUP_EFFECT();
                }
            }
            else
                SPAWN_PICKUP_EFFECT();
        }

        if (params[4] <= 4)
        {
            u8 nextState;
            playSound(SFX_PICKUP_STEP);
            nextState = gPickupStates[params[4]];
            *(u8 *)(gs + GS_PICKUP_STATE) = nextState;
        }
    }

    if ((u16)(params[4] - 5) <= 1)
    {
        u16 step;
        playSound(SFX_PICKUP_FINAL);
        if (params[4] == 5)
        {
            (*(u16 *)(gs + GS_COLLECTED))++;
            {
                u8 *fb = gMainWorkspace;
                (*(u16 *)(fb + MW_COLLECTED))++;
            }
        }
        step = params[4];
        {
            u8 *fb = gMainWorkspace;
            if (step == 6)
            {
                *(u16 *)(gs + GS_COLLECTED) += 5;
                *(u16 *)(fb + MW_COLLECTED) += 5;
            }
            {
                u8 *fb2;
                __builtin_memcpy(&fb2, &fb, 4);
                if (*(u8 *)(fb2 + MW_ACTION_STATE) == 0x26)
                {
                    if (params[4] == 5)
                    {
                        (*(u16 *)(gs + GS_COLLECTED))++;
                        (*(u16 *)(fb2 + MW_COLLECTED))++;
                    }
                    if (params[4] == 6)
                    {
                        *(u16 *)(gs + GS_COLLECTED) += 5;
                        (*(u16 *)(fb + MW_COLLECTED)) += 5;
                    }
                }
            }
        }
        {
            s16 total = *(s16 *)(gs + GS_COLLECTED);
            u16 target = *(u16 *)(gs + GS_COLLECTED_TARGET);
            s16 targetSigned = *(s16 *)(gs + GS_COLLECTED_TARGET);
            if (total > targetSigned)
                *(u16 *)(gs + GS_COLLECTED) = target;
        }
    }

    _call_via_r1(arg0, *(void **)((u8 *)arg0 + 0x24));
}
