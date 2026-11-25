extern s32 sub_080A8AB0(void *, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script step: try to fire a projectile at the target; on success play the
 * fire sound and advance to the next command. */
void sub_080A72A8(void *obj) {
    u8 *self = (u8 *)obj;
    u8 *data = *(u8 **)(self + 0x3C);
    if (sub_080A8AB0(obj, data + 0x48) != 0) {
        s32 *lit;
        sub_08005E80(0x177);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
