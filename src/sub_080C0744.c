void sub_080C31E0(void *obj, u32 handler);

/* Call the sound engine's per-channel callback registered at 0x030040C8. */
void sub_080C0744(void *chan) {
    sub_080C31E0(chan, *(s32 *)0x030040C8);
}
