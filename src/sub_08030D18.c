/* Run the entity's behavior state machine: spawn a queued effect, tick its
 * cooldowns relative to the player, and choose a facing direction. */
extern s32 scaleByRandom(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern s32 signOf(s32);
extern s32 sub_08014990(void *);
extern void sub_080149A4(void *, void *, void *, s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);

struct Behavior {
    s16 spawnIndex;
    s16 pad2;
    s16 timer;
    s16 cooldown;
    s16 state;
    s16 pada;
    s32 paramC;
};

struct Mover {
    u16 f0;
    u16 flags2;
    u32 pad4;
    s32 x;
    s32 y;
    s32 facing;
};

struct ScriptArg { u8 pad[0x22]; s16 index; };

extern s16 D_080CEB70[];
extern u32 gScriptStepCallbacks[];

void sub_08030D18(void *entity)
{
    void *workObj = *(void **)((u8 *)entity + 0x38);
    struct Mover *mover = *(struct Mover **)((u8 *)entity + 0x3C);
    void *moverTarget = (u8 *)mover + 0x34;
    struct Behavior *behavior = (struct Behavior *)((u8 *)mover + 0x48);

    if (behavior->state == 1) {
        void *paramPtr = (u8 *)mover + 0x4A;
        s16 idx = behavior->spawnIndex;
        s16 *base = D_080CEB70;
        s32 a = base[idx * 2];
        base += 1;
        {
            s32 b = base[idx * 2];
            sub_080149A4(workObj, mover, paramPtr, a, b);
        }
    }

    setAnimationFrame(workObj, moverTarget, 0, 1);

    behavior->cooldown--;
    if ((s16)behavior->cooldown <= 0) {
        if (sub_08014900(mover->x) <= 0x180000 && sub_0801491C(mover->y) <= 0x100000) {
            s32 dirSign = signOf(mover->x);
            if (dirSign == sub_08014990(workObj)) {
                s16 idx2;
                u8 *p;
                u32 *pp;
                behavior->cooldown = 0x3C;
                idx2 = ((struct ScriptArg *)entity)->index;
                p = (u8 *)((s16 *)entity + idx2);
                p[0x19] = 0;
                pp = gScriptStepCallbacks;
                sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, 1, *pp);
                return;
            }
            behavior->timer = 0;
            behavior->state = 1;
        }
        behavior->cooldown = 0;
    }

    if (mover->flags2 & 3) {
        s32 zero;
        u16 tmp;
        tmp = *(u16 *)((u8 *)workObj + 2);
        tmp ^= 0x10;
        zero = 0;
        *(u16 *)((u8 *)workObj + 2) = tmp;
        behavior->timer = scaleByRandom(0x3D) + 0x78;
        behavior->state = zero;
    }

    behavior->timer--;
    if ((s16)behavior->timer <= 0) {
        behavior->timer = scaleByRandom(0x3D) + 0x78;
        if (sub_08014900(mover->x) <= 0x600000 && sub_0801491C(mover->y) <= 0x400000) {
            behavior->state = 1;
        } else {
            behavior->state = 0;
            if (mover->x < behavior->paramC)
                *(u16 *)((u8 *)workObj + 2) |= 0x10;
            else
                *(u16 *)((u8 *)workObj + 2) &= 0xFFEF;
        }
    }

    if (sub_08014990(workObj) > 0)
        mover->facing = 0x6000;
    else
        mover->facing = 0xFFFFA000;
}
