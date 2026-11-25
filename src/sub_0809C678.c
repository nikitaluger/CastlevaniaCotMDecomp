struct FrameEntry { u8 pad[2]; u16 id; };

extern u8 D_08101938[];
extern void sub_08014588(void *, void *);

/* Copies one of three 8-byte offset records from D_08101938 into `dst`: the
 * default record, or the variant picked by the mover's current animation frame
 * (0x7D -> variant 1, 0x83 -> variant 2). */
void sub_0809C678(void *anim, void *dstArg)
{
    void *dst = dstArg;
    s32 pose = 0;
    void **frameTable = *(void ***)((u8 *)anim + 8);
    s32 frameIndex = *(s16 *)((u8 *)anim + 0x0E) + *(u8 *)((u8 *)anim + 1);
    s32 frameId = ((struct FrameEntry *)((u8 *)*frameTable + frameIndex * 4 - 4))->id;

    if (frameId == 0x77)
        goto end;
    if (frameId <= 0x77)
        goto end;
    if (frameId == 0x7D)
        goto set1;
    if (frameId == 0x83)
        goto set2;
    goto end;
set1:
    pose = 1;
    goto end;
set2:
    pose = 2;
end:
    sub_08014588(dst, D_08101938 + pose * 8);
}
