extern u8 D_0866D57C[];
extern u8 D_0866D56C[];
extern u32 gMainObjTimerCallback;
extern u32 D_08671BD8;

void _call_via_r1(void *, void *);
void _call_via_r2(void *, void *, u32);
void _call_via_r3(void *, void *, u32, u32);
void setAnimationFrame(u32, void *, u32, u32);

/* Switch the script to handler table D_0866D57C: clear the state object's
 * fields, run the current step's handler with its repeat count bumped, then
 * restore the step index. */
void sub_08017B5C(void *obj)
{
    u8 *data = (u8 *)obj;
    u8 *state = *(u8 **)(data + 0x3C);
    s16 step;

    *(u32 *)(state + 0x14) = 0;
    *(u32 *)(state + 0x10) = 0;
    *(u32 *)(state + 0x68) = 0;
    *(u32 *)(data + 0x14) = (u32)D_0866D57C;
    *(u16 *)(data + 0x22) = *(u16 *)(data + 0x22) + 1;

    step = *(s16 *)(data + 0x22);
    *(u8 *)(data + step * 2 + 0x19) = *(u8 *)(data + step * 2 + 0x19) + 1;

    step = *(s16 *)(data + 0x22);
    {
        s32 stepOff = step * 2;
        u8 *params = data + 0x18;
        _call_via_r1(obj, *(void **)((u8 *)*(void **)(data + 0x14) + *(u8 *)(params + stepOff) * 4));
    }

    *(u16 *)(data + 0x22) = *(u16 *)(data + 0x22) - 1;
}
