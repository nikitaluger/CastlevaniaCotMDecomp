extern void *gScriptStepCallbacks;
struct WorldFlags { u8 pad[0x146C]; u16 flags; };
extern struct WorldFlags gCameraState;

void startScreenTransition(void);
s32 setEntityForm(void *, void *, s32);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, s32);

/*
 * Tests global mode/input flags to decide whether a companion action is allowed;
 * on the go path it masks a state word, triggers an effect and fires the current
 * pose's attack routine from gScriptStepCallbacks.
 */
/* Checks the configured companion-action button against the active input word: in a special scene it starts a screen transition and returns 2; otherwise, if the blocking status bytes are clear, it switches to form 0x35, plays the summon sound, clears the current script step and dispatches step 0x1C, returning 1. Returns 0 when the action is not allowed. */ s32 tryCompanionAction(void *actor, void *owner, void *state) {
    u8 *gameStatus = (u8 *)0x02025368;
    u8 *workspaceBase = (u8 *)0x02025FF0;
    u8 actionState = workspaceBase[0x14ED];
    u8 *workspace = workspaceBase;
    u8 blockFlag;
    s16 stepIndex;

    if (actionState != 0) {
        if (*(s32 *)(workspace + 0x24) != 0) {
            if ((*(u16 *)(workspace + 0x28) & *(u16 *)(gameStatus + 0x3C2)) != 0) goto success;
            goto ret0;
        } else {
            if ((gCameraState.flags & *(u16 *)(gameStatus + 0x3C2)) == 0) goto ret0;
        }
success:
        startScreenTransition();
        return 2;
    }
    if (*(s32 *)(workspace + 0x24) != 0) {
        if ((*(u16 *)(workspace + 0x28) & *(u16 *)(gameStatus + 0x3C2)) != 0) goto cont;
        goto ret0;
    } else {
        if ((gCameraState.flags & *(u16 *)(gameStatus + 0x3C2)) == 0) goto ret0;
    }
cont:
    blockFlag = *(u8 *)(gameStatus + 0x2DB);
    if (blockFlag == 0 && *(u8 *)(gameStatus + *(u8 *)(gameStatus + 0x305) + 0x315) != 0 && *(u8 *)(gameStatus + *(u8 *)(gameStatus + 0x304) + 0x30B) != 0) {
        *(s32 *)(workspace + 0x1848) |= 0x49FE0000;
        setEntityForm(owner, state, 0x35);
        sub_08005E80(0x12C);
        *(s32 *)((u8 *)state + 0x8C) = 1;
        stepIndex = *(s16 *)((u8 *)actor + 0x22);
        *((u8 *)actor + stepIndex*2 + 0x19) = blockFlag;
        {
            u32 *callbackTable = (u32 *)0x08671BD0;
            sub_080C31E8((u8 *)actor + 0x18, (u8 *)actor + 0x22, 0x1C, *callbackTable);
        }
        return 1;
    }
ret0:
    return 0;
}
