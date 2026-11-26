void sub_080627C8(void);
struct S_02021E90_H {
    u8 _0x000[0x1360];
    u8 fadeMode;   /* 0x1360 */
    u8 _0x1361[0x4D];
    u8 fadeLevel;  /* 0x13AE */
};
extern struct S_02021E90_H gCameraState;

/* Fade step: ramp the global fade level down from 0x10 to 0 in step with the
 * counter at entity+0x22 while the fade mode stays 6; once the counter reaches
 * 0x10, stop the fade, reset the counter and install the follow-up update. */
void sub_08062788(void *entity) {
    struct S_02021E90_H *state = &gCameraState;
    state->fadeLevel = 0x10 - *(u16 *)((u8 *)entity + 0x22);
    state->fadeMode = 6;
    if ((s16)*(u16 *)((u8 *)entity + 0x22) == 0x10) {
        state->fadeMode = 0;
        *(u16 *)((u8 *)entity + 0x22) = 0;
        *(u32 *)((u8 *)entity + 0x14) = (u32)sub_080627C8;
    }
}
