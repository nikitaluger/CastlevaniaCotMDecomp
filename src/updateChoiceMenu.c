extern void playSound(s32);
extern void sub_080C31E4(void *, void *, void *);

extern struct ChoiceMenuCameraInput gCameraState;
extern struct ChoiceMenuMainInput gMainWorkspace;
extern u8 gChoiceMenuOptionTable[];
extern void *gMainObjTimerCallbacks;

/* Handles a two-option (confirm/cancel) menu: moves the highlighted option with
 * the prev/next buttons, plays a cursor sound when it changes, then on confirm
 * or cancel finishes the menu's current script step. */
void updateChoiceMenu(void *menuObj)
{
    u8 *menu = (u8 *)menuObj;
    u8 *workState = *(u8 **)(menu + 0x6C) + 4;
    void **optionDisplay = *(void ***)(menu + 0x38);
    u32 *choiceOptions = (u32 *)(gChoiceMenuOptionTable + (*(u32 *)(workState + 0x30) << 4));
    s32 previousChoice = gMainWorkspace.choice;

    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_NEXT) goto check_both;
        goto do_lr;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_NEXT) goto check_both;
        goto do_lr;
    }

check_both:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_PREV) goto after_lr;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_PREV) goto after_lr;
    }

do_lr:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_NEXT) goto set1;
        goto check2;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_NEXT) goto set1;
        goto check2;
    }
set1:
    gMainWorkspace.choice = 1;
    *(u32 *)((u8 *)optionDisplay + 0x24) = *(u32 *)((u8 *)choiceOptions + 8);
check2:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_PREV) goto set0;
        goto after_lr;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_PREV) goto set0;
        goto after_lr;
    }
set0:
    gMainWorkspace.choice = 0;
    *(u32 *)((u8 *)optionDisplay + 0x24) = *(u32 *)((u8 *)choiceOptions + 0xC);

after_lr:
    if (previousChoice != gMainWorkspace.choice) playSound(0x153);

    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_CONFIRM) goto confirm;
        goto cancel_check;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_CONFIRM) goto confirm;
        goto cancel_check;
    }

confirm:
    if (*(u32 *)(workState + 0x30) == 0 && gMainWorkspace.choice == 1)
        playSound(0x96 << 1);
    *(u8 *)(menu + *(s16 *)(menu + 0x22) * 2 + 0x19) = 0;
    {
        void **stepCallback = &gMainObjTimerCallbacks;
        sub_080C31E4(menu + 0x18, menu + 0x22, *stepCallback);
    }
    return;

cancel_check:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & CHOICE_MENU_CANCEL) goto cancel;
        return;
    } else {
        if (gCameraState.buttons & CHOICE_MENU_CANCEL) goto cancel;
        return;
    }

cancel:
    gMainWorkspace.choice = 0;
    *(u32 *)((u8 *)optionDisplay + 0x24) = *(u32 *)((u8 *)choiceOptions + 0xC);
    *(u8 *)(menu + *(s16 *)(menu + 0x22) * 2 + 0x19) = 0;
    {
        void **stepCallback = &gMainObjTimerCallbacks;
        sub_080C31E4(menu + 0x18, menu + 0x22, *stepCallback);
    }
}
