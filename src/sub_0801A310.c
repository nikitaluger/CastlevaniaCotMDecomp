extern void *sub_0805FAEC(s32, s32);

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

/* Copy the stat row selected by the mode byte at +0x28 into the work area's
 * four-word stat buffer. */
void sub_08019ED4(void *arg0, void *arg1) {
    u8 *work = *(u8**)((u8*)arg0 + 0x3C);
    u16 *stats = (u16*)0x080CE5E8;
    u16 mode = *(u16*)((u8*)arg1 + 0x28);
    if (mode == 0x2D) {
        stats += 8;
    } else if (mode == 0x2E) {
        stats += 4;
    }
    {
        u16 *dst = *(u16**)(work + 0x28);
        dst[3] = stats[0];
        dst[4] = stats[1];
        dst[5] = stats[2];
        dst[6] = stats[3];
    }
}

/* Spawn an effect object (0x8B) from fixed-point x/y and two raw parameters. */
void *sub_08019E74(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    void *obj;
    s32 x, y;
    obj = sub_0805FAEC(gMainWorkspace.pool, 0x8B);
    if (obj == 0) return 0;
    x = arg0;
    if (x < 0) x += 0xFFFF;
    *(s16 *)((u8 *)obj + 0x4C) = (s16)(x >> 16);
    y = arg1;
    if (y < 0) y += 0xFFFF;
    *(s16 *)((u8 *)obj + 0x54) = (s16)(y >> 16);
    *(u32 *)((u8 *)obj + 0x5C) = arg2;
    *(u32 *)((u8 *)obj + 0x6C) = arg3;
    return obj;
}

/* Spawn an effect object (0x8C) and fill its four parameter fields. */
void *sub_0801A310(s32 a0, s32 a1, s32 a2, s32 a3) {
    struct SpawnedObj *obj;
    void *result;
    obj = (struct SpawnedObj *)sub_0805FAEC(gMainWorkspace.pool, 0x8C);
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
