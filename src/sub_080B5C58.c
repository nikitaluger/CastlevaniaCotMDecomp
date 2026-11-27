extern s32 getAngleFromDelta(s32 dy, s32 dx);
extern s32 fixedPointDistance(s32 dx, s32 dy);
extern void stepAnimationTrack(s32 sprite, void *moverData);
extern void advanceMotion(void *mover, s32 accel);
extern void setPolarOffset(void *mover, s32 angle, s32 speed);
extern void sub_0808D7BC(s32 x, s32 y, u32 id, u8 kind);
extern void sub_080C31E0(void *arg, void *func);

/* Chase script step: steers the mover toward the linked object and integrates its
 * velocity; once within range, advances the target's counter by a capped delta,
 * spawns an effect at the target and fires the callback stored at self+0x24. */
void sub_080B5C58(u8 *self) {
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *mover = *(u8 **)(self + 0x3C);
    u8 *targetMover;
    s32 targetX, targetY, yOffset, dy, dx, distance;
    s32 cur, delta, maxDelta;
    u32 animData = (u32)(mover + 0x34);
    targetMover = *(u8 **)(*(u8 **)(self + 0x28) + 0x3C);
    stepAnimationTrack(sprite, (void *)animData);
    targetX = *(s32 *)(targetMover + 8);
    targetY = *(s32 *)(targetMover + 0xC);
    yOffset = 0xFFF00000;
    targetY += yOffset;
    dy = targetY - *(s32 *)(mover + 0xC);
    dx = targetX - *(s32 *)(mover + 8);
    setPolarOffset(mover, getAngleFromDelta(dy, dx), 0x80 << 11);
    advanceMotion(mover, 0);
    targetX = targetX - *(s32 *)(mover + 8);
    targetY = targetY - *(s32 *)(mover + 0xC);
    distance = fixedPointDistance(targetX, targetY);
    if (distance <= 0x7FFFF) {
        u8 *target = *(u8 **)(self + 0x28);
        s32 targetParam = *(s32 *)(target + 0x4C);
        cur = *(s32 *)(targetMover + 0x18);
        delta = targetParam - cur;
        maxDelta = *(s32 *)(target + 0x5C);
        if (delta > maxDelta) delta = maxDelta;
        *(s32 *)(targetMover + 0x18) = cur + delta;
        sub_0808D7BC(*(s32 *)(targetMover + 8), *(s32 *)(targetMover + 0xC) + yOffset, delta, 2);
        sub_080C31E0(self, *(void **)(self + 0x24));
    }
}
