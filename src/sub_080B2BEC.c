void stepAnimationTrack(void *, void *);

/* Actor state struct: +0x04 frame timer, +0x28 linked object, +0x38 sprite,
 * +0x3C work block, +0x5C cached animation contact code. */
struct B2_Outer {
    u8 pad0[4];
    u32 timer;
    u8 pad8[0x20];
    void *linked;
    u8 pad2C[0xC];
    void *sprite;
    void *work;
    u8 pad40[0x1C];
    u16 contactCode;
};

/* Work block's animator at work+0x34: flags, current step, frame table and
 * current frame index. */
struct B2_Sub {
    u8 flags;
    u8 step;
    u8 pad2[6];
    void *frames;
    u8 padC[2];
    s16 frame;
};

/* Animation step: advance the sprite animator, mirror the new frame's contact
 * code into the cached value at +0x5C (nudging the linked object's u16 fields
 * at +6/+0xA by 4 when it changes), and on frame 240 signal the linked object
 * (u16 at +0x64). */
void sub_080B2BEC(void *arg0) {
    struct B2_Outer *self = (struct B2_Outer *)arg0;
    u8 *work; void *sprite; struct B2_Sub *anim; u8 **frames; u8 *table; s32 idx; u8 *entry; u16 newCode; u16 *cached; u8 *linked; s32 timer;
    sprite = self->sprite;
    work = (u8 *)self->work;
    anim = (struct B2_Sub *)(work + 0x34);
    stepAnimationTrack(sprite, anim);
    frames = (u8 **)anim->frames;
    idx = anim->frame + anim->step;
    table = *frames;
    entry = (u8 *)((idx << 2) + (s32)table) - 4;
    cached = &self->contactCode;
    newCode = *(u16 *)(entry + 2);
    if (newCode != *cached) {
        *cached = newCode;
        linked = *(u8 * volatile *)(work + 0x28);
        *(u16 *)(linked + 6) += 4;
        linked = *(u8 * volatile *)(work + 0x28);
        *(u16 *)(linked + 0xA) -= 4;
    }
    timer = self->timer + 1;
    self->timer = timer;
    if (timer == 0xF0) *(u16 *)((u8 *)self->linked + 0x64) = 1;
}
