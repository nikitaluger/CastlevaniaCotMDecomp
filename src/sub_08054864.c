extern void setAnimationFrame(s32, s32, s16, s32);
extern s16 D_080CFB4C[];

/* Pick one of five animation frames according to which range a signed
 * phase/angle value falls into, then set it on the given animation state. */
void sub_08054864(s32 owner, s32 animCtrl, s16 angle) {
    s32 ownerCopy = owner;
    s32 animCopy = animCtrl;
    s32 phase = angle;
    s32 frameIdx;

    if (phase < (s32)0xFFFFD000)
        frameIdx = 0;
    else if (phase < (s32)0xFFFFF000)
        frameIdx = 1;
    else if (phase <= 0xFFF)
        frameIdx = 2;
    else if (phase <= 0x2FFF)
        frameIdx = 3;
    else
        frameIdx = 4;

    setAnimationFrame(ownerCopy, animCopy, D_080CFB4C[frameIdx], 0);
}
