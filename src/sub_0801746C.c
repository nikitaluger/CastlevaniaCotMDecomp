s32 signOf(s32);
s32 getSpriteFacingSign(s32);
s32 rollProbability(s16);
void sub_080186C0(s32, s32);
void sub_080186DC(s32, s32);
void sub_080C31E4(void *, void *, u32);

struct S_02025FF0_174C { u8 _0x000[0x174C]; u32 referenceX; };
extern struct S_02025FF0_174C gMainWorkspace;
extern u32 gMainObjTimerCallbacks;

/* When its countdown expires, flips a patrolling entity's direction and
 * clamps its X position to a bounded range around a reference point. */
void sub_0801746C(void *entity) {
    void *sprite;
    u8 *motion;
    u8 *control;
    s32 stepSize;
    u8 zero;
    u8 *self = (u8*)entity;

    sprite = *(void **)(self + 0x38);
    motion = *(u8 **)(self + 0x3C);
    control = motion + 0x48;
    *(u16 *)(control + 0x16) = *(u16 *)(control + 0x16) - 1;
    if ((s16)*(u16 *)(control + 0x16) < 0) {
        if (rollProbability((s16)*(s16 *)(control + 0x28)) == 1) {
            stepSize = 0xB0 << 15;
            sub_080186DC((s32)(motion + 0x70), 0xFA << 2);
        } else {
            stepSize = 0xF0 << 14;
            sub_080186C0((s32)(motion + 0x70), 0xFA << 2);
        }
        if (signOf(*(s32 *)(motion + 0x08)) < 0) {
            s32 newPos = gMainWorkspace.referenceX - stepSize;
            s32 bound;
            *(s32 *)(motion + 0x08) = newPos;
            bound = *(s32 *)(control + 0x00) + (s32)0xFF000000;
            if (newPos < bound) {
                *(s32 *)(motion + 0x08) = gMainWorkspace.referenceX + stepSize;
            }
        } else {
            s32 newPos = gMainWorkspace.referenceX + stepSize;
            s32 bound;
            *(s32 *)(motion + 0x08) = newPos;
            bound = *(s32 *)(control + 0x00) + 0x1000000;
            if (newPos > bound) {
                *(s32 *)(motion + 0x08) = gMainWorkspace.referenceX - stepSize;
            }
        }
        if (getSpriteFacingSign((s32)sprite) > 0)
            *(s32 *)(motion + 0x10) = 0xC0 << 11;
        else
            *(s32 *)(motion + 0x10) = 0xFFFA0000;
        zero = 0;
        *(u16 *)(control + 0x16) = 5;
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            u32 *scriptTable = &gMainObjTimerCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
        }
    }
}
