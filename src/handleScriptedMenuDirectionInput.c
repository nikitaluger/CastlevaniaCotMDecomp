struct InputState { u8 _0[0x146C]; u16 pressedButtons; u8 _146E[2]; u16 heldButtons; };
extern void playSound(s32);
extern void sub_0800B824(u16, s32, s32);
extern void _call_via_r3(void *, void *, s32, void *);
extern s32 gMenuState;
extern u8 gMenuValueTable[];
extern u16 gMenuSoundTable[];
extern void *gMenuScriptCallback;
extern struct InputState gCameraState;

/* Handles directional input for a scripted menu: moves the selection by rows
 * or columns, plays a sound and stores the selected value when it changes, then
 * dispatches a confirm or cancel command to the script. */
void handleScriptedMenuDirectionInput(u8 *script)
{
    u8 *menu = *(u8 **)(script + 0x3C);
    u8 selection = *(u8 *)(menu + 0x636);
    u16 buttons;
    u8 zero;
    u8 *stateSlot;
    u8 *selectionPtr;
    u16 pressButtons;
    u16 cancelBit;
    u8 selection2;
    u8 *data;
    u8 selectionCopy;
    u8 *data44;
    u8 tableVal;
    u8 *altSelectionPtr;
    u8 *valueTable;
    u16 *soundTable;
    u32 mask80;
    u32 mask10;
    u32 mask01;

    buttons = gCameraState.heldButtons;
    if ((buttons & MENU_INPUT_DIR_BOTH) != MENU_INPUT_DIR_BOTH) {
        if (buttons & MENU_INPUT_PREV) {
            if (selection > 1) *(u8 *)(menu + 0x636) = selection - 2;
        } else {
            mask80 = MENU_INPUT_NEXT;
            mask80 &= buttons;
            if (mask80) {
                if (selection <= 1) *(u8 *)(menu + 0x636) = selection + 2;
            }
        }
    }
    buttons = gCameraState.heldButtons;
    if ((buttons & 0x30) != 0x30) {
        if (buttons & 0x20) {
            selection2 = *(u8 *)(menu + 0x636);
            if (selection2 & 1) *(u8 *)(menu + 0x636) = selection2 - 1;
        } else {
            mask10 = 0x10;
            mask10 &= buttons;
            if (mask10) {
                selection2 = *(u8 *)(menu + 0x636);
                if (!(selection2 & 1)) *(u8 *)(menu + 0x636) = selection2 + 1;
            }
        }
    }
    stateSlot = menu + 0x628;
    data = *(u8 **)stateSlot;
    selectionPtr = menu + 0x636;
    selectionCopy = *(u8 *)selectionPtr;
    data44 = data + 0x44;
    zero = 0;
    *data44 = selectionCopy;
    if (selection != *(u8 *)selectionPtr) {
        playSound(SCRIPT_MENU_MOVE_SFX);
        soundTable = gMenuSoundTable;
        sub_0800B824(soundTable[*(u8 *)selectionPtr], 0x9C << 2, 0xC0 << 3);
    }
    pressButtons = gCameraState.pressedButtons;
    cancelBit = pressButtons & MENU_INPUT_CANCEL;
    if (cancelBit != 0) {
        playSound(SCRIPT_MENU_CANCEL_SFX);
        *(u8 *)(*(u8 **)stateSlot + 0x40) = zero;
        gMenuState = 1;
        {
            u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
            scriptState[0x17] = zero;
        }
        {
            void **callbackSlot = &gMenuScriptCallback;
            _call_via_r3(script + 0x18, script + 0x22, SCRIPT_MENU_CANCEL_CMD, *callbackSlot);
        }
    } else {
        mask01 = MENU_INPUT_CONFIRM;
        mask01 &= pressButtons;
        if (mask01) {
            playSound(SCRIPT_MENU_CONFIRM_SFX);
            *(u8 *)(*(u8 **)stateSlot + 0x40) = cancelBit;
            valueTable = gMenuValueTable;
            tableVal = *(u8 *)(valueTable + *(u8 *)selectionPtr);
            altSelectionPtr = menu + 0x635;
            *altSelectionPtr = tableVal;
            {
                u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
                scriptState[0x17] = cancelBit;
            }
            {
                void **callbackSlot = &gMenuScriptCallback;
                _call_via_r3(script + 0x18, script + 0x22, SCRIPT_MENU_CONFIRM_CMD, *callbackSlot);
            }
        }
    }
}
