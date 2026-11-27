extern void moveEntityWithCollision(void *, s32);
extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Ballistic actor update: integrate its movement with the stored acceleration,
 * play the falling animation while it descends faster than 2.0, and hand control
 * back to its update callback once it has hit something. */
void sub_080AA860(void *arg0) {
    u8 *actor = (u8 *)arg0;
    s32 sprite = *(s32 *)(actor + 0x38);
    u8 *work = *(u8 **)(actor + 0x3C);
    u8 *anim = work + 0x34;
    moveEntityWithCollision(work, *(s32 *)(actor + 0x4C));
    if (*(s32 *)(work + 0x14) > (0x80 << 10)) {
        setAnimationFrame(sprite, anim, 0xC, 0);
    }
    if (*(u16 *)(work + 2) != 0) {
        sub_080C31E0(arg0, *(s32 *)(actor + 0x24));
    }
}
