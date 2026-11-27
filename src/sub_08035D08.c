void stepAnimationTrack(s32, u8 *);
void sub_08035DEC(s32, u8 *);
void sub_080C31E0(void *, s32);

/* Update the object attached to this entity's owner: mirror the owner's sprite
 * according to the entity flag, advance its animation, then either run the
 * entity's script or refresh the two attached child objects. */
void sub_08035D08(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 owner = *(s32 *)(self + 0x38);
    u8 *attached = *(u8 **)(self + 0x3C);
    u8 *animState = attached + 0x34;
    u8 *children = attached + 0x48;
    s16 idx;
    u8 *attr;
    s32 value;

    idx = *(s16 *)(self + 0x22);
    if (*(u8 *)(self + idx * 2 + 0x19) & 1) {
        attr = (u8 *)(owner + 0x2A);
        value = 0xBF & *attr;
        *attr = value;
    } else {
        attr = (u8 *)(owner + 0x2A);
        value = 0x40 | *attr;
        *attr = value;
    }
    stepAnimationTrack(owner, animState);
    if (*(u8 *)animState & 2) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
    } else {
        sub_08035DEC(owner, children);
    }
}
