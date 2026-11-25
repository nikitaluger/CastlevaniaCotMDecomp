extern s32 sub_08056C20(void *, void *, void *, s32, void *, void *, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Fixed arc path: base X/velocity X, base Y/velocity Y. */
struct PathData { s32 baseX, velX, baseY, velY; };

/* Drive one scripted effect with the shared path state machine along its fixed
 * arc path; when the effect finishes, clear the script action byte and dispatch
 * the next script command. */
void sub_08056100(void *self) {
    struct PathData path;
    void *sprite = *(void **)((u8 *)self + 0x38);
    u8 *target = *(u8 **)((u8 *)self + 0x3C);
    u8 *status = 0x34 + target;
    u8 *script = target + 0x48;
    s16 index;
    path = *(struct PathData *)0x080CFC88;
    if (sub_08056C20(self, target, script, (s32)sprite, status, &path, 0) != 0) {
        index = *(s16 *)((u8 *)self + 0x22);
        ((u8 *)self)[index * 2 + 0x19] = 0;
        {
            s32 *callbackTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)self + 0x18, (u8 *)self + 0x22, *callbackTable);
        }
    }
}
