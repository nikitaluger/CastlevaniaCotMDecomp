extern void playSound(s32);
extern void sub_08006210(void);
extern void sub_0800EB44(u16, s32, s32);
extern void _call_via_r3(void *, void *, s32, s32);

struct S_020278D0 {
    u8 _0[0x64];
    u8 chosenValue;
    u8 _65[3];
    s8 selection;
};
extern struct S_020278D0 gMenuState;

struct S_02021E90 {
    u8 _0[0x146C];
    u16 actionButtons;
    u8 _2[0x1470 - 0x146E];
    u16 dirButtons;
};
extern struct S_02021E90 gCameraState;

extern u8 gMenuGfxIdTable[];
extern u8 gMenuChoiceValueTable[];
extern u32 gMenuScriptCallback[];

/* Moves the five-way menu cursor from the held D-pad bits, redraws its icon and
 * plays a click when the choice changes, then dispatches the cancel or confirm
 * script command. */
void handleMenuSelectionInput(void *script)
{
    s32 previousSelection;
    u16 heldButtons;
    u16 pressedButtons;
    u32 cancelBits;

    previousSelection = gMenuState.selection;
    heldButtons = gCameraState.dirButtons;
    {
        u32 bothDirMask = MENU_INPUT_DIR_BOTH;

        bothDirMask &= heldButtons;
        if (bothDirMask != MENU_INPUT_DIR_BOTH) {
            u32 prevMask = MENU_INPUT_PREV;

            prevMask &= heldButtons;
            if (prevMask != 0) gMenuState.selection--;
            {
                u16 heldButtons2 = gCameraState.dirButtons;
                u32 nextMask = MENU_INPUT_NEXT;

                nextMask &= heldButtons2;
                if (nextMask != 0) gMenuState.selection++;
            }
            if (gMenuState.selection < 0) gMenuState.selection = FIVEWAY_MENU_MAX_INDEX;
            if (gMenuState.selection > FIVEWAY_MENU_MAX_INDEX) gMenuState.selection = 0;
        }
    }
    if (previousSelection != gMenuState.selection) {
        u8 *gfxIds;
        s32 selectedIndex;

        playSound(SFX_MENU_MOVE);
        gfxIds = gMenuGfxIdTable;
        selectedIndex = gMenuState.selection;
        sub_0800EB44(*(u16 *)(gfxIds + selectedIndex * 2), FIVEWAY_MENU_TILE_ROW, FIVEWAY_MENU_TILE_SIZE);
    }
    pressedButtons = gCameraState.actionButtons;
    cancelBits = FIVEWAY_MENU_CANCEL_BITS;
    cancelBits &= pressedButtons;
    if (cancelBits != 0) {
        playSound(SFX_MENU_CANCEL);
        sub_08006210();
        *(u8 *)((u8 *)script + *(s16 *)((u8 *)script + SCRIPT_STEP_INDEX_OFFSET) * 2 + FIVEWAY_STEP_TIMER_OFF) = 0;
        {
            u32 *callbackTable = gMenuScriptCallback;

            _call_via_r3((u8 *)script + SCRIPT_STEP_BASE_OFFSET, (u8 *)script + SCRIPT_STEP_INDEX_OFFSET, FIVEWAY_MENU_CANCEL_CMD, callbackTable[0]);
        }
        return;
    }
    {
        u32 confirmButton = MENU_INPUT_CONFIRM;

        confirmButton &= pressedButtons;
        if (confirmButton != 0) {
            playSound(SFX_MENU_CONFIRM);
            gMenuState.chosenValue = gMenuChoiceValueTable[gMenuState.selection];
            *(u8 *)((u8 *)script + *(s16 *)((u8 *)script + SCRIPT_STEP_INDEX_OFFSET) * 2 + FIVEWAY_STEP_TIMER_OFF) = cancelBits;
            {
                u32 *confirmCallbackTable = gMenuScriptCallback;

                _call_via_r3((u8 *)script + SCRIPT_STEP_BASE_OFFSET, (u8 *)script + SCRIPT_STEP_INDEX_OFFSET, FIVEWAY_MENU_CONFIRM_CMD, confirmCallbackTable[0]);
            }
        }
    }
}
