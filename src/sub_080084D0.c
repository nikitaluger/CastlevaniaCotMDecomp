extern void sub_080C0574(void);
extern void sub_080C08D0(u32);
extern void sub_080C31E4(void *, void *, u32);
extern u32 D_0083FC00;

/* Script callback for substate 0x78: release the registered effect objects,
 * reset the sound channels, clear the current step's substate and dispatch the
 * next script command. */
void sub_080084D0(void *arg0) {
    u8 *self = arg0;
    s16 step = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + step * 2 + 0x19) == 0x78) {
        sub_080C0574();
        sub_080C08D0((u32)&D_0083FC00 & (0xF0 << 12));
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *cmdTable = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *cmdTable);
        }
    }
}
