/* Motion state at body+0x48: its first halfword is the status flag. */
struct MotionState {
    s16 status;
};

/* Flag the object's motion as complete (status = 1). */
void sub_08022754(void *obj) {
    u8 *body = *(u8 **)((u8 *)obj + 0x3C);
    ((struct MotionState *)(body + 0x48))->status = 1;
}
