extern void sub_08005E80(u16);
extern void sub_08010214(void);
extern void sub_080C31E4(void *, void *, void *);

struct S_02021E90 {
    u8 pad[0x146C];
    u16 f146C;
    u16 f146E;
    u16 f1470;
};

extern struct S_02021E90 gCameraState;
extern u16 gCrossfadeGfxState[];
extern void *gScriptStepCallbackTable;

/* Forces the entity's mode byte (+0x60) from the global state flags, plays a
 * sound when it changes, and on a trigger flag runs the spawn/action sequence. */
void sub_080098A8(void *entity)
{
    s8 *modePos;
    s32 oldMode;
    u16 stateFlags;
    s8 *modeRecheck;
    u32 mask20;
    u32 mask2;

    modePos = (s8 *)entity + 0x60;
    oldMode = *modePos;
    stateFlags = gCameraState.f1470;
    if ((stateFlags & 0x30) != 0x30) {
        mask20 = 0x20;
        mask20 &= stateFlags;
        if (mask20 == 0) {
        } else {
            *modePos = 0;
        }
        if (gCameraState.f1470 & 0x10) {
            *modePos = 1;
        }
    }
    modeRecheck = (s8 *)entity + 0x60;
    if (oldMode != *modeRecheck) {
        sub_08005E80(0x153);
    }
    {
        u16 triggerFlags = gCameraState.f146C;
        if (triggerFlags & 3) {
            mask2 = 2;
            mask2 &= triggerFlags;
            if (mask2 == 0) {
                if (*modeRecheck == 0) {
                    sub_08010214();
                    sub_08005E80(0x15A);
                } else {
                    sub_08005E80(0x159);
                }
            } else {
                sub_08005E80(0x159);
            }
            gCrossfadeGfxState[2] = 0xFF;
            *((s8 *)entity + 0x5C) = 0;
            {
                s16 stepIndex = *(s16 *)((u8 *)entity + 0x22);
                *((s8 *)entity + stepIndex * 2 + 0x19) = 0;
            }
            {
                void **callback = &gScriptStepCallbackTable;
                sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
            }
        }
    }
}
