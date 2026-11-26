extern void *D_08671BDC;
extern u8 gCameraState[];
struct GameState { u8 _0[0x18A8]; u8 roomIndex18A8; u8 _1[0x13]; u16 field18BC; };
extern struct GameState gMainWorkspace;

struct SpawnFlags { u8 _0[1]; u8 f; };
struct HitFlags { u16 f; };

extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08016238(void *);
extern s32 sub_08013B5C(s32, void *);
extern void sub_08005E80(s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void sub_080113A8(s32, void *);
extern void sub_0801165C(void *, s32);
extern void sub_08048030(s32, void *);

/* Updates a scripted attack/hit entity: flags spawn state, checks whether the
 * attack is off or spent, handles hit/lifetime results, advances the script while
 * live, then re-anchors the attacker to the current room's coordinate table. */
void sub_08047CA4(u8 *script) {
    s32 attacker = *(s32 *)(script + 0x38);
    u8 *attack = *(u8 **)(script + 0x3C);
    u8 *attackData34 = attack + 0x34;
    u8 *state48 = attack + 0x48;
    u32 coordTable, coordOffsetX, coordOffsetY;

    {
        u8 *spawnFlags = *(u8 **)(attack + 0x28);
        ((struct SpawnFlags *)spawnFlags)->f |= 5;
    }

    if (sub_0805F9B4(*(s32 *)(attack + 8), *(s32 *)(attack + 0xC)) == 1) {
        sub_080C31E0(script, *(void **)(script + 0x24));
        goto done;
    }

    {
        s32 timer = *(s16 *)(state48 + 0xA);
        u8 *hitFlags = *(u8 **)(attack + 0x28);
        if (timer == 0 || (*(u16 *)(hitFlags + 0x14) & 1) != 0) {
            if (sub_08016238(hitFlags) != 0) {
                ((struct HitFlags *)attack)->f |= 1;
            }
        }
    }

    if (*(u16 *)attack & 1) {
        u8 *scriptState0 = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
        if (*(u8 *)(scriptState0 + 0x1A) != 2) {
            sub_08005E80(0x189);
            {
                u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
                *(u8 *)(scriptState + 0x1B) = 0;
                { void **fnaddr = &D_08671BDC;
                  sub_080C31E8(script + 0x18, script + 0x22, 2, *fnaddr); }
            }
        }
    }

    if (sub_08013B5C(attacker, attack) != 0) goto db0;

    *(u32 *)(script + 0x14) = 0x0866E324;
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) + 1;
    {
        u8 *scriptState = (u8 *)((u32)(*(s16 *)(script + 0x22)) * 2 + (u32)script);
        scriptState[0x19] = (u8)(scriptState[0x19] + 1);
    }
    {
        s32 scriptIndex = (*(s16 *)(script + 0x22)) * 2;
        u8 *scriptPc = script + 0x18;
        u8 opcode = *(scriptPc + scriptIndex);
        void **cmdTable = *(void **)(script + 0x14);
        void *handler = cmdTable[opcode];
        sub_080C31E0(script, handler);
    }
    *(u16 *)(script + 0x22) = *(u16 *)(script + 0x22) - 1;
    if ((*(u16 *)(script + 2) & 0x8000) != 0) goto done;
    sub_080113A8(attacker, attackData34);
    sub_0801165C(attack, 0x16C1);
    goto dc8;

db0:
    if (*(s16 *)(state48 + 0xA) == 1) {
        *(s16 *)(state48 + 0xA) = 0;
        --gMainWorkspace.field18BC;
    }

dc8:
    sub_08048030(attacker, attack);
    {
        u8 *hitFlags = *(u8 **)(attack + 0x28);
        *(u16 *)(hitFlags + 0x14) = 0;
    }
    coordTable = (u32)gCameraState;
    coordOffsetX = 0x1278;
    *(s32 *)((u8 *)attacker + 0x14) = *(s32 *)(attack + 8) - (s32)(((*(u32 *)(coordTable + coordOffsetX + ((gMainWorkspace.roomIndex18A8 + 1) << 6))) + 0x8000) & 0xFFFF0000);
    coordOffsetY = 0x127C;
    *(s32 *)((u8 *)attacker + 0x18) = *(s32 *)(attack + 0xC) - (s32)(((*(u32 *)(coordTable + coordOffsetY + ((gMainWorkspace.roomIndex18A8 + 1) << 6))) + 0xFFFF8000) & 0xFFFF0000);

done:
    ;
}
