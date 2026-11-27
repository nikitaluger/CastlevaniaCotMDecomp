extern void sub_08051D3C(void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

struct WorkState { u8 pad[0x20]; s16 step; u8 pad2[0x26]; u16 angle; };

/* Set up the work object's motion from the angle at +0x48, then advance that
 * angle by 0x10 (mod 0x100). Once its step counter at +0x20 reaches 1 or less,
 * clear this action's byte at +0x19 and run the handler at gScriptStepCallbacks[0]. */
void sub_08050F78(void *arg0) {
    u8 *self = (u8 *)arg0;
    struct WorkState *work = *(struct WorkState **)(self + 0x3C);
    u16 *anglePtr = &work->angle;
    s32 angle;
    s32 *handlerTable;
    sub_08051D3C(self, (u8 *)work + 0xA0, *anglePtr, 1);
    angle = work->angle;
    angle = angle + 0x10;
    work->angle = angle & 0xFF;
    if (work->step <= 1) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        handlerTable = (s32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *handlerTable);
    }
}
