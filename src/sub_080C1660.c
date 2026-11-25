void sub_080C31E4(void *owner, void *task, u32 handler);

/* Run the sound-engine handler (function pointer stored at 0x03004040) on
 * this owner/task pair. */
void sub_080C1660(void *owner, void *task) {
    sub_080C31E4(owner, task, *(s32 *)0x03004040);
}
