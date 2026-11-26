/* Copy the shared sprite scale into the actor's scale field, wait for its
 * countdown, then abort the script if the room/mode changed. */
extern s32 sub_08003740(s32, u16 *);
extern s32 sub_0806D518(void *, u16 *, s32);
extern s32 sub_0806D588(u16 *, s32);
extern void sub_080C31E0(void *, s32);
struct GameState {
    u8 _0[0x10];
    s32 field10;
    u8 _14[0x14ED - 0x14];
    u8 field14ED;
    u8 _14EE[0x173A - 0x14EE];
    u8 field173A;
    u8 _173B[0x18C2 - 0x173B];
    u16 scale;
};
extern struct GameState gMainWorkspace;

void sub_08079C68(void *arg0) {
    u8 *self = (u8 *)arg0;
    s32 actor = *(s32 *)(self + 0x6C);
    u8 *mover = (u8 *)(actor + 4);
    u16 *scalePtr = *(u16 **)(self + 0x38);
    if (sub_0806D518(arg0, scalePtr, (s32)mover) == 0) {
        *scalePtr = gMainWorkspace.scale;
        if (sub_08003740(actor + 0x20, scalePtr) == 0) {
            sub_080C31E0(arg0, *(s32 *)(self + 0x24));
        } else {
            sub_0806D588(scalePtr, (s32)mover);
            if ((gMainWorkspace.field173A == 0x1C) || ((gMainWorkspace.field14ED == 0) && (gMainWorkspace.field10 != 0))) {
                sub_080C31E0(arg0, *(s32 *)(self + 0x24));
            }
        }
    }
}
