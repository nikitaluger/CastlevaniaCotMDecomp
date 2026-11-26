void sub_080144D8(void *, void *);
void sub_080144FC(void *, void *);
void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void copyPoseAttrs(void *, void *);

/* Advance this actor to its next script step (state table 0x0866DD1C): stamp
 * the step on its sprite, bump and mark the step counter, dispatch the step's
 * handler, then reposition the sprite on screen. */
void sub_08033174(void *arg0) {
    void *sprite = *(void **)((u8 *)arg0 + 0x38);
    sub_080144D8(arg0, sprite);
    *(void **)((u8 *)arg0 + 0x14) = (void *)0x0866DD1C;
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) + 1);
    {
        u8 *stepByte = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        stepByte[0x19] = (u8)(stepByte[0x19] + 1);
        {
            s32 stepOffset = (*(s16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *steps = (u8 *)arg0 + 0x18;
            u8 cmd = *(steps + stepOffset);
            void **table = *(void ***)((u8 *)arg0 + 0x14);
            void *handler = table[cmd];
            sub_080C31E0(arg0, handler);
        }
    }
    *(u16 *)((u8 *)arg0 + 0x22) = (u16)(*(u16 *)((u8 *)arg0 + 0x22) - 1);
    sub_080144FC(arg0, sprite);
}

/* If the actor is already flagged (f7C), clear the "finished" bit (0x40) on
 * its sprite; otherwise clear the current step's progress byte and advance to
 * the next script step. */
void sub_080338B4(void *arg0) {
    u8 *self = (u8*)arg0;
    u8 *sprite = *(u8**)(self + 0x38);
    if (self[0x7C] != 0) {
        sprite[0x2A] = (u8)(sprite[0x2A] & 0xBF);
        return;
    }
    self[*(s16*)(self+0x22)*2 + 0x19] = 0;
    {
        void **stepFnTable = (void**)0x08671BC0;
        sub_080C31E4(self + 0x18, self + 0x22, (s32)*stepFnTable);
    }
}

/* Layout of the actor header holding the view pointer at +0x30, and of the
 * view object receiving the copied motion state. */
struct S338F0 { u8 pad[0x30]; u8 * volatile f30; };
struct O338F0 {
    u8 pad0[0x4C];
    u32 f4C;
    u8 pad1[0x5C - 0x50];
    u32 f5C;
    u8 pad2[0x6C - 0x60];
    u16 f6C;
    u8 pad3[0x74 - 0x6E];
    u16 f74;
    u8 pad4[0x7C - 0x76];
    u8 f7C;
    u8 pad5[0x80 - 0x7D];
    u8 f80;
    u8 pad6[0x84 - 0x81];
    u8 f84;
};
/* Copy this actor's state (position, action parameters, facing) into the view
 * object at owner->f30, then flag it for a re-draw. */
void sub_080338F0(u8 *owner, u8 *source, u8 *params)
{
    struct S338F0 *self;
    u8 *view;
    u8 *paramPtr;
    unsigned long long one;
    u8 *stepPtr;
    self = (struct S338F0 *) owner;
    paramPtr = params + 0;
    one = 1;
    view = self->f30;
    if (view == 0) return;
    *((u8 *) (view + 0x80)) = one;
    ((struct O338F0 *) self->f30)->f84 = *((u8 *) (params + 2)) & 0x10;
    *((u32 *) (self->f30 + 0x4C)) = *((u32 *) (source + 8));
    *((u32 *) (self->f30 + 0x5C)) = *((u32 *) (source + 0xC));
    ((struct O338F0 *) self->f30)->f6C = *((u16 *) paramPtr);
    ((struct O338F0 *) self->f30)->f74 = *((u16 *) (params + 2));
    stepPtr = (u8 *) ((((u32) *((s16 *) (((u8 *) owner) + 0x22))) * 2) + (u32) owner);
    if (stepPtr[0x1A] == 4)
        *((u8 *) (self->f30 + 0x7C)) = one;
    else
        *((u8 *) (self->f30 + 0x7C)) = 0;
}

/* Copy the motion-parameter entry for the actor's current action into its view
 * object: action indices 0x43..0x47 select table entries 1..5 (entry 0 is the
 * default), 8 bytes per entry at 0x080CEC8C. */
void sub_08033950(void *arg0, void *arg1) {
    u16 action;
    u32 idx;
    u32 entry;
    u32 view;

    entry = 0;
    action = *(u16 *)((u8 *)arg0 + 0x28);
    idx = action - 0x43;
    if (idx <= 4) {
        switch (idx) {
            case 0: entry = 1; break;
            case 1: entry = 2; break;
            case 2: entry = 3; break;
            case 3: entry = 4; break;
            case 4: entry = 5; break;
        }
    }
    view = *(u32 *)((u8 *)arg1 + 0x28);
    copyPoseAttrs((void *)view, (void *)(0x080CEC8C + entry * 8));
}
