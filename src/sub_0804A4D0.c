void sub_08011368(void *sprite, void *anim, s32 frame, s32 mode);

struct AnimReq {
    u8 pad_0x00[0x06];
    u16 unk_0x06;           /* +0x06: copied from the sprite's animation descriptor */
    s8 frame;               /* +0x08: animation frame to play */
};

/* Play `frame` on the sprite's animation state and record the frame plus the
 * sprite's current animation descriptor value in the request record. */
void sub_0804A4D0(void *sprite, void *anim, struct AnimReq *req, s32 frame) {
    req->frame = (s8)frame;
    sub_08011368(sprite, anim, (s16)frame, 1);
    req->unk_0x06 = *(u16 *)((u8 *)sprite + 0x28);
}
