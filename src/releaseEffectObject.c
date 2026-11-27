s32 unlinkAndFreeObject();
s32 unregisterSpriteEntity();
void sub_080C31E0(void *, s32);

/* Tears down `obj`: unregisters it, frees the sub-object recorded at data+0x28
 * when present, then hands the +0x24 value to the generic release handler. */
void releaseEffectObject(void *obj)
{
    void *data = *(void **)((u8 *)obj + 0x3C);

    unregisterSpriteEntity();
    if (*(s32 *)((u8 *)data + 0x28) != 0)
    {
        obj++;
        obj--;
        unlinkAndFreeObject();
    }
    sub_080C31E0(obj, *(s32 *)((u8 *)data + 0x24));
}
