void sub_08003A6C(s32, s32, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0_14AC { u8 _0x000[0x14AC]; s32 mode; };
extern struct S_02025FF0_14AC gMainWorkspace;

/* Script step for the "mode 4" cutscene: load script 0x0862ED44 into the
 * actor's script slot and advance to its next command. */
void sub_0808C514(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *actor = *(void **)(self + 0x6C);
    if (gMainWorkspace.mode == 4) {
        sub_08003A6C((s32)((u8 *)actor + 0x20), 0, (s32)0x0862ED44);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        {
            s32 *handlers = (s32 *)0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *handlers);
        }
    }
}
