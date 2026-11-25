extern void sub_08003A6C(void *, s32, void *);
extern void sub_0806D588(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Starts the effect: point the handle at its data, initialise the object's
 * sub-structure and fields, position the handle, then run the setup callback
 * and dispatch this entity's first callback. */
void sub_08089A04(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *obj = *(u8 **)(self + 0x6C);
    u8 *obj4 = obj + 0x04;
    u8 *handle = *(u8 **)(self + 0x38);

    *(u32 *)(handle + 0x24) = 0x08507BA0;
    sub_08003A6C(obj + 0x20, 0, (void *)0x08507DE4);
    *(u32 *)(obj + 0x04) = 0x00A00000;
    *(u32 *)(obj4 + 0x04) = 0x00800000;
    sub_0806D588(handle);
    *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        const u32 *cbTable = (const u32 *)0x08671BB0;
        u8 *frameEntry = self + 0x18;
        sub_080C31E4(frameEntry, self + 0x22, *cbTable);
        *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        frameEntry = frameEntry + (s32)*(s16 *)(self + 0x22) * 2;
        sub_080C31E0(arg0, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)frameEntry * 4));
    }
}
