extern void *spawnBudgetedEffect(s32, s32);
extern void sub_080A2D80(void *, s32, s32);
extern void sub_080A2D8C(void *, s32);

struct S_80 { u8 pad[0x80]; u8 b[1]; };

/* Spawns projectile object 0x18B owned by `owner`, giving it a velocity, a
 * lifetime, a kind and a direction taken from the facing bit of the source
 * sprite; returns NULL when the object pool is exhausted. */
void *sub_080A2D30(s32 owner, void *source, s32 kind, s32 velX, s32 velY, s32 lifetime) {
    void *obj = spawnBudgetedEffect(owner, 0x18B);
    if (obj == NULL) return NULL;
    sub_080A2D80(obj, velX, velY);
    sub_080A2D8C(obj, lifetime);
    *(s32 *)((u8 *)obj + 0x6C) = (*(u16 *)((u8 *)source + 2) & 0x10) ? 1 : -1;
    ((struct S_80 *)obj)->b[0] = kind;
    return obj;
}
