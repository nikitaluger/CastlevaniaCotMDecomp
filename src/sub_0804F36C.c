extern s32 sub_08014A6C(void *, s32, s32, s32);
extern s32 sub_080C31E4(void *, void *, s32);

/* When the work's tracked value reaches its target, clear this script slot's
 * byte and advance the script through the 0x08671BB4 callback. */
void sub_0804F36C(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    s32 *scriptCb;
    if (sub_08014A6C(work, *(s32 *)(work + 0x50), 0x4000, 0) == 1) {
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x17) = 0;
        scriptCb = (s32 *)0x08671BB4;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptCb);
    }
}
