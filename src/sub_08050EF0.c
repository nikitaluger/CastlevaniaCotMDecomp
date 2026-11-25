extern void sub_080520CC(void *a, void *b, s32 c);
extern void sub_08051D3C(void *a, void *b, s32 c, s32 d);
extern void sub_08051F98(void *a, void *b, s32 c, s32 d, s32 e);

/* Readable aliases for the game's helpers (preprocessor-only, no code effect). */
#define SpawnEffect       sub_080520CC
#define BuildArcTrail     sub_08051D3C
#define ArmScriptAdvance  sub_08051F98

/*
 * Effect step: when the current script value is a multiple of four (<= 0x77)
 * spawn one effect scaled by the entity's byte at 0x6C; when it is 0x96 reset
 * the pose timer, build the eight-point arc trail at work+0xF0, and arm the
 * 30-frame timer that advances the script.
 */
void sub_08050EF0(u8 *self)
{
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *body;
    s16 stepIdx, stepIdx2;
    u8 stepValue, stepValue2;
    body = work + 0x48;
    stepIdx = *(s16 *)(self + 0x22);
    stepValue = *(u8 *)(self + stepIdx * 2 + 0x19);
    if (stepValue <= 0x77) {
        if ((stepValue & 3) == 0) {
            SpawnEffect(self, body, 0x38000);
        }
    }
    stepIdx2 = *(s16 *)(self + 0x22);
    stepValue2 = *(u8 *)(self + stepIdx2 * 2 + 0x19);
    if (stepValue2 == 0x96) {
        *(u16 *)body = 0;
        BuildArcTrail(self, body + 0xA8, 0, 1);
        ArmScriptAdvance(self, body, 0x1E, 0, -2);
    }
}
