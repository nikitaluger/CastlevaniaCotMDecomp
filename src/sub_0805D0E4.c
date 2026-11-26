extern s32 sub_08015850(s32, s32, s32, s32, s32, s32);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08016238(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_080113A8(void *, void *);
extern s32 sub_08011898(void *, s32);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];
extern u8 D_0866E968[];
extern s32 D_08671BDC;

struct SpawnFlags { u8 a; u8 flag; };
struct ActorFlags { u8 flag; };
struct HitFlags { u16 flag; };

/* Updates a scripted attack entity: checks its hit box and timer, manages hit and
 * spawn flags, advances the script while live, then re-anchors the attacker to the
 * current room's coordinate table. */
void sub_0805D0E4(u8 *script) {
    u8 *attacker;
    u8 *attack;
    u8 *state48;
    u8 *attackData34;
    u8 *scriptPc;
    u8 *coordTable;
    u8 *coordXTable;
    u8 *roomIndexPtr;
    u32 roomOffset;
    u32 coordX;
    u32 coordY;
    u32 opcode;
    s32 scriptIndex;
    u8 *scriptState1;
    u8 *scriptState2;
    s32 hitFlag;
    s32 *cmdTableAddr;

    attacker = *(u8 **)(script + 0x38);
    attack = *(u8 **)(script + 0x3C);
    attackData34 = attack + 0x34;
    state48 = attack + 0x48;
    if (sub_08015850(*(s32 *)(attack + 8), *(s32 *)(attack + 0xC), -8, 8, -8, 8) == 0) {
        sub_080C31E0(script, *(u32 *)(script + 0x24));
        return;
    }
    if (*(s16 *)(state48 + 2) > 0) {
        *(u16 *)(state48 + 2) = (u16)(*(s16 *)(state48 + 2) - 1);
    }
    if (sub_0805F9B4(*(s32 *)(attack + 8), *(s32 *)(attack + 0xC)) == 1) {
        s32 tmp = 0xBF & ((struct ActorFlags *)(attacker + 0x2A))->flag;
        u8 v = 0;
        ((struct ActorFlags *)(attacker + 0x2A))->flag = tmp;
        ((struct SpawnFlags *)(*(u8 **)(attack + 0x28)))->flag = v;
    } else {
        ((struct ActorFlags *)(attacker + 0x2A))->flag = 0x40 | ((struct ActorFlags *)(attacker + 0x2A))->flag;
        if (*(s16 *)(state48 + 2) > 0) {
            ((struct SpawnFlags *)(*(u8 **)(attack + 0x28)))->flag = 0;
        } else {
            ((struct SpawnFlags *)(*(u8 **)(attack + 0x28)))->flag = 4;
            if (sub_08016238(*(u8 **)(attack + 0x28)) != 0) {
                ((struct HitFlags *)attack)->flag |= 1;
            }
        }
    }
    hitFlag = *(u16 *)attack & 1;
    scriptPc = script + 0x18;
    if (hitFlag) {
        ((struct SpawnFlags *)(*(u8 **)(attack + 0x28)))->flag = 0;
        scriptIndex = *(s16 *)(script + 0x22) * 2;
        scriptState1 = (u8 *)((s32)scriptIndex + (s32)script);
        if (*(u8 *)(scriptState1 + 0x1A) != 1) {
            *(u8 *)(scriptState1 + 0x1B) = 0;
            cmdTableAddr = &D_08671BDC;
            sub_080C31E8(scriptPc, script + 0x22, 1, *cmdTableAddr);
        }
    }
    *(u32 *)(script + 0x14) = (u32)D_0866E968;
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) + 1;
    scriptState2 = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
    *(u8 *)(scriptState2 + 0x19) = *(u8 *)(scriptState2 + 0x19) + 1;
    scriptIndex = *(s16 *)(script + 0x22) * 2;
    opcode = *(u8 *)((u32)scriptPc + (u32)scriptIndex);
    sub_080C31E0(script, *(u32 *)(*(u32 *)(script + 0x14) + opcode * 4));
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) - 1;
    if ((*(u16 *)(script + 2) & 0x8000) != 0) return;
    sub_080113A8(attacker, attackData34);
    sub_08011898(attack, *(u32 *)(state48 + 8));
    coordTable = gCameraState;
    roomIndexPtr = gMainWorkspace;
    roomIndexPtr += 0x18A8;
    roomOffset = ((u32)*roomIndexPtr + 1) * 0x40;
    coordXTable = coordTable + 0x1278;
    coordX = *(u32 *)(coordXTable + roomOffset);
    *(u32 *)(attacker + 0x14) = *(u32 *)(attack + 8) - ((coordX + 0x8000) & 0xFFFF0000);
    roomOffset = ((u32)*roomIndexPtr + 1) * 0x40;
    coordTable += 0x127C;
    coordY = *(u32 *)(coordTable + roomOffset);
    *(u32 *)(attacker + 0x18) = *(u32 *)(attack + 0xC) - ((coordY + 0xFFFF8000) & 0xFFFF0000);
}
