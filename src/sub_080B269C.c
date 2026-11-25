s32 sub_080C050C(s32); /* start the sound/music cue with the given id */
void sub_080C31E4(void *, void *, s32);

/* Script command: once the entity's wait counter (+0x64) is set, clear the
 * active flag on every linked child effect, restart music cue 0x180, clear the
 * current script step and advance to the next command. */
void sub_080B269C(void *arg0) {
    void *effect;

    if (*(u16 *)((u8 *)arg0 + 0x64) != 0) {
        effect = *(void **)((u8 *)arg0 + 0x30);
        if (effect != NULL) {
            do {
                *(s8 *)(*(void **)(*(void **)((u8 *)effect + 0x3C) + 0x28) + 1) = 0;
                effect = *(void **)((u8 *)effect + 0x2C);
            } while (effect != NULL);
        }
        sub_080C050C(0x180);
        *(s8 *)((*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u8 *)arg0 + 0x19) = 0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *(s32 *)0x08671BB0);
    }
}
