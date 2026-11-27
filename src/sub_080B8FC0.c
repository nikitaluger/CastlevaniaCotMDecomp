extern s32 stepAnimationTrack(s32, void *);
extern s32 advanceMotion(void *, s32);

struct Work {
    u8 pad_0x00[0x34];
    u8 anim;                    /* +0x34: animation/frame descriptor */
};

struct MainObj {
    u8 pad_0x00[0x38];
    s32 sprite;                 /* +0x38: sprite/animation owner */
    struct Work *work;          /* +0x3C: position/physics work area */
};

/* Advance this object's sprite animation, then integrate its work-area motion. */
void sub_080B8FC0(struct MainObj *obj) {
    s32 sprite = obj->sprite;
    struct Work *work = obj->work;

    stepAnimationTrack(sprite, (s8 *)work + 0x34);
    advanceMotion(work, 0);
}
