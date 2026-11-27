extern void stepAnimationTrack(void *, void *);
extern void sub_08045034(void *, void *);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *gScriptStepCallbackTable;
extern void *gScriptStepCallbacks;

/* Advance an object's animation, spawning an effect when its sprite enters a
 * particular state; when the animation finishes, cycle a counter that chooses
 * between two behavior-script continuations. */
void sub_08044AC0(void *arg0)
{
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    void *state = *(void **)((u8 *)arg0 + 0x3C);
    u8 *anim = (u8 *)state + 0x34;
    u8 *extra = (u8 *)state + 0x48;
    u16 oldState = *(u16 *)((u8 *)sprite + 0x28);

    stepAnimationTrack(sprite, anim);

    if (*(u16 *)((u8 *)sprite + 0x28) == 7 && *(u16 *)((u8 *)sprite + 0x28) != oldState) {
        sub_08045034(sprite, state);
    }

    if (anim[0] & 2) {
        s32 zero;
        s32 next;
        next = (s32)extra[6] + 1;
        zero = 0;
        extra[6] = (u8)next;
        if ((u8)next == 3) {
            setAnimationFrame(sprite, anim, 5, 0);
            ((u8 *)arg0)[*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19] = zero;
            {
                void **table = &gScriptStepCallbackTable;
                sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *table);
            }
        } else {
            setAnimationFrame(sprite, anim, 3, 1);
            ((u8 *)arg0)[*(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19] = zero;
            {
                void **table = &gScriptStepCallbacks;
                sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 5, *table);
            }
        }
    }
}
