struct S_02025FF0_49EBC {
    u8 _0[0x174C];
    u32 f174C;
    u32 f1750;
};
extern struct S_02025FF0_49EBC gMainWorkspace;
extern void *gMainObjTimerCallback;
extern s32 sub_08005910(s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_0804A4D0(void *, void *, void *, s32);
extern s32 sub_0804A4F0(void *, void *, void *, void *);
extern void sub_0804A650(void *, void *, void *);
extern void sub_080C31E4(void *, void *, void *);

/* Steps an enemy's attack decision: after its AI update, if its one-shot flag
 * is clear and the angle to the player falls in the firing window (mirrored
 * when facing the other way), it triggers the attack, sets the flag and calls
 * the notify callback. */
void sub_08049EBC(u8 *object) {
    void *sprite = *(void **)(object + 0x38);
    u8 *state = *(u8 **)(object + 0x3C);
    u8 *pose = state + 0x34;
    u8 *ctrl = state + 0x48;
    u32 firedFlag;
    s32 angle;
    sub_0801165C(state, 0);
    sub_0804A650(object, state, ctrl);
    if (sub_0804A4F0(sprite, pose, state, ctrl) != 0) {
        firedFlag = *(u8 *)(ctrl + 9);
        if (firedFlag == 0) {
            angle = sub_08005910(gMainWorkspace.f1750 - *(s32 *)(state + 0xC), gMainWorkspace.f174C - *(s32 *)(state + 8));
            if (*(u16 *)(sprite + 2) & 0x10) {
                angle = (0x8000 - angle) & 0xFFFF;
            }
            if ((u32)(angle + 0xFFFFA7FF) <= 0xFFE) {
                *(u8 *)(ctrl + 9) = 1;
                sub_0804A4D0(sprite, pose, ctrl, 0xC);
                (object + *(s16 *)(object + 0x22) * 2)[0x19] = (u8)firedFlag;
                {
                    void **callback = &gMainObjTimerCallback;
                    sub_080C31E4(object + 0x18, object + 0x22, *callback);
                }
            }
        }
    }
}
