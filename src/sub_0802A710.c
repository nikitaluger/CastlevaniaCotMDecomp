extern s32 sub_08011368(s32 obj, s32 anim, s32 frame, s32 mode);

/* A host that owns a gameplay object and its animation-playback state. */
struct ActorAnimHost {
    u8 pad[0x38];
    s32 obj;   /* object whose +0x28 the animation player updates */
    s32 anim;  /* animation state; frame descriptors begin at +0x34 */
};

/* Switch the host's animation to frame 9, mode 1 (normal playback). */
void sub_0802A710(struct ActorAnimHost *actor) {
    sub_08011368(actor->obj, actor->anim + 0x34, 9, 1);
}
