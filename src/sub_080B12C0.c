extern void setObjectAnimation(s32, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern void startScriptOnce(s32, s32, s32);

/* When the object's current script step reaches 0x1E, run startScriptOnce on its
 * id, clear the step's paired byte and advance the script through table
 * 0x08671BD8 with command 2. */
void sub_080B12C0(void *arg0) {
    u8 *obj = (u8 *)arg0;
    s32 id4C = *(s32 *)(obj + 0x4C);
    if (*(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) == 0x1E) {
        s32 *table;
        startScriptOnce(id4C, 1, 1);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x17) = 0;
        table = (s32 *)0x08671BD8;
        sub_080C31E8(obj + 0x18, obj + 0x22, 2, *table);
    }
}
