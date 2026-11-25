void sub_08015974(void *);
void sub_080161F0(void *);
void sub_08016678(void *);
void sub_080C31E0(void *, u32);

struct Actor {
    u8 pad_0x00[0x3C];
    u32 sub;            /* sub-object driving this actor's script/animation */
};

struct ActorSub {
    u8 pad_0x00[0x24];
    u32 handler;        /* per-frame update handler, run last */
    u32 attachedA;      /* auxiliary object, freed when non-NULL */
    u32 attachedB;      /* auxiliary object, freed when non-NULL */
};

/* Per-frame actor update: free the sub-object's auxiliary objects when flagged,
 * update its animation, then run the sub-object's update handler. */
void sub_080592F0(struct Actor *actor) {
    struct ActorSub *sub = (struct ActorSub *)actor->sub;
    if (sub->attachedA != 0) {
        sub_080161F0((void *)sub->attachedA);
    }
    if (sub->attachedB != 0) {
        sub_08015974((void *)sub->attachedB);
    }
    sub_08016678(actor);
    sub_080C31E0(actor, sub->handler);
}
