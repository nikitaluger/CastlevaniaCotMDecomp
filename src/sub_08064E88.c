struct ActorUpdate {
    u8 _0[0x18]; u8 kind; u8 _19[9]; s16 step; u8 _24[0x14];
    u32 parent; u8 _3C[0x30]; u32 state;
};
struct ActorState {
    u8 _0[8]; u32 f08; u32 f0C; u8 _10[0x1A]; u16 align; u16 action;
    u8 _2E[0x12]; u32 f40; u8 _44[0x80]; u32 result;
};
struct S32Table { u8 pad[0x50]; s32 values[1]; };
extern s32 sub_0806C4B4(void *, void *);
extern void sub_0806C5EC(void *, void *, void *, void *);
extern void sub_0806AB04(void *, void *, void *, void *);
extern void sub_0806A884(void *, void *);
extern void sub_0806A800(void *, s32);
extern u16 sub_0806BCD8(void *, void *, void *, void *);
extern void sub_0806C6B0(void *, void *, void *, void *);
extern void sub_08003740(void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void sub_080C31E4(void *, void *, s32);
extern void *D_08671BB0;
extern void *D_08671BD8;
extern struct S32Table D_080E03A0;

/* Updates one actor for the current frame: picks a target position, resets its
 * contact state, applies the camera-relative position fix, runs the special
 * action for kind 0x14, then runs the actor's main update routine. */
void sub_08064E88(struct ActorUpdate *entity) {
    u8 *state; struct ActorState *actor; struct ActorState *actorAlias;
    s32 parent; s32 posMode; s32 adjust;

    state = (u8 *)entity->state;
    actorAlias = (struct ActorState *)(state + 4);
    parent = entity->parent;
    actor = actorAlias;
    posMode = sub_0806C4B4(actorAlias, actor);
    if (posMode != 0) return;
    sub_0806C5EC(entity, (void *)parent, actor, actor);
    sub_0806AB04(entity, (void *)parent, actor, actor);
    sub_0806A884((void *)parent, actor);
    sub_08003740(state + 0x2C, (void *)parent);
    if (entity->kind == 0x14) {
        switch (actor->action) {
        case 2:
            sub_0806A800(actor, 0x86);
            break;
        case 3:
            sub_0806A800(actor, 0x87);
            adjust = D_080E03A0.values[0x16 * *(s32 *)((u8 *)actor + 0x44)];
            if (*(u16 *)((u8 *)parent + 2) & 0x10) adjust = -adjust;
            *(s32 *)((u8 *)actor + 8) = adjust;
            *(u8 *)((u32)entity->step * 2 + (u32)entity + 0x19) = posMode;
            { void **fnaddr = &D_08671BB0; sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, (s32)*fnaddr); }
            break;
        }
    }
    actorAlias->result = sub_0806BCD8(entity, (void *)parent, actorAlias, actor);
    if (actorAlias->result != 0) {
        sub_08003740((u8 *)actorAlias + 0x28, (void *)parent);
        *(u8 *)((u32)entity->step * 2 + (u32)entity + 0x17) = 0;
        { void **fnaddr = &D_08671BD8; sub_080C31E8((u8 *)entity + 0x18, (u8 *)entity + 0x22, actorAlias->result, *fnaddr); }
    }
    sub_0806C6B0(entity, (void *)parent, actorAlias, actor);
}
