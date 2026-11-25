extern void sub_08011898(void *, s32);
extern void sub_0808DBB4(s32, s32, s32);

/* Launch the projectile (spawn id 0x2D82); every 16th script step, spawn a
 * short-lived effect just below the work area's recorded position. */
void sub_080470F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *work = *(u8 **)(self + 0x3C);
    sub_08011898(work, 0x2D82);
    if (!(0xF & *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))) {
        sub_0808DBB4(*(s32 *)(work + 8), *(s32 *)(work + 0xC) + 0x40000, 8);
    }
}
