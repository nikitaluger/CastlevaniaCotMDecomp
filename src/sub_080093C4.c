s32 sub_08005F1C(s32);
void sub_080C0574(void);
void sub_080C08D0(s32);
void sub_08000F50(void);
void sub_080C31E4(void *, void *, s32);
extern u8 D_083FC00[];

struct GameStateBlock { u8 b[0x20]; };
extern struct GameStateBlock gCameraState[];

/* Teardown step of an ending sequence: once the step's flag byte has counted
 * past 12 frames, and only if no effect slot of type 2 is still active, it
 * stops all music tracks (sub_080C0574), resets the sound engine's reverb
 * (mode 3 = 0x30000), clears the global ending flag (bit 0x20000000 of
 * gCameraState) and the state byte at offset 0x1360, clears the step flag and
 * advances the script via sub_080C31E4. */
void sub_080093C4(void *actor) {
    u8 *self = (u8 *)actor;
    s32 active;

    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) > 0xC) {
        active = sub_08005F1C(2);
        if (active == 0) {
            sub_080C0574();
            sub_080C08D0((u32)D_083FC00 & 0xF0000);
            sub_08000F50();
            gCameraState[0x9B].b[0] = active;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = active;
            {
                s32 *scriptTable;
                scriptTable = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
            }
        }
    }
}
