/* identical to sub_080191DC (matched), with its names changed by decompdecomp */
extern vu32 gMainWorkspace;
extern vu32 gMainObjTimerCallbacks;

void *spawnBudgetedEffect(s32, s32);
void unlinkAndFreeObject(void);
void sub_080C31E0(void *, u32);
void sub_080C31E4(void *, void *, u32);
void setAnimationFrame(u32, void *, u32, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 slot;                   /* +0x22: current command slot */
    u32 handler;                /* +0x24: saved script handler */
    u8 pad_0x28[0x38 - 0x28];
    u32 sprite;                 /* +0x38: sprite handle */
    u32 subObj;                 /* +0x3C: state sub-object pointer */
};

struct SubObj {
    u8 pad_0x00[0x24];
    u32 handler;                /* +0x24: script handler passed to sub_080C31E0 */
    u32 child;                  /* +0x28: linked child object released when nonzero */
    u8 pad_0x2C[0x34 - 0x2C];
    u8 stateFlags;              /* +0x34: animation/state flags */
};

struct ResultObj {
    u8 pad_0x00[0x4C];
    s16 x;                      /* +0x4C: fixed-point X coordinate (high word) */
    u8 pad_0x4E[0x54 - 0x4E];
    s16 y;                      /* +0x54: fixed-point Y coordinate (high word) */
};

/* Release the sub-object's linked child (if any), then dispatch its saved
 * script handler on this entity. */
void sub_080B05CC(struct MainObj *obj) {
    struct SubObj *sub = (struct SubObj *)obj->subObj;
    if (sub->child != 0) {
        unlinkAndFreeObject();
    }
    sub_080C31E0(obj, sub->handler);
}

/* Spawn a result object from the 0x89 pool and store the high words of the two
 * fixed-point coordinates into it. */
void *sub_080191FC(s32 x, s32 y) {
    struct ResultObj *result;
    s32 fixedX;
    s32 fixedY;
    void *obj;

    obj = spawnBudgetedEffect(*(vu32 *)((u8 *)&gMainWorkspace + 0x1870), 0x89);
    if (obj == NULL) {
        return NULL;
    }
    fixedX = x;
    if (fixedX < 0) {
        fixedX += 0xFFFF;
    }
    ((struct ResultObj *)obj)->x = (s16)(fixedX >> 16);
    fixedY = y;
    if (fixedY < 0) {
        fixedY += 0xFFFF;
    }
    ((struct ResultObj *)obj)->y = (s16)(fixedY >> 16);
    return obj;
}

/* Run the state updater, then re-dispatch the object's handler if a status bit
 * is set. */
void MainObj_CallUpdate2(struct MainObj *obj) {
    u8 *state = (u8 *)obj->subObj + 0x34;
    setAnimationFrame(obj->sprite, state, 0x34, 0);
    if ((state[0] & 2) != 0) {
        sub_080C31E0(obj, obj->handler);
    }
}

/* Run the state updater in its alternate mode, then wrap the script slot back
 * to zero once it passes its limit. */
void sub_08019170(struct MainObj *obj) {
    u8 *unused;
    u8 *slotPtr;
    s16 idx;

    setAnimationFrame(obj->sprite, (u8 *)obj->subObj + 0x34, 0x2B, 1);
    idx = obj->slot;
    slotPtr = (u8 *)obj + idx * 2;
    if (slotPtr[0x19] > 0x1E) {
        slotPtr[0x19] = 0;
        sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, gMainObjTimerCallbacks);
    }
}
