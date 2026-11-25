void sub_08015974(void);
void sub_080161F0(void);
void sub_08016678(void *);
void sub_080C31E0(void *, u32);

struct MainObj {
    u8 pad_0x00[0x22];
    s16 unk_0x22;
    u32 unk_0x24;
    u8 pad_0x28[0x38 - 0x28];
    u32 unk_0x38;
    u32 sub;            /* sub-object driving this actor's script/animation */
};

struct SubObj {
    u8 pad_0x00[0x24];
    u32 handler;        /* per-frame update handler, run last */
    u32 attachedA;      /* auxiliary object, freed when non-NULL */
    u32 attachedB;      /* auxiliary object, freed when non-NULL */
};

/* Per-frame actor update: free the sub-object's auxiliary objects when flagged,
 * update its animation, then run the sub-object's update handler. */
void sub_08053DCC(struct MainObj *actor) {
    struct SubObj *r4 = (struct SubObj *)actor->sub;
    if (r4->attachedA != 0) {
        sub_080161F0();
    }
    if (r4->attachedB != 0) {
        sub_08015974();
    }
    sub_08016678(actor);
    sub_080C31E0(actor, r4->handler);
}
