extern s32 gMenuState;
extern u8 D_0083FC00;
extern s32 sub_08005F1C(u16 id);
extern void stopAllSounds(void);
extern void sub_080C08D0(s32 mode);
extern void sub_080C31E4(void *state, void *step, s32 data);
extern void sub_080C31E0(void *actor, s32 handler);

void sub_08009A34(u8 *self) {
    if (gMenuState == 2) {
        u8 *stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22) * 2) + (u32)self);
        if (stepPtr[0x19] == 0x68) {
            stopAllSounds();
            sub_080C08D0((u32)&D_0083FC00 & 0xF0000);
            *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = 0;
            {
                s32 *scriptTable = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
            }
        }
        return;
    }
    {
        s32 status = sub_08005F1C(0x151);
        if (status == 0) {
            *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) = status;
            {
                s32 *scriptTable = (s32 *)0x08671BB0;
                u8 *actionList = self + 0x18;
                sub_080C31E4(actionList, self + 0x22, *scriptTable);
                *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) =
                    *(u8 *)(self + (*(s16 *)(self + 0x22)) * 2 + 0x19) + 1;
                {
                    s32 actionOffset = (*(s16 *)(self + 0x22)) * 2;
                    u8 actionId = *(actionList + actionOffset);
                    u8 **stepHandlers = *(u8 **)(self + 0x14);
                    sub_080C31E0(self, (s32)stepHandlers[actionId]);
                }
            }
        }
    }
}
