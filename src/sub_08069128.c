extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, s32, void *, void *);
extern void sub_0806BA20(s32, void *, void *);
extern void sub_080694D8(s32, void *, void *);
extern void sub_0806AB04(void *, s32, void *, void *);
extern void sub_0806A884(s32, void *);
extern s32 sub_08003740(void *, s32);
extern void sub_08003A6C(void *, s32, s32);
extern void sub_0806932C(void *, void *);
extern u16 sub_0806BCD8(void *, s32, void *, void *);
extern void sub_0806C6B0(void *, s32, void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Mutable motion state of the effect at spawn+4. */
struct EffectState {
    u8 pad00[8];
    s32 velX;        /* 0x08 */
    s32 velY;        /* 0x0C */
    u8 pad10[0x40 - 0x10];
    s32 action;      /* 0x40 */
    s32 tableIndex;  /* 0x44 */
    u8 pad48[4];
    s32 f4C;         /* 0x4C */
    s32 f50;         /* 0x50 */
};
/* Spawn object: holds the effect at +4 and the follow-up command at +0xC8. */
struct SpawnObj {
    u8 pad00[0xC8];
    s32 command;     /* 0xC8 */
};

/* Advance a spawned effect's motion from the 0x080E03A0 profile table, then
   issue its hit, script and follow-up command cues. */
void sub_08069128(u8 *arg0) {
    u8 *hitbox;
    u8 *spawn = *(u8 **)(arg0 + 0x6C);
    u8 *effect = spawn + 4;
    s32 owner = *(s32 *)(arg0 + 0x38);
    s32 zeroResult = sub_0806C4B4(effect, effect);
    s32 motionTable, tableOffset;

    if (zeroResult != 0) return;

    sub_0806C5EC(arg0, owner, effect, effect);
    sub_0806BA20(owner, effect, effect);
    motionTable = 0x080E03A0;
    tableOffset = ((struct EffectState *)effect)->tableIndex * 0x58;
    ((struct EffectState *)effect)->velY = ((struct EffectState *)effect)->velY + *(s32 *)(motionTable + tableOffset);
    motionTable += 4;
    {
        s32 maxValue = *(s32 *)(motionTable + tableOffset);
        if (((struct EffectState *)effect)->velY > maxValue) ((struct EffectState *)effect)->velY = maxValue;
    }
    sub_080694D8(owner, effect, effect);
    sub_0806AB04(arg0, owner, effect, effect);
    if (((struct EffectState *)effect)->action == 1) {
        u8 *stateByte;
        s32 *cmdTable;
        ((struct EffectState *)effect)->f4C = zeroResult;
        ((struct EffectState *)effect)->f50 = zeroResult;
        ((struct EffectState *)effect)->velX = zeroResult;
        stateByte = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stateByte + 0x19) = zeroResult;
        cmdTable = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x2B, *cmdTable);
    }
    sub_0806A884(owner, effect);
    hitbox = spawn + 0x2C;
    if (sub_08003740(hitbox, owner) == 0) {
        u8 *stateByte;
        s32 *cmdTable;
        sub_08003A6C(hitbox, 0, (void *)0x084FCA84);
        stateByte = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stateByte + 0x19) = zeroResult;
        cmdTable = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 0x28, *cmdTable);
    }
    sub_0806932C(arg0, effect);
    *(s32 *)((u8 *)spawn + 0xC8) = (u16)sub_0806BCD8(arg0, owner, effect, effect);
    if (((struct SpawnObj *)spawn)->command != 0) {
        u8 *stateByte;
        s32 *cmdTable;
        sub_08003740(hitbox, owner);
        stateByte = (u8 *)((u32)(*(s16 *)(arg0 + 0x22)) * 2 + (u32)arg0);
        *(u8 *)(stateByte + 0x19) = zeroResult;
        cmdTable = (s32 *)0x08671BD0;
        sub_080C31E8(arg0 + 0x18, arg0 + 0x22, ((struct SpawnObj *)spawn)->command, *cmdTable);
    }
    sub_0806C6B0(arg0, owner, effect, effect);
}
