s32 sub_0801459C(void *, s32);
void sub_080148D8(void *, s32);
void sub_080AC908(void *, void *, void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 pad[0x3C]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;
extern s32 gMainObjTimerCallback;

/* Aim-step script callback: arm the aim controller and refresh the companion's
 * direction, then, when a global flag is set and the entity is near the player
 * (or its animation flag is set), reset the script step and dispatch the
 * script handler. */
void sub_080AB268(void *entity) {
    u8 *self = (u8 *)entity;
    void *companion = *(void **)(self + 0x38);
    u8 *scriptState = *(u8 **)(self + 0x3C);
    u8 *anim = scriptState + 0x34;
    u8 *aim = scriptState + 0x48;
    s32 *handlerTable;

    aim[0x11] = 1;
    sub_080AC908(companion, anim, scriptState, aim);
    sub_080148D8(companion, *(s32 *)(scriptState + 0x08));

    if (gMainWorkspace.w != 0) {
        if (sub_0801459C(scriptState, 0x700000) != 0 || (*(u16 *)scriptState & 2)) {
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            handlerTable = &gMainObjTimerCallback;
            sub_080C31E4(self + 0x18, self + 0x22, *handlerTable);
        }
    }
}
