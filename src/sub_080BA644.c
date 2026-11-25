void sub_080BB940(void *ctrl, void *obj);
void sub_080C31E4(void *base, void *index, s32 table);

/* Script-step callback: let the companion update its shared control block, then
 * once the companion's state reaches 2, clear the block's counter and advance
 * the script to the next step. */
void sub_080BA644(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *ctrl = *(void **)(self + 0x3C);
    u8 *ctx = (u8 *)ctrl + 0x48;
    void *obj = *(void **)(self + 0x4C);
    sub_080BB940(ctrl, obj);
    if (*(u8 *)((u8 *)obj + 0x25) == 2) {
        *(s32 *)(ctx + 0x68) = 0;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *stepTable;
            stepTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *stepTable);
        }
    }
}
