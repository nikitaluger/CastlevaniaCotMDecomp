void sub_08011368(void *, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);

/* Script step: unless the entity's parameter byte is 1, set its body animation
 * to frame 7, clear the current step byte and run the next script step. */
void sub_0809EE00(void *a) {
    void *scene = *(void **)((u8 *)a + 0x38);
    void *bodyBase = *(void **)((u8 *)a + 0x3C);
    void *anim = (u8 *)bodyBase + 0x34;
    s32 *stepTable;
    if (*((u8 *)a + 0x6C) != 1) {
        sub_08011368(scene, anim, 7, 0);
        *((u8 *)a + (*(s16 *)((u8 *)a + 0x22)) * 2 + 0x19) = 0;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)a + 0x18, (u8 *)a + 0x22, *stepTable);
    }
}
