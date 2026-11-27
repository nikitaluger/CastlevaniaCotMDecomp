extern u8 gMainWorkspace[];
extern u32 D_080E572C[];
s32 sub_0806D35C(void *, void *, void *);
void sub_0806D588(void *, void *);
void startEffectTimer(void *, s32, s32);
void stepDelayTimer(void *, void *);

/* Updates a follower entity: if the current area's special behavior handled it
 * (sub_0806D35C returned nonzero) do nothing; otherwise copy the global target
 * position and the source's 0x10 flag, reinitialize its animation whenever the
 * global animation index changes, step the animation timer, and snap the state
 * object to the grid. */
void sub_0807FCD4(u8 *entity) {
    u8 *component;   /* entity+0x6C: motion component, +4 = target position */
    u8 *target;      /* component+4: target position vector */
    u8 *state;       /* entity+0x38: area-behavior state object */
    u8 *targetCopy;  /* saved target pointer for the final grid snap */
    component = *(u8 **)(entity + 0x6C);
    target = component + 4;
    state = *(u8 **)(entity + 0x38);
    targetCopy = target;
    if (sub_0806D35C(entity, state, target) != 0) return;
    {
        u8 *globals = gMainWorkspace;
        u32 value;
        u32 cachedIndex;
        u8 *sourceState;
        value = 0x14FC;
        *(u32 *)(component + 4) = *(u32 *)(globals + value);
        value += 4;
        *(u32 *)(target + 4) = *(u32 *)(globals + value);
        sourceState = *(u8 **)(*(u8 **)(entity + 0x28) + 0x38);
        *(u16 *)(state + 2) = 0x10 & *(u16 *)(sourceState + 2);
        value = *(u32 *)(globals + 0x14F8);
        if (value != 0) {
            u8 *animTimer;
            u32 animData;
            cachedIndex = *(u32 *)(target + 0x54);
            animTimer = component + 0x20;
            if (cachedIndex != value) {
                *(u32 *)(target + 0x54) = value;
                {
                    u32 tbl = (u32)D_080E572C;
                    value--;
                    value <<= 2;
                    value += tbl;
                    animData = *(u32 *)value;
                }
                startEffectTimer(animTimer, 0, animData);
            }
            stepDelayTimer(animTimer, state);
        } else {
            u8 *flags = state + 0x2A;
            *flags = 0xBF & *flags;
        }
    }
    sub_0806D588(state, targetCopy);
    {
        u8 *globalsEnd = gMainWorkspace;
        *(u32 *)(target + 0x54) = *(u32 *)(globalsEnd + 0x14F8);
    }
}
