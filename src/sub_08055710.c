struct S_080316BC {
    u8 _0x00[0x14];
    u32 funcTable;
    u8 _0x18[0x0A];
    s16 step;
    u32 field_0x24;
    u8 _0x28[0x10];
    u32 sprite;
    u32 state;
};
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BD0;

// Plays frame 9, runs one step callback, and on a negative angle restarts at the step-2 callback.
void sub_08055710(struct S_080316BC *obj)
{
    void *sprite;
    u8 *state;
    u8 *stepData;
    void *animState;
    s32 offset;

    sprite = (void *)obj->sprite;
    state = (u8 *)obj->state;
    animState = state + 0x34;
    state += 0x48;
    setAnimationFrame(sprite, animState, 0x09, 1);
    obj->funcTable = 0x0866E758;
    obj->step += 1;
    ((u8 *)obj)[obj->step * 2 + 0x19]++;
    offset = obj->step * 2;
    stepData = (u8 *)obj + 0x18;
    sub_080C31E0(obj, *(void **)(obj->funcTable + *(u8 *)(stepData + offset) * 4));
    obj->step -= 1;
    if (*(s16 *)(state + 6) < 0) {
        ((u8 *)obj)[obj->step * 2 + 0x19] = 0;
        {
            void **lit = &D_08671BD0;
            sub_080C31E8(stepData, (u8 *)obj + 0x22, 2, *lit);
        }
    }
}
