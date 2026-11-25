void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);

struct ViewFlags { u8 pad[0x2A]; u8 flags; };

/* Script-step update: installs this object's handler table, runs the handler
 * for the current step slot (index temporarily advanced), restores the view
 * position and clears the view's in-view flag when the next slot ends it. */
void sub_08045F5C(void *arg0) {
    void *view = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, view);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866E2C8;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepPtr[0x19] = (u8)(stepPtr[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *scriptSlots = (u8 *)arg0 + 0x18;
            u8 handlerId = *(scriptSlots + stepOffset);
            void **handlers = *(void **)((u8 *)arg0 + 0x14);
            void *handler = handlers[handlerId];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, view);
    {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        if (stepPtr[0x1A] == 1) {
            ((struct ViewFlags *)view)->flags &= 0xBF;
        }
    }
}
