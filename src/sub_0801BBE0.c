extern u16 sub_08014990(s32);
extern void *spawnBudgetedEffect(void *, s32);

/* Three parallel 5-entry u16 arrays in the entity's data block: x at +0, y at
 * +10, direction at +20. Advancing the pointer by 2 fills one column of all
 * three arrays per iteration. */
struct Fill {
  u16 x;
  u8 pad1[8];
  u16 y;
  u8 pad2[8];
  u16 direction;
};
/* Fixed-point position of a child object. */
struct ObjFields {
  u8 pad0[0x4C];
  s16 x;
  u8 pad1[6];
  s16 y;
};
/* Round a 16.16 fixed-point value toward +infinity and take its whole part. */
static inline s32 adj(s32 xval) { if (xval < 0) xval += 0xFFFF; return xval >> 16; }

/* Fills the entity's direction tables and creates one or two child objects at
 * the entity's fixed-point coordinates. */
void sub_0801BBE0(u8 *self) {
    u8 *base;
    s32 param = *(s32 *)(self + 0x38);
    u16 dir;
    s32 i;
    struct Fill *p;
    u8 *obj, *obj2;
    s32 objX, objY, childX, childY;

    base = *(u8 **)(self + 0x3C);
    dir = sub_08014990(param);
    p = (struct Fill *)(base + 0xA8);
    i = 4;

    do {
        p->x = *(s32 *)(base + 8);
        p->y = *(s32 *)(base + 0xC);
        p->direction = dir;
        p = (struct Fill *)((u8 *)p + 2);
        i--;
    } while (i >= 0);

    obj = spawnBudgetedEffect(self, 0x8E);
    if (obj != 0) {
        objX = adj(*(s32 *)(base + 8));
        ((struct ObjFields *)obj)->x = objX;
        objY = adj(*(s32 *)(base + 0xC));
        ((struct ObjFields *)obj)->y = objY;
        *(u16 *)(obj + 0x5C) = dir;
        obj2 = spawnBudgetedEffect(obj, 0x8E);
        if (obj2 != 0) {
            childX = adj(*(s32 *)(base + 8));
            ((struct ObjFields *)obj2)->x = childX;
            childY = adj(*(s32 *)(base + 0xC));
            ((struct ObjFields *)obj2)->y = childY;
            *(u16 *)(obj2 + 0x5C) = dir;
        }
    }
}
