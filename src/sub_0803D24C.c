extern void advanceMotion(s32, s32);
extern void sub_080C31E0(void *, s32);

/* Apply the fixed acceleration 0x16C1 to the entity's motion; once the current
 * script step's repeat counter reaches the limit stored at +0x8C, dispatch the
 * next script command. */
void sub_0803D24C(void *arg0) {
    advanceMotion(*(s32 *)((s8 *)arg0 + 0x3C), 0x16C1);
    if (*(u8 *)((*(s16 *)((s8 *)arg0 + 0x22) * 2) + arg0 + 0x19) == *(u8 *)((s8 *)arg0 + 0x8C)) {
        sub_080C31E0(arg0, *(s32 *)((s8 *)arg0 + 0x24));
    }
}
