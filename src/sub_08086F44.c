void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_D02025FF0_h { u8 _0[0x10]; u32 enableFlag; };
extern struct S_D02025FF0_h D_02025FF0;

/* Script step: while the global enable flag is set, clear then bump the step
 * phase byte, advance the script and dispatch the new command's handler. */
void sub_08086F44(void *entity) {
    u8 *self = entity;
    if (D_02025FF0.enableFlag != 0) {
        u8 *stepCursor;
        s32 *scriptTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        stepCursor = self + 0x18;
        sub_080C31E4(stepCursor, self + 0x22, *scriptTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        stepCursor = stepCursor + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(entity, *(void **)((u32)*stepCursor * 4 + *(u32 *)(self + 0x14)));
    }
}
