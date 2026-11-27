extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void setObjectAnimation(s32, void *, s32, s32);
extern void advanceAnimTrack(s32, void *);
extern void setSpriteFacingToTarget(s32, s32);

struct S_02025FF0_40 { u8 _pad[0x40]; u32 state; };
extern struct S_02025FF0_40 gMainWorkspace;

/* Set up the sprite's animation from the work state, update its visibility
 * flag from the work's x, and advance the script when the global state is 1. */
void sub_080B36F8(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *anim = work + 0x34;
    setObjectAnimation(sprite, anim, 0, 1);
    advanceAnimTrack(sprite, anim);
    setSpriteFacingToTarget(sprite, *(s32 *)(work + 8));
    if (gMainWorkspace.state == 1) {
        s32 *lit;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
