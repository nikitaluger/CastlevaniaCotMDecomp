/* Runs one step of a scripted effect: sets animation frame 0x02, dispatches to a
 * table routine selected by a per-step byte, and ends when the effect timer hits zero. */
struct S_080318B0 {
    u8 _0x00[0x14];
    u32 field_0x14;
    u8 _0x18[0x0A];
    s16 field_0x22;
    u32 field_0x24;
    u8 _0x28[0x10];
    u32 field_0x38;
    u32 field_0x3C;
};
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void *D_08671BD0;

void sub_080318B0(struct S_080318B0 *obj)
{
    void *owner;
    u8 *work;
    u8 *stateBytes;
    void *anim;
    s32 index2;

    owner = (void *)obj->field_0x38;
    work = (u8 *)obj->field_0x3C;
    anim = work + 0x34;
    work += 0x48;
    setAnimationFrame(owner, anim, 0x02, 0);
    obj->field_0x14 = 0x0866DC98;
    obj->field_0x22 += 1;
    ((u8 *)obj)[obj->field_0x22 * 2 + 0x19]++;
    index2 = obj->field_0x22 * 2;
    stateBytes = (u8 *)obj + 0x18;
    sub_080C31E0(obj, *(void **)(obj->field_0x14 + *(u8 *)(stateBytes + index2) * 4));
    obj->field_0x22 -= 1;
    if (*(s16 *)(work + 6) == 0) {
        ((u8 *)obj)[obj->field_0x22 * 2 + 0x19] = 0;
        {
            void **endFuncs = &D_08671BD0;
            sub_080C31E8(stateBytes, (u8 *)obj + 0x22, 0, *endFuncs);
        }
    }
}
