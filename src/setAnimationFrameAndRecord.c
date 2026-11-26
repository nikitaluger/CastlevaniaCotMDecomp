void setAnimationFrame(void *sprite, void *anim, s32 frame, s32 mode);

struct AnimReq {
    s8 frame;               /* +0x00: animation frame to play */
    u8 pad_0x01;
    u16 unk_0x02;           /* +0x02: copied from the sprite's animation descriptor */
};

/* Play `frame` on the sprite's animation state and record the frame plus the
 * sprite's current animation descriptor value in the request record. */
void sub_080409FC(void *sprite, void *anim, struct AnimReq *req, s32 frame) {
    req->frame = (s8)frame;
    setAnimationFrame(sprite, anim, (s16)frame, 1);
    req->unk_0x02 = *(u16 *)((u8 *)sprite + 0x28);
}
