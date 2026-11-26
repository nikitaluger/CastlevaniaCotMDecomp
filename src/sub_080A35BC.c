s32 sub_0801459C(void *, s32);
void sub_080A3E8C(s32, void *, void *, void *);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 pad[0x3C]; u16 w; };
extern struct S_02025FF0 gMainWorkspace;

/* Aim step: let the target chooser pick among the possible targets, then,
 * while gameplay is running, advance the script when the player is within
 * 0x900000 units or the aim state has flag bit 1 set. */
void sub_080A35BC(void *entity) {
    u8 *self = (u8 *)entity;
    s32 sprite = *(s32 *)(self + 0x38);
    u16 *aimState = *(u16 **)(self + 0x3C);
    u8 *anim = (u8 *)aimState + 0x34;
    u8 *aim = (u8 *)aimState + 0x48;
    sub_080A3E8C(sprite, anim, aimState, aim);
    if (gMainWorkspace.w != 0) {
        if (sub_0801459C(aimState, 0x900000) != 0 || (*aimState & 2)) {
            *(s32 *)(aim + 0x5C) = 1;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
            {
                s32 *scriptTable = (s32 *)0x08671BB0;
                sub_080C31E4(self + 0x18, self + 0x22, *scriptTable);
            }
        }
    }
}
