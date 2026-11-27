extern void *gMainObjTimerCallbacks;
extern void *gMenuScriptCallback;
struct S_02021E90 { u8 _0[0x146C]; u16 f146C; };
extern struct S_02021E90 gCameraState;
extern void sub_08005E80(s32);
extern void sub_0800B824(s32, s32, s32);
extern s32 sub_0800B8C4(void *, s32);
extern void sub_0800B9A8(s32, s32, void *);
extern s32 sub_080103F0(u8);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Handles a menu-style selection for an entity: updates the highlighted entry,
 * confirms it when available (playing feedback sound/effects and advancing the
 * AI script), or clears the selection state when the owning entity is idle. */
void sub_0800AE0C(u8 *self) {
    u8 *parent;
    s32 parentState;
    s32 selectionChanged;
    s16 scriptIndex;

    parent = *(u8 **)(self + 0x3C);
    parentState = *(parent + 0x638);
    if (parentState != 0) {
        u8 *selected;
        selectionChanged = sub_0800B8C4(self, 1);
        if (selectionChanged == 0) {
            if (gCameraState.f146C & 1) {
                selected = self + 0x50;
                if (sub_080103F0(*selected) != 0) {
                    s8 *selectedSigned;
                    sub_08005E80(0x157);
                    selectedSigned = (s8 *)selected;
                    if (selectedSigned[0] != 0) {
                        self[0x54] = selectionChanged;
                    } else {
                        self[0x54] = 1;
                    }
                    sub_0800B9A8((s8)self[0x54], 2, parent);
                    sub_0800B824(0x81D7, 0x270, 0x600);
                    scriptIndex = *(s16 *)(self + 0x22);
                    *(self + scriptIndex * 2 + 0x19) = 0;
                    {
                        void **fnaddr = &gMainObjTimerCallbacks;
                        sub_080C31E4(self + 0x18, self + 0x22, (s32)*fnaddr);
                    }
                }
            }
        }
    } else if (gCameraState.f146C & 3) {
        sub_08005E80(0x159);
        *(parent + 0x635) = parentState;
        scriptIndex = *(s16 *)(self + 0x22);
        *(self + scriptIndex * 2 + 0x17) = parentState;
        {
            void **fnaddr = &gMenuScriptCallback;
            sub_080C31E8(self + 0x18, self + 0x22, 0x10, (s32)*fnaddr);
        }
    }
}
