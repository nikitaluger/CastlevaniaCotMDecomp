extern void sub_080113A8(void *sprite, void *animTrack);
extern void sub_080C31E4(void *stepBase, void *stepIndex, s32 handler);
extern void copyPoseAttrs(void *hitbox, void *record);
extern u8 D_080CEDB4[];             /* 8 hitbox records, four halfwords each */

/* Update an actor's sprite for this frame: step the animation track, restart the
 * script step when the animation asks for it, and install the attack hitbox that
 * matches the current animation frame (frame / 7 selects one of 8 records). */
void sub_08033EB4(u8 *entity) {
    u8 *sprite = *(u8 **)(entity + 0x38);
    u8 *motion = *(u8 **)(entity + 0x3C);
    u8 *animTrack = motion + 0x34;
    u8 *motionState = motion + 0x48;
    s32 pose = 0;
    u8 *hitbox = *(u8 **)(motionState + 0x0C);
    void **handlerTable;
    *(hitbox + 1) = 1;
    sub_080113A8(sprite, animTrack);
    if (*animTrack & 2) {
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = pose;
        handlerTable = (void **)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*handlerTable);
    }
    switch (*(u16 *)(sprite + 0x28)) {
    case 62: case 69: case 76: case 83: pose = 1; break;
    case 90: case 97: case 104: case 111: pose = 2; break;
    case 118: case 125: case 132: case 139: case 146: pose = 3; break;
    case 159: case 164: case 169: case 174: case 179: case 186: case 193: case 200: pose = 4; break;
    case 207: case 214: case 221: case 228: pose = 5; break;
    case 235: case 242: case 249: case 256: pose = 6; break;
    case 263: case 270: case 277: case 284: case 291: pose = 7; break;
    }
    copyPoseAttrs(*(u8 **)(motionState + 0x0C), &D_080CEDB4[pose * 8]);
}
