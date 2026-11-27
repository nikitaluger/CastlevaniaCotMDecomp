extern void setAnimationFrame(s32, void *, s32, s32);

void sub_0801E160(void *arg0) {
    u8 *script = (u8 *)arg0;
    s32 parent = *(s32 *)(script + 0x38);
    u8 *motion = *(u8 **)(script + 0x3C);
    u8 *anim = motion + 0x34;
    u8 *state = motion + 0x48;
    setAnimationFrame(parent, anim, 5, 0);
}
