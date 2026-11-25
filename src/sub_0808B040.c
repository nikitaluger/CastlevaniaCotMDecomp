extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script step: clear the work object's +0x30 field and the actor's current
 * action byte, advance the script through the shared dispatcher, then bump the
 * action byte and run the new command's handler from the actor's table. */
void sub_0808B040(void *arg0) {
    u8 *stepPtr;
    const u32 *scriptCb;
    *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x6C) + 0x30) = 0;
    *(u8 *)((u8 *)arg0 + (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = 0;
    scriptCb = (const u32 *)0x08671BB0;
    stepPtr = (u8 *)arg0 + 0x18;
    sub_080C31E4(stepPtr, (u8 *)arg0 + 0x22, *scriptCb);
    *(u8 *)((u8 *)arg0 + (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) += 1;
    stepPtr += (s32)*(s16 *)((u8 *)arg0 + 0x22) * 2;
    sub_080C31E0(arg0, *(u32 *)((u8 *)*(u32 *)((u8 *)arg0 + 0x14) + *(u8 *)stepPtr * 4));
}
