extern void sub_080B71AC(void *, s32, s32, s32);
extern s32 sub_080C31E0(s32, s32);

#define ANGLE_QUARTER 0x4000
#define ANGLE_STEP 0x1800
#define EFFECT_LAST 5U

/* Spawns a ring of six effects evenly spaced around (centerX, centerY):
 * for each angle place one object at center + cos/sin(angle) * 8. */
void sub_080B71CC(void *entity, s32 centerX, s32 centerY) {
    s32 posX;
    s32 angle;
    u32 i;

    angle = 0x8400;
    i = 0;
    do {
        posX = (sub_080C31E0(angle + ANGLE_QUARTER, *(s32 *)0x08671BFC) * 8) + centerX;
        sub_080B71AC(entity, posX, (sub_080C31E0(angle, *(s32 *)0x08671BFC) * 8) + centerY, angle);
        angle += ANGLE_STEP;
        i += 1;
    } while (i <= EFFECT_LAST);
}
