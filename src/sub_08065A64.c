s32 sub_0806C4B4(void *, void *);
void sub_0806C5EC(void *, void *, void *, void *);
void sub_0806AB04(void *, void *, void *, void *);
void sub_08003A6C(void *, s32, s32);
void sub_08005E80(s32);
void sub_0806A7AC(void *, void *, s32);
void sub_0806A884(void *, void *);
void sub_08003740(void *, void *);
void sub_0806C6B0(void *, void *, void *, void *);
void sub_08084CBC(void *, void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E8(void *, void *, s32, s32);
extern s32 gMainObjTimerCallback;
extern s32 D_08671BD8;

/* Advance a spawned effect's motion from its profile table at 0x080E03A0 and,
   when its action flag is set, fire the kind-specific hit/sound/animation cues. */
void sub_08065A64(void *arg0) {
    void *spawn = *(void **)((u8 *)arg0 + 0x6C);
    void *effectBase = (void *)((u32)spawn + 4);
    void *effect;
    void *owner = *(void **)((u8 *)arg0 + 0x38);
    s32 zeroResult;
    u8 *motionTable;
    s32 tableOffset;
    s32 maxValue;
    s32 kind;
    u8 *stateByte;
    s32 *cmdTable;

    effect = effectBase;
    zeroResult = sub_0806C4B4(effect, effect);
    if (zeroResult != 0) return;
    sub_0806C5EC(arg0, owner, effect, effect);
    motionTable = (u8 *)0x080E03A0;
    tableOffset = *(s32 *)((u8 *)effect + 0x44) * 0x58;
    *(s32 *)((u8 *)effect + 0x0C) += *(s32 *)(tableOffset + motionTable);
    motionTable += 4;
    maxValue = *(s32 *)(tableOffset + motionTable);
    if (*(s32 *)((u8 *)effect + 0x0C) > maxValue)
        *(s32 *)((u8 *)effect + 0x0C) = maxValue;
    sub_0806AB04(arg0, owner, effect, effect);
    if (*(s32 *)((u8 *)effect + 0x40) == 1) {
        *(s32 *)((u8 *)effect + 8) = zeroResult;
        *(s32 *)((u8 *)effect + 0x0C) = zeroResult;
        kind = *(s32 *)((u8 *)spawn + 0xA0);
        switch (kind) {
        case 1:
            sub_0806A7AC(owner, effect, 0x26);
            sub_08005E80(0x7A);
            sub_08084CBC(arg0, effect);
            stateByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            stateByte[0x17] = zeroResult;
            cmdTable = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0x1A, *cmdTable);
            break;
        case 3:
            sub_0806A7AC(owner, effect, 0x25);
            sub_08005E80(0x79);
            sub_08084CBC(arg0, effect);
            *(s32 *)((u8 *)effect + 0x10) = zeroResult;
            stateByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            stateByte[0x17] = zeroResult;
            cmdTable = (s32 *)0x08671BD8;
            sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0x1B, *cmdTable);
            break;
        default:
            sub_08003A6C((u8 *)spawn + 0x2C, 0, 0x0846EC44);
            stateByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            stateByte[0x19] = zeroResult;
            cmdTable = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *cmdTable);
            break;
        }
    }
    sub_0806A884(owner, effect);
    sub_08003740((u8 *)effectBase + 0x28, owner);
    sub_0806C6B0(arg0, owner, effectBase, effect);
}
