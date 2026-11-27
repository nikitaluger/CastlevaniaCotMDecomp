s32 scaleByRandom(s32);
s32 randomSignedOffset(s32);
s32 sub_080C36E4(s32, s32);
void sub_08054E88(s32, s32, s32, s32, s32, s32);

struct S_Tbl546F0 {
    u8 pad0;
    u8 f01;
    u8 pad2[0x0A - 0x02];
    s16 f0A;
    s16 f0C;
};

struct S_Obj546F0 {
    u8 pad0[0x08];
    u32 f08;
    u32 f0C;
    u8 pad10[0x1C - 0x10];
    s16 f1C;
    u8 pad1E[0x28 - 0x1E];
    struct S_Tbl546F0 *f28;
};

struct S_080546F0 {
    u8 pad0[0x22];
    s16 f22;
    void (*f24)(void *);
    u8 pad28[0x3C - 0x28];
    struct S_Obj546F0 *f3C;
};

extern s32 gMainWorkspace[];

/* Spawn a particle at a jittered position derived from the object's
 * coordinates, with random velocity/angle parameters, then invoke the
 * entity's callback once its script counter passes 6. */
void sub_080546F0(struct S_080546F0 *self)
{
    struct S_Obj546F0 *obj;
    struct S_Tbl546F0 *cfg;
    s32 jitterX, jitterY, spawnX, spawnY, velX, velY, angle, param, sp0;

    obj = self->f3C;
    cfg = obj->f28;
    cfg->f01 = 0;
    jitterX = randomSignedOffset(0x80000);
    cfg = obj->f28;
    spawnX = obj->f08 + ((s32)cfg->f0A << 16) + jitterX;
    jitterY = randomSignedOffset(0x80000);
    cfg = obj->f28;
    spawnY = obj->f0C + ((s32)cfg->f0C << 16) + jitterY;
    param = sub_080C36E4(gMainWorkspace[1575], 7);
    velX = (param - 3) << 13;
    velY = 0x8000 - scaleByRandom(0x20000);
    angle = sub_080C36E4(gMainWorkspace[1575], 7);
    sp0 = (s32)(s16)angle;
    sub_08054E88(spawnX, spawnY, velX, velY, sp0, (s32)(s16)obj->f1C);
    if (*(u8 *)((u8 *)self + (s32)self->f22 * 2 + 0x19) > 6) {
        self->f24(self);
    }
}
