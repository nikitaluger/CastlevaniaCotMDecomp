s32 sub_0806D450(void *, void *, void *);
void stepDelayTimer(void *, s32);
void sub_0806D588(void *, void *);
void sub_080C31E0(void *, s32);
void sub_080C31E4(void *, void *, s32);

extern s32 gScriptStepCallbackTable;

struct S_02025FF0 {
    u8 pad0[0x10];
    s32 f10;
    u8 pad14[0x14ED - 0x14];
    u8 f14ED;
    u8 pad14EE[0x173A - 0x14EE];
    u8 f173A;
    u8 pad173B[0x1754 - 0x173B];
    s32 f1754;
    u8 pad1758[0x18C2 - 0x1758];
    u16 f18C2;
};
extern struct S_02025FF0 gMainWorkspace;

/* Per-frame update for this entity type: when a special camera/scroll mode owns
 * the position, hand off to the entity callback and return; otherwise apply the
 * scroll delta to the view, run a countdown that fires an effect when it expires,
 * post an idle effect, snap the view back to the grid, and finally call the
 * callback again under certain area states. */
void sub_0807A7DC(u8 *self)
{
    u8 *pos = *(u8 **)(self + 0x6C) + 4;
    u8 *view = *(u8 **)(self + 0x38);
    u8 *vec = (u8 *)pos;

    if (sub_0806D450(self, view, vec) > 0) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }

    *(s32 *)(view + 0x18) += *(s32 *)(vec + 0x0C);
    *(u16 *)view = gMainWorkspace.f18C2;
    {
        s32 countdown = *(s32 *)(vec + 0x10) - 1;
        *(s32 *)(vec + 0x10) = countdown;
        if (countdown == 0) {
            *(s32 *)(vec + 0x10) = 0x40;
            countdown = gMainWorkspace.f1754;
            if (countdown <= 4) {
                gMainWorkspace.f1754 = 5;
            }
            *(u8 *)(self + (s32)*(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                s32 *effectData = &gScriptStepCallbackTable;
                sub_080C31E4(self + 0x18, self + 0x22, *effectData);
            }
        }
    }
    stepDelayTimer((u8 *)pos + 0x1C, (s32)view);
    {
        s32 savedX = *(s32 *)(view + 0x18);
        sub_0806D588(view, vec);
        *(s32 *)(view + 0x18) = savedX;
    }
    if (gMainWorkspace.f173A == 0x1C || (gMainWorkspace.f14ED == 0 && gMainWorkspace.f10 != 0)) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
    }
}
