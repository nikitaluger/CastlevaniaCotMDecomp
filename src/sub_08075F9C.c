struct S_02025FF0 { u8 _0[0x10]; u32 v10; u8 _1[0x14ED-0x14]; u8 v14ED; u8 _2[0x173A-0x14EE]; u8 v173A; u8 _3[0x18C2-0x173B]; u16 v18C2; };
extern struct S_02025FF0 gMainWorkspace;

extern s32 stepDelayTimer(void *, void *);
extern s32 sub_0806D330(void *, void *);
extern s32 checkGlobalStateChange(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 spawnKind2CEntity(s32, s32, s32, s32);
extern void sub_080C31E0(void *, u32);

/* Update a scripted entity's motion while active: tick its velocity, integrate
 * its position, then despawn on the linked flag or the global stop condition. */
void sub_08075F9C(void *entity)
{
    void *self;
    void *owner;
    void *body;
    void *component;
    struct S_02025FF0 *state;
    s32 sum;

    self = entity;
    owner = *((void **)(((u8 *)entity) + 0x6C));
    body = ((u8 *)owner) + 4;
    component = *((void **)(((u8 *)entity) + 0x38));

    if (checkGlobalStateChange(entity, component, body) != 0)
    {
        return;
    }

    {
        s32 v = *((s32 *)(((u8 *)body) + 0xC));
        v += 0x4000;
        *((s32 *)(((u8 *)body) + 0xC)) = v;
        if (v > 0x80000)
        {
            *((s32 *)(((u8 *)body) + 0xC)) = 0x80000;
        }
    }

    {
        s32 v = *((s32 *)(((u8 *)owner) + 0x4));
        v += *((s32 *)(((u8 *)body) + 0x8));
        *((s32 *)(((u8 *)owner) + 0x4)) = v;
    }

    {
        s32 v = *((s32 *)(((u8 *)body) + 0x4));
        do {
            sum = v + *((s32 *)(((u8 *)body) + 0xC));
        } while (0);
        *((s32 *)(((u8 *)body) + 0x4)) = sum;
    }

    {
        u16 *flags = *((u16 **)(((u8 *)body) + 0x2C));
        if (flags[0x14 / 2] & 1)
        {
            spawnKind2CEntity(*((s32 *)(((u8 *)entity) + 0x28)), 8, *((s32 *)(((u8 *)owner) + 0x4)), *((s32 *)(((u8 *)body) + 0x4)));
            sub_080C31E0(entity, *((s32 *)(((u8 *)entity) + 0x24)));
            return;
        }
    }

    state = &gMainWorkspace;
    *((u16 *)component) = state->v18C2;
    stepDelayTimer(((u8 *)owner) + 0x20, component);
    sub_0806D588(component, body);
    sub_0806D330(entity, component);

    if (state->v173A == 0x1C)
    {
        goto call;
    }
    if (state->v14ED != 0)
    {
        goto end;
    }
    if (state->v10 == 0)
    {
        goto end;
    }

call:
    sub_080C31E0(entity, *((s32 *)(((u8 *)entity) + 0x24)));

end:
    return;
}
