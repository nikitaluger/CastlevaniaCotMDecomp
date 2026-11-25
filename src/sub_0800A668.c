extern void sub_08005E80(s32);
extern void sub_0800B824(u16, s32, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern s32 D_020278D0;
extern u8 D_080CAABA[];
extern u16 D_080CAABE[];
extern void *D_08671BD8;
struct InputState { u8 _0[0x146C]; u16 buttons146C; u8 _146E[2]; u16 buttons1470; };
extern struct InputState D_02021E90;

/* Handles directional input for a scripted menu: moves the selection by rows or
 * columns, plays a sound and updates a value table when it changes, then dispatches
 * a confirm or cancel command to the script. */
void sub_0800A668(u8 *script) {
    u8 *menu = *(u8 **)(script + 0x3C);
    u8 selection = *(u8 *)(menu + 0x636);
    u16 buttons;
    u8 zero;
    u8 *statePtr;
    u8 *selectionPtr;
    u16 pressButtons;
    u16 selectionFlag;
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

    buttons = D_02021E90.buttons1470;
    if ((buttons & 0xC0) != 0xC0) {
        if (buttons & 0x40) {
            if (selection > 1) *(u8 *)(menu + 0x636) = selection - 2;
        } else {
            mask80 = 0x80;
            mask80 &= buttons;
            if (mask80) {
                if (selection <= 1) *(u8 *)(menu + 0x636) = selection + 2;
            }
        }
    }
    buttons = D_02021E90.buttons1470;
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
    statePtr = menu + 0x628;
    data = *(u8 **)statePtr;
    selectionPtr = menu + 0x636;
    selectionCopy = *(u8 *)selectionPtr;
    data44 = data + 0x44;
    zero = 0;
    *data44 = selectionCopy;
    if (selection != *(u8 *)selectionPtr) {
        sub_08005E80(0x153);
        soundTable = D_080CAABE;
        sub_0800B824(soundTable[*(u8 *)selectionPtr], 0x9C << 2, 0xC0 << 3);
    }
    pressButtons = D_02021E90.buttons146C;
    selectionFlag = pressButtons & 2;
    if (selectionFlag != 0) {
        sub_08005E80(0x159);
        *(u8 *)(*(u8 **)statePtr + 0x40) = zero;
        D_020278D0 = 1;
        {
            u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
            scriptState[0x17] = zero;
        }
        {
            void **cmdTable = &D_08671BD8;
            sub_080C31E8(script + 0x18, script + 0x22, 0x11, *cmdTable);
        }
    } else {
        mask01 = 1;
        mask01 &= pressButtons;
        if (mask01) {
            sub_08005E80(0x155);
            *(u8 *)(*(u8 **)statePtr + 0x40) = selectionFlag;
            valueTable = D_080CAABA;
            tableVal = *(u8 *)(valueTable + *(u8 *)selectionPtr);
            altSelectionPtr = menu + 0x635;
            *altSelectionPtr = tableVal;
            {
                u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
                scriptState[0x17] = selectionFlag;
            }
            {
                void **cmdTable = &D_08671BD8;
                sub_080C31E8(script + 0x18, script + 0x22, 0x10, *cmdTable);
            }
        }
    }
}
