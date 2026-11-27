extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern s32 gScriptStepCallbackTable[];
extern void sub_08072270(void);

/* Switch the entity to its next state: remember the current state handler in
 * the object at +0x6C, install sub_08072270 as the handler, then run the
 * script-advance callback and dispatch the current script byte. */
void sub_08072140(void *arg0)
{
    u8 *self = (u8 *)arg0;
    u8 *script;
    s32 *callback;

    *(u32 *)(*(u32 *)(self + 0x6C) + 0x1C) = *(u32 *)(self + 0x24);
    *(u32 *)(self + 0x24) = (u32)sub_08072270;

    *(u8 *)(self + (s16)*(u16 *)(self + 0x22) * 2 + 0x19) = 0;
    callback = gScriptStepCallbackTable;
    script = self + 0x18;
    sub_080C31E4(script, self + 0x22, *callback);

    *(u8 *)(self + (s16)*(u16 *)(self + 0x22) * 2 + 0x19) += 1;
    script += (s16)*(u16 *)(self + 0x22) * 2;
    sub_080C31E0(self, *(void **)(*(u32 *)(self + 0x14) + *(u8 *)script * 4));
}
