/* Script-slot handler: applies the entity's contact recoil, then, once the
 * current script slot's timer has run for 30 frames, resets the timer and
 * runs the script handler from the gScriptStepCallbacks table. */
void sub_08048AC8(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 sprite;
    s32 work;
    s16 slot;
    s32 off;
    u8 *entry;

    sprite = *(s32 *)(self + 0x38);
    work = *(s32 *)(self + 0x3C);
    applyHomingContactRecoil(sprite, work + 0x34, work, work + 0x48);

    slot = *(s16 *)(self + 0x22);
    off = slot * 2;
    entry = (u8 *)off + (u32)self;
    if (*(u8 *)(entry + 0x19) == 0x1E) {
        u32 *handlerTable;
        *(u8 *)(entry + 0x19) = 0;
        handlerTable = (u32 *)0x08671BD0;
        sub_080C31E8(self + 0x18, self + 0x22, 0, *handlerTable);
    }
}
