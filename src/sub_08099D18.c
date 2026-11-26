extern void setObjectAnimation(s32, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Script step 0x0A: play animation 0x28, clear the step byte and advance
 * to the next script step. */
void sub_08099D18(void *arg0) {
    s32 scene;
    u8 *body;
    void *anim;
    s16 stepIndex;
    u8 stepValue;
    s32 *stepTable;
    scene = *(s32 *)((u8 *)arg0 + 0x38);
    body = *(u8 **)((u8 *)arg0 + 0x3C);
    anim = body;
    anim = (u8 *)anim + 0x34;
    stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
    stepValue = *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19);
    if (stepValue == 0x0A) {
        setObjectAnimation(scene, anim, 0x28, 0);
        stepIndex = *(s16 *)((u8 *)arg0 + 0x22);
        *(u8 *)((u8 *)arg0 + stepIndex * 2 + 0x19) = 0;
        stepTable = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stepTable);
    }
}
