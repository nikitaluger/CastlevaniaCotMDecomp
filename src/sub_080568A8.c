extern s32 isOutsideCameraBounds(s32, s32);
extern s32 sub_08056C20(void *, void *, void *, void *, void *, s32, s32);
extern void sub_08056D7C(void *, void *, void *);
extern void sub_080C31E4(void *, void *, u32);

/* Path table: each record starts with a word holding a pointer to path data. */
struct PathEntry { s32 value; u8 _rest[0x20]; };
struct PathTable { u8 _pad[0x14]; struct PathEntry entries[1]; };
extern struct PathTable D_080CFBF8;

/* Drive one scripted effect. If the owner's fixed-point point at +0x4C/+0x5C
 * lies inside the camera bounds, advance the script at target+0x48 with the
 * path selected by the script's +9 byte; when the script finishes, clean up,
 * clear the slot timer and dispatch the gScriptStepCallbackTable callback. */
void sub_080568A8(void *owner) {
    void *handle;
    void *target;
    void *status;
    void *script;
    u32 *callbackTable;

    handle = *(void **)((u8 *)owner + 0x38);
    target = *(void **)((u8 *)owner + 0x3C);
    status = (u8 *)target + 0x34;
    script = (u8 *)target + 0x48;
    if (isOutsideCameraBounds(*(s32 *)((u8 *)owner + 0x4C), *(s32 *)((u8 *)owner + 0x5C)) != 1) {
        if (sub_08056C20(owner, target, script, handle, status,
                         D_080CFBF8.entries[*(u8 *)((u8 *)script + 9)].value, 1) != 0) {
            sub_08056D7C(owner, target, script);
            *(u8 *)((u8 *)owner + ((s32)*(s16 *)((u8 *)owner + 0x22) * 2) + 0x19) = 0;
            callbackTable = (u32 *)0x08671BB0;
            sub_080C31E4((u8 *)owner + 0x18, (u8 *)owner + 0x22, *callbackTable);
        }
    }
}
