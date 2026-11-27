void setObjectAnimation(s32, void *, s32, s32);
void sub_08011528(s32, void *);
void advanceMotion(void *, s32);

/* Animated two-pose cycle: play the current animation, toggle between poses
 * 0x45 and 0x47 when it finishes, then integrate the body's motion. */
void sub_080AE52C(void *arg0) {
    s32 scene;
    void *body;
    void *anim;

    scene = *(s32 *)((u8 *)arg0 + 0x38);
    body = *(void **)((u8 *)arg0 + 0x3C);
    anim = (u8 *)body + 0x34;
    sub_08011528(scene, anim);
    if (2 & *(u8 *)((u8 *)body + 0x34)) {
        if (*(s16 *)((u8 *)anim + 0xE) == 0x47) {
            setObjectAnimation(scene, anim, 0x45, 0);
        } else {
            setObjectAnimation(scene, anim, 0x47, 0);
        }
    }
    advanceMotion(body, 0);
}
