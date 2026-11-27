extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern void sub_0800B888(void *, s32);
extern void sub_0800B9A8(s8, s32, s32);
extern void sub_080103A0(u8, u8);
extern s32 sub_080103F0(u8);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Global input state; the two key-input words live at +0x146C and +0x1470. */
struct InputState {
    u8 pad[0x146C];
    u16 buttons;    /* 0x146C: bit0 A, bit1 B */
    u16 pad146E;
    u16 direction;  /* 0x1470: d-pad bits */
};
extern struct InputState gCameraState;

/* Save-file menu entity: +0x50 is the source slot (never selectable) and
 * +0x54 the currently highlighted destination slot. */
struct SaveCopyMenuEntity {
    u8 _0[0x50];
    u8 srcSlot;
    u8 _51[3];
    s8 destSlot;
};
extern u32 gScriptStepCallbackTable[];
extern u32 D_08671BC0[];
extern u32 gScriptStepCallbacks[];

/* Save-copy menu cursor: the d-pad moves the highlighted destination slot over
 * the eight saves (skipping the source slot) and plays a move sound; B cancels
 * back to the menu script, A copies the source save into the chosen slot and
 * advances this actor's script. */
void updateSaveCopyMenu(struct SaveCopyMenuEntity *menu)
{
    s32 dataPtr = *(s32 *)((u8 *)menu + 0x3C);
    s32 oldSlot = menu->destSlot;
    u32 cancelPressed;
    s32 saveStatus;
    s32 newSlot;
    u8 slotBeforeSkip;

    if ((0x30 & gCameraState.direction) != 0x30)
    {
        if ((0x20 & gCameraState.direction) != 0)
        {
            newSlot = (u8)menu->destSlot - 1;
            menu->destSlot = newSlot;
            if ((s32)((s8)newSlot << 24) < 0)
                menu->destSlot = 7;
            slotBeforeSkip = (u8)menu->destSlot;
            if (menu->destSlot == (s8)menu->srcSlot)
            {
                newSlot = slotBeforeSkip - 1;
                menu->destSlot = newSlot;
                if ((s32)((s8)newSlot << 24) < 0)
                    menu->destSlot = 7;
            }
        }
        if ((0x10 & gCameraState.direction) != 0)
        {
            u8 zero;
            newSlot = (u8)menu->destSlot + 1;
            zero = 0;
            menu->destSlot = newSlot;
            if ((s8)newSlot == 8)
                menu->destSlot = zero;
            slotBeforeSkip = (u8)menu->destSlot;
            if (menu->destSlot == (s8)menu->srcSlot)
            {
                newSlot = slotBeforeSkip + 1;
                menu->destSlot = newSlot;
                if ((s8)newSlot == 8)
                    menu->destSlot = zero;
            }
        }
        if ((0x30 & gCameraState.direction) != 0)
            sub_08005E80(0x154);
    }

    cancelPressed = (u16)(gCameraState.buttons & 2);
    if (cancelPressed != 0)
    {
        sub_08005E80(0x159);
        menu->destSlot = -1;
        sub_0800B9A8(menu->destSlot, 2, dataPtr);
        sub_0800B824(0x81D6, 0x270, 0x600);
        *((u8 *)((u8 *)menu + *(s16 *)((u8 *)menu + 0x22) * 2 + 0x19)) = 0;
        {
            u32 *tbl = &D_08671BC0;
            sub_080C31E4((u8 *)menu + 0x18, (u8 *)menu + 0x22, *tbl);
        }
        return;
    }
    if (oldSlot != menu->destSlot)
        sub_0800B9A8(menu->destSlot, 2, dataPtr);
    if ((1 & gCameraState.buttons) != 0)
    {
        saveStatus = sub_080103F0((u8)menu->destSlot);
        if (saveStatus != 0)
        {
            sub_08005E80(0x157);
            sub_0800B824(0x81D8, 0x270, 0x600);
            *((u8 *)((u8 *)menu + *(s16 *)((u8 *)menu + 0x22) * 2 + 0x19)) = cancelPressed;
            {
                u32 *tbl = &gScriptStepCallbackTable;
                sub_080C31E4((u8 *)menu + 0x18, (u8 *)menu + 0x22, *tbl);
            }
            return;
        }
        sub_08005E80(0x15B);
        sub_080103A0(*(u8 *)((u8 *)menu + 0x50), (u8)menu->destSlot);
        sub_0800B9A8(menu->destSlot, 2, dataPtr);
        sub_0800B888(menu, dataPtr);
        sub_0800B824(0x81D9, 0x270, 0x600);
        *((u8 *)((u8 *)menu + *(s16 *)((u8 *)menu + 0x22) * 2 + 0x19)) = saveStatus;
        {
            u32 *tbl = &gScriptStepCallbacks;
            sub_080C31E8((u8 *)menu + 0x18, (u8 *)menu + 0x22, 3, *tbl);
        }
    }
}
