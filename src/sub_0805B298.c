extern vu32 gMainWorkspace;
extern vu32 gMainObjTimerCallbacks;

void *spawnBudgetedEffect(s32, s32);
void unlinkAndFreeObject(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);

/* Scripted object header: current command slot index (0x22), the handler run
 * by the command script (0x24), sprite object (0x38) and work/animation state
 * (0x3C). The per-slot frame counter sits at 0x19 + slot * 2. */
struct MainObj {
    u8 pad_0x00[0x22];
    s16 slot;
    u32 updateCb;
    u8 pad_0x28[0x38 - 0x28];
    u32 sprite;
    u32 work;
};

/* Per-object work block: the update handler (0x24), the cleanup-request flag
 * (0x28) and the animation state at work + 0x34 (where the work pointer is
 * already offset by 0x34 when used as an animation). */
struct SubObj {
    u8 pad_0x00[0x24];
    u32 updateCb;
    u32 cleanupFlag;
    u8 pad_0x2C[0x34 - 0x2C];
    u8 anim;
};

/* Spawned result/sprite object with the packed screen position at 0x4C/0x54. */
struct ResultObj {
    u8 pad_0x00[0x4C];
    s16 posX;
    u8 pad_0x4E[0x54 - 0x4E];
    s16 posY;
};

/* Per-frame object update: when the work block requests cleanup, run the
 * object-list cleanup, then dispatch this object's script handler at +0x24. */
void sub_0805B298(struct MainObj *arg0) {
    struct SubObj *sub = (struct SubObj *)arg0->work;
    if (sub->cleanupFlag != 0) {
        unlinkAndFreeObject();
    }
    sub_080C31E0(arg0, sub->updateCb);
}

/* Spawn a result object of type 0x89 and store the packed x/y position of the
 * two 16.16 fixed-point arguments (upper 16 bits) in it. */
void *sub_080191FC(s32 x, s32 y) {
    struct ResultObj *res;
    s32 vx;
    s32 vy;
    void *obj;

    obj = spawnBudgetedEffect(*(vu32 *)((u8 *)&gMainWorkspace + 0x1870), 0x89);
    if (obj == NULL) {
        return NULL;
    }
    vx = x;
    if (vx < 0) {
        vx += 0xFFFF;
    }
    ((struct ResultObj *)obj)->posX = (s16)(vx >> 16);
    vy = y;
    if (vy < 0) {
        vy += 0xFFFF;
    }
    ((struct ResultObj *)obj)->posY = (s16)(vy >> 16);
    return obj;
}

/* Play animation frame 0x34 forward and, if the animation state asks to
 * advance, dispatch this object's script handler at +0x24. */
void MainObj_CallUpdate2(struct MainObj *arg0) {
    u8 *anim = (u8 *)arg0->work + 0x34;
    setAnimationFrame(arg0->sprite, anim, 0x34, 0);
    if ((anim[0] & 2) != 0) {
        sub_080C31E0(arg0, arg0->updateCb);
    }
}

/* Main-object update: play animation frame 0x2B forward, then, once the
 * current command slot's timer exceeds 30, reset it and dispatch the next
 * command through the script pointer table at 0x08671BB0. */
void sub_08019170(struct MainObj *arg0) {
    u8 *step;
    s16 idx;

    setAnimationFrame(arg0->sprite, (u8 *)arg0->work + 0x34, 0x2B, 1);
    idx = arg0->slot;
    step = (u8 *)arg0 + idx * 2;
    if (step[0x19] > 0x1E) {
        step[0x19] = 0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, gMainObjTimerCallbacks);
    }
}
