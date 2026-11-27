void sub_08005E80(s32);
void sub_0805FA88(s32, s32);
void sub_080C31E4(void *, void *, void *);
extern void *gScriptStepCallbackTable;
extern u8 gMainWorkspace[];
struct S { u8 pad[0x0C]; s16 started; s16 doneFlag; s16 cooldown; };

/*
 * Script step: when the work cooldown expires, spawn an effect and reset it;
 * when the work's done flag is clear, play a sound, mark it started and restart
 * the script step.
 */
void sub_080927EC(void *arg0)
{
    u8 *self = arg0;
    struct S *work = *(struct S **)(self + 0x3C);

    if (work->cooldown <= 0) {
        u8 *state = gMainWorkspace;
        sub_0805FA88(*(s32 *)(state + 0x1868), 0x1FC);
        work->cooldown = 0x2D0;
    }

    if (work->doneFlag == 0) {
        s16 idx;
        sub_08005E80(0x1B6);
        work->started = 1;
        idx = *(s16 *)(self + 0x22);
        self[idx * 2 + 0x19] = 0;
        {
            void **lit = &gScriptStepCallbackTable;
            sub_080C31E4(self + 0x18, self + 0x22, *lit);
        }
    }
}
