/* Script step that configures an actor with fixed script/data pointers, sets a
 * flip flag from the global view position and a couple of movement constants,
 * then fires the step's timed effect and dispatches the next command. */
extern void startEffectTimer(s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, void *);
extern s32 gMainObjTimerCallbacks[];
extern u8 gMainWorkspace[];

void sub_0808A584(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *ctrl = *(u8 **)(self + 0x6C);
    u8 *pos = ctrl + 4;
    u8 *actor = *(u8 **)(self + 0x38);

    *(s32 *)(actor + 0x24) = 0x08502C40;
    startEffectTimer((s32)(ctrl + 0x20), 0, (s32)0x08502DAC);

    {
        u8 *globals = gMainWorkspace;
        u32 *globalViewX = (u32 *)(globals + 0x1728);
        if (*(s32 *)globalViewX <= 0x00FFFFFF) {
            u32 flipFlags = (u16)(*(u16 *)(actor + 2) | 0x10U);
            *(u16 *)(actor + 2) = flipFlags;
        }
        *(s32 *)(ctrl + 4) = 0x01000000;
        *(s32 *)(pos + 4) = 0x01E70000;
        *(u32 *)(globals + 0x40) = 3;
    }

    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        s32 *effectData = gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *effectData);
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
    {
        u8 *cmdArray = self + 0x18;
        s16 cmdIndex = *(s16 *)(self + 0x22);
        cmdArray += cmdIndex * 2;
        sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *cmdArray * 4));
    }
}
