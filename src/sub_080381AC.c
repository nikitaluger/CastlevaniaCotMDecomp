void sub_08013C5C(void *, void *);
s32 sub_080141AC(void *, void *);
s32 sub_08013558(void *, void *, void *);
void sub_08013978(void *, void *);
void sub_08013AC4(void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08013C8C(void *, void *);
void sub_080142C0(void *, void *);
void sub_08014314(void *, void *);
s32 sub_080C31E0(s32, s32);
void sub_080C31E4(void *, void *, u32);

/* Extension hanging off the enemy component at +0x48 (target at +0x54). */
struct AIComponentExt { u8 unk0[0xC]; void *target; };

/* Runs one tick of a scripted AI behaviour: refreshes contact with the enemy's
 * target, then either runs an effect routine or dispatches the next behaviour
 * through the function table the entity holds at +0x14. */
void sub_080381AC(u8 *self) {
    u8 *parent;        /* entity +0x38 */
    u8 *enemy;         /* entity +0x3C */
    u8 *enemyExt;      /* enemy +0x48 */
    s32 behaviorFunc;

    parent = *(u8 **)(self + 0x38);
    enemy = *(u8 **)(self + 0x3C);
    enemyExt = enemy + 0x48;
    sub_08013C5C(self, parent);
    if (sub_080141AC(parent, enemy) == 1) {
        return;
    }
    if (sub_08013558(parent, enemy, *(void **)(enemy + 0x28)) != 0)
        sub_08013978(self, *(void **)(enemy + 0x28));
    sub_080142C0(self, *(void **)(enemy + 0x28));
    if (*(u16 *)enemy & 1) {
        u32 *effectRoutine;
        u8 *script;
        u8 behaviorId;
        u32 behaviorTable;
        s32 scriptOffset;
        sub_08013AC4(self);
        {
            u8 *target = (u8 *)((struct AIComponentExt *)enemyExt)->target;
            u8 zero = 0;
            *(u8 *)(target + 1) = zero;
        }
        {
            u8 *stepBase;
            stepBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(stepBase + 0x19) = 0;
        }
        effectRoutine = (u32 *)0x08671BB0;
        script = self + 0x18;
        sub_080C31E4(script, self + 0x22, *effectRoutine);
        {
            u8 *stepBase;
            stepBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
        }
        scriptOffset = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        script += scriptOffset;
        behaviorId = *script;
        behaviorTable = *(u32 *)(self + 0x14);
        behaviorFunc = *(s32 *)((u32)(behaviorId * 4) + behaviorTable);
        sub_080C31E0((s32)self, behaviorFunc);
    } else {
        if (updateObjectDisplayState(parent, enemy) == 0) {
            u8 *stepBase;
            u8 *script;
            u8 behaviorId;
            u32 behaviorTable;
            s32 scriptOffset;
            *(u32 *)(self + 0x14) = (u32)0x0866DE8C;
            *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
            stepBase = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            *(u8 *)(stepBase + 0x19) = *(u8 *)(stepBase + 0x19) + 1;
            scriptOffset = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
            script = self;
            script += 0x18;
            script += scriptOffset;
            behaviorId = *script;
            behaviorTable = *(u32 *)(self + 0x14);
            sub_080C31E0((s32)self, *(s32 *)((u32)(behaviorId * 4) + behaviorTable));
            *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
        } else {
            sub_08014314(enemy, ((struct AIComponentExt *)enemyExt)->target);
        }
        sub_08013C8C(self, parent);
    }
}
