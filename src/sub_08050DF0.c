extern void setAnimationFrame(s32, void *, s32, s32);
extern void stepAnimationTrack(s32, void *);
extern void sub_08051D3C(void *, void *, s32, s32);
extern void sub_08051F98(void *, void *, s32, s32, s32);

/* Weapon-swing step: play animation 0xA and advance it; on the script step that
 * starts the swing (step 0x14), reset the pose timer, rebuild the 8-point arc
 * trail stored at work+0xF0, and arm the 30-frame follow-up timer that will
 * advance the script. */
void sub_08050DF0(void *self) {
    s32 sprite = *(s32 *)((u8 *)self + 0x38);
    void *work = *(void **)((u8 *)self + 0x3C);
    void *anim = (u8 *)work + 0x34;
    void *body = (u8 *)work + 0x48;
    setAnimationFrame(sprite, anim, 0x0A, 0);
    stepAnimationTrack(sprite, anim);
    if (((u8 *)self)[(*(s16 *)((u8 *)self + 0x22)) * 2 + 0x19] == 0x14) {
        *(u16 *)body = 0;
        sub_08051D3C(self, (u8 *)work + 0xF0, 0, 1);
        sub_08051F98(self, body, 0x1E, 0, -2);
    }
}
