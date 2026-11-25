void sub_08011368(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Play sprite animation 0x1A on the entity (animation state at work+0x34); if
 * the animation's finished flag (bit 1 of its state byte) is set, clear the
 * current step byte and advance the entity's command script. */
void sub_0801D014(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    sub_08011368((s32)sprite, work + 0x34, 0x1A, 0);
    if (2 & work[0x34]) {
        void **scriptTable;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = 0;
        scriptTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, (s32)*scriptTable);
    }
}
