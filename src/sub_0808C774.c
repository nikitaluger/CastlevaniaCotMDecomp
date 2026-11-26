extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, void *);

struct Alt { u8 pad[0x146C]; u16 buttons; };
struct Sys { u8 p0[0x24]; u32 inputSource; u16 buttons; u8 p1[0x1486]; u32 choice; };
extern struct Alt gCameraState;
extern struct Sys gMainWorkspace;
extern u8 D_080F3DFC[];
extern void *gMainObjTimerCallback;

#define BTN_CONFIRM 1
#define BTN_CANCEL  2
#define BTN_PREV    0x10
#define BTN_NEXT    0x20

/* A two-option Yes/No style prompt. Moves the selection with the prev/next
 * buttons (ignoring both at once), plays a sound when it changes, then acts on
 * confirm or cancel by advancing the menu's script step. */
void sub_0808C774(void *arg0)
{
    u8 *menu = (u8 *)arg0;
    u8 *actionState = *(u8 **)(menu + 0x6C) + 4;
    void **display = *(void ***)(menu + 0x38);
    u32 *options = (u32 *)(D_080F3DFC + (*(u32 *)(actionState + 0x30) << 4));
    s32 oldChoice = gMainWorkspace.choice;

    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_NEXT) goto check_both;
        goto do_lr;
    } else {
        if (gCameraState.buttons & BTN_NEXT) goto check_both;
        goto do_lr;
    }

check_both:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_PREV) goto after_lr;
    } else {
        if (gCameraState.buttons & BTN_PREV) goto after_lr;
    }

do_lr:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_NEXT) goto set1;
        goto check2;
    } else {
        if (gCameraState.buttons & BTN_NEXT) goto set1;
        goto check2;
    }
set1:
    gMainWorkspace.choice = 1;
    *(u32 *)((u8 *)display + 0x24) = *(u32 *)((u8 *)options + 8);
check2:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_PREV) goto set0;
        goto after_lr;
    } else {
        if (gCameraState.buttons & BTN_PREV) goto set0;
        goto after_lr;
    }
set0:
    gMainWorkspace.choice = 0;
    *(u32 *)((u8 *)display + 0x24) = *(u32 *)((u8 *)options + 0xC);

after_lr:
    if (oldChoice != gMainWorkspace.choice) sub_08005E80(0x153);

    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_CONFIRM) goto confirm;
        goto cancel_check;
    } else {
        if (gCameraState.buttons & BTN_CONFIRM) goto confirm;
        goto cancel_check;
    }

confirm:
    if (*(u32 *)(actionState + 0x30) == 0 && gMainWorkspace.choice == 1)
        sub_08005E80(0x96 << 1);
    *(u8 *)(menu + *(s16 *)(menu + 0x22) * 2 + 0x19) = 0;
    {
        void **stepTable = &gMainObjTimerCallback;
        sub_080C31E4(menu + 0x18, menu + 0x22, *stepTable);
    }
    return;

cancel_check:
    if (gMainWorkspace.inputSource != 0) {
        if (gMainWorkspace.buttons & BTN_CANCEL) goto cancel;
        return;
    } else {
        if (gCameraState.buttons & BTN_CANCEL) goto cancel;
        return;
    }

cancel:
    gMainWorkspace.choice = 0;
    *(u32 *)((u8 *)display + 0x24) = *(u32 *)((u8 *)options + 0xC);
    *(u8 *)(menu + *(s16 *)(menu + 0x22) * 2 + 0x19) = 0;
    {
        void **stepTable = &gMainObjTimerCallback;
        sub_080C31E4(menu + 0x18, menu + 0x22, *stepTable);
    }
}
