struct S_02025FF0 { u8 _0[0x10]; u32 v10; u8 _1[0x14ED-0x14]; u8 v14ED; u8 _2[0x173A-0x14EE]; u8 v173A; u8 _3[0x18C2-0x173B]; u16 v18C2; };
extern struct S_02025FF0 gMainWorkspace;

void stepDelayTimer(void *, void *);
void sub_0806D330(void *, void *);
s32 checkGlobalStateChange(void *, void *, void *);
void sub_0806D588(void *, void *);
void spawnKind2CEntity(s32, s32, s32, s32);
u8 sub_08072280(s32, s32, s32, s32);
void sub_080C31E0(void *, s32);

/* Update a scripted entity's motion while it is active: tick its timer and
 * velocity, aim it along its movement segment, integrate its position, then
 * despawn on the linked flag or the global stop condition. */
void sub_08083EBC(void *entity) {
    void *body;
    void *owner;
    void *component;

    owner = *(void **)((u8 *)entity + 0x6C);
    body = (u8 *)owner + 4;
    component = *(void **)((u8 *)entity + 0x38);
    if (checkGlobalStateChange(entity, component, body) == 0) {
        *(s32 *)((u8 *)body + 0x10) = *(s32 *)((u8 *)body + 0x10) + 1;
        if (!(*(s32 *)((u8 *)body + 0x10) & 7)) {
            spawnKind2CEntity(*(s32 *)((u8 *)entity + 0x28), 0xC, *(s32 *)((u8 *)owner + 4), *(s32 *)((u8 *)body + 4));
        }
        *(s32 *)((u8 *)body + 0x0C) = *(s32 *)((u8 *)body + 0x0C) + 0x2000;
        if (*(s32 *)((u8 *)body + 0x0C) > 0x80000) {
            *(s32 *)((u8 *)body + 0x0C) = 0x80000;
        }
        {
            s32 x0 = *(s32 *)((u8 *)owner + 4);
            s32 y0 = *(s32 *)((u8 *)body + 4);
            s32 x1 = x0 + *(s32 *)((u8 *)body + 8);
            s32 y1 = y0 + *(s32 *)((u8 *)body + 0x0C);
            s32 frac = sub_08072280(x0, y0, x1, y1);
            s32 angle = 0x100 - frac;
            *(s16 *)((u8 *)component + 8) = (s16)(angle << 8);
        }
        *(s32 *)((u8 *)owner + 4) = *(s32 *)((u8 *)owner + 4) + *(s32 *)((u8 *)body + 8);
        *(s32 *)((u8 *)body + 4) = *(s32 *)((u8 *)body + 4) + *(s32 *)((u8 *)body + 0x0C);
        if (*(u16 *)((u8 *)*(void **)((u8 *)body + 0x2C) + 0x14) & 1) {
            spawnKind2CEntity(*(s32 *)((u8 *)entity + 0x28), 0xD, *(s32 *)((u8 *)owner + 4), *(s32 *)((u8 *)body + 4));
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
            return;
        }
        *(u16 *)((u8 *)component + 0) = gMainWorkspace.v18C2;
        stepDelayTimer((u8 *)owner + 0x20, component);
        sub_0806D588(component, body);
        sub_0806D330(entity, component);
        if ((gMainWorkspace.v173A == 0x1C) || ((gMainWorkspace.v14ED == 0) && (gMainWorkspace.v10 != 0))) {
            sub_080C31E0(entity, *(s32 *)((u8 *)entity + 0x24));
        }
    }
}
