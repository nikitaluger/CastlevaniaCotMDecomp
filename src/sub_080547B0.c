/* identical to sub_08014290 (matched), with its names changed by decompdecomp */
void sub_08015974(void);
void unlinkAndFreeObject(void);
void sub_08016678(void *);
void sub_080C31E0(void *, u32);
void sub_08062394(s32, u8);
s32 isOutsideCameraBounds(s32, s32);

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
void sub_080547B0(struct MainObj *actor) {
    struct SubObj *sub = (struct SubObj *)actor->sub;
    if (sub->attachedA != 0) {
        unlinkAndFreeObject();
    }
    if (sub->attachedB != 0) {
        sub_08015974();
    }
    sub_08016678(actor);
    sub_080C31E0(actor, sub->handler);
}

void uploadPendingSpriteGraphic(void *arg0, void *arg1) {
    u16 temp_r2;
    void *temp_r3;

    temp_r3 = *(void **)((u8 *)arg0 + 0x3C);
    if ((temp_r3 != NULL) && (arg1 != NULL)) {
        temp_r2 = *(u16 *)temp_r3;
        if (!(0x20 & temp_r2) && ((3 & temp_r2) || (1 & *(u16 *)((u8 *)arg1 + 0x14)))) {
            *(u16 *)temp_r3 = (u16)(0x20 | temp_r2);
            sub_08062394(0, *(u8 *)((u8 *)temp_r3 + 0x1C));
        }
    }
}

void sub_08014314(u16 *arg0, void *arg1) {
    if (0xC & *arg0) {
        *(u8 *)((u8 *)arg1 + 1) = 0;
    }
}

void checkActorViewBounds(void *arg0, void *arg1) {
    void *temp_r1;

    if (isOutsideCameraBounds(*(u32 *)((u8 *)arg1 + 8), *(u32 *)((u8 *)arg1 + 0xC)) == 1) {
        *(u8 *)((u8 *)arg0 + 0x2A) = (u8)(0xBF & *(u8 *)((u8 *)arg0 + 0x2A));
        temp_r1 = *(void **)((u8 *)arg1 + 0x28);
        if (temp_r1 != NULL) {
            *(u8 *)((u8 *)temp_r1 + 1) = 0;
        }
        if (!(0xD & *(u16 *)arg1)) {
            return 1;
        }
        return 0;
    }
    *(u8 *)((u8 *)arg0 + 0x2A) = (u8)(0x40 | *(u8 *)((u8 *)arg0 + 0x2A));
    return 0;
}
