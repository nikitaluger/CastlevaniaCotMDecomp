extern void *spawnBudgetedEffect(s32, s32);

struct ObjectPool { u8 _p[0x1870]; u32 pool; };
extern struct ObjectPool gMainWorkspace;

struct SpawnedObj {
    u8 _p0[0x4C];
    u16 x;
    u8 _p1[6];
    u16 y;
    u8 _p2[6];
    u16 param;
    u8 _p3[0x6C - 0x5E];
    u32 data;
};

/* Spawn an effect object (0x93) and fill its four parameter fields. */
void *sub_0801DAB4(s32 a0, s32 a1, s32 a2, s32 a3) {
    struct SpawnedObj *obj;
    void *result;
    obj = (struct SpawnedObj *)spawnBudgetedEffect(gMainWorkspace.pool, 0x93);
    if (obj != 0) {
        obj->x = a0;
        obj->y = a1;
        obj->param = a2;
        obj->data = a3;
        result = obj;
    } else {
        result = 0;
    }
    return result;
}
