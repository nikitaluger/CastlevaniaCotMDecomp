/* Update a scripted effect: seed its random horizontal motion, run its
 * animation step, then handle the finish branch with a facing-dependent
 * speed and a follow-up script. */
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080269A8(void *, s32);
extern void sub_08026954(void *, void *);
extern s32 getSpriteFacingSign(void *);
extern void sub_080269D4(void *, s32);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbacks;

struct S_02025FF0 { u8 _0[0x189C]; u32 v; };
extern struct S_02025FF0 gMainWorkspace;

void sub_08026374(u8 *effect) {
    u8 *sprite = *((u8 **) (effect + 0x38));
    u8 *fxState = *((u8 **) (effect + 0x3C));
    u8 *motion = fxState + 0x34;
    u8 *state48 = fxState + 0x48;
    u8 randomFlag;

    *((u32 *) (fxState + 0x14)) = 0;
    *((u32 *) (fxState + 0x10)) = 0;
    randomFlag = motion[1];
    if (randomFlag == 1) {
        u32 globalRand = gMainWorkspace.v;
        s32 motionX = ((s32)(globalRand + (globalRand >> 31)) >> 1) & randomFlag;
        if (motionX != 0) motionX = 0x80 << 9;
        *((u32 *) (state48 + 0x14)) = motionX;
    }
    setAnimationFrame(sprite, motion, 5, 0);
    if (motion[1] == 2 && *((u32 *) (motion + 4)) == 1)
        sub_080269A8(effect, 8);
    if (motion[0] & 2) {
        s32 speed;
        s32 facing;
        sub_08026954(state48 + 8, state48 + 0xC);
        facing = getSpriteFacingSign(sprite);
        speed = 0xE0 << 8;
        if (facing < 0)
            speed = 0xA0 << 8;
        *((u32 *) (state48 + 0x38)) = speed;
        sub_080269D4(effect, 0x1C);
        {
            s16 stepIndex = *((s16 *) (effect + 0x22));
            effect[stepIndex * 2 + 0x19] = 0;
        }
        {
            void **scriptTable = &gScriptStepCallbacks;
            sub_080C31E8(effect + 0x18, effect + 0x22, 1, *scriptTable);
        }
        *((u16 *) (state48 + 0x1E)) = 1;
    }
}
