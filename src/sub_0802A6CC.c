s32 setAnimationFrame(s32, void *, s32, s32);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
s32 sub_080C364C(s32, s32);
s32 sub_080C31E0(s32, s32);
s32 sub_0800583C(s32);

/* Play sprite animation 5 on the entity (animation state at work+0x34); if the
 * animation's finished flag (bit 1 of its state byte) is set, clear the current
 * step byte and advance the entity's command script. */
void sub_0802A6CC(void *arg0) {
    s32 sprite = *(s32 *)((u8 *)arg0 + 0x38);
    void *anim = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x34;
    setAnimationFrame(sprite, anim, 5, 0);
    if (*(u8 *)anim & 2) {
        s32 step = *(s16 *)((u8 *)arg0 + 0x22);
        s32 *script;
        *(u8 *)((u8 *)arg0 + step * 2 + 0x19) = 0;
        script = (s32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *script);
    }
}
