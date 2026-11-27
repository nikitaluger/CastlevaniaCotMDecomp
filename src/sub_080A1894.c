extern u32 D_0866FDEC[];
void advanceAnimTrackByDelta(void *, void *, u32);
void advanceMotion(void *, s32);

/* Look up an id from the action object's data; when it is 11 or 12 set the
 * target's +0x10 velocity to +2.0 or -2.0 depending on a flag in the source,
 * otherwise clear it. Then update the target's accumulated motion and return
 * the action's flag bits. */
u8 sub_080A1894(void *source, void *target, void *action, void *context)
{
    u32 tablePtr;
    u32 animId;
    u32 velocity;
    s32 minAnimId = 0x0B;
    advanceAnimTrackByDelta(source, action, D_0866FDEC[((u8 *)context)[0x16]]);
    tablePtr = *(u32 *)((u8 *)action + 8);
    animId = *(s16 *)((u8 *)action + 0x0E);
    animId += ((u8 *)action)[1];
    tablePtr = *(u32 *)tablePtr;
    animId = animId * 4 + tablePtr - 4;
    animId = *(u16 *)((u8 *)animId + 2);
    if (animId > 0x0C) goto end;
    if (animId < minAnimId) goto end;
    if ((*((u16 *) ((u8 *)source + 2))) & 0x10)
        velocity = 0x20000;
    else
        velocity = 0xFFFE0000;
    *((u32 *) ((u8 *)target + 0x10)) = velocity;
    goto done;
end:
    *((u32 *) ((u8 *)target + 0x10)) = 0;
done:
    advanceMotion(target, 0);
    return ((u8 *)action)[0] & 2;
}
