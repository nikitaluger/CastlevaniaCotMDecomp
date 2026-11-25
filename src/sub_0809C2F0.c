extern s32 sub_0801147C(s32, s32, s32, s32, s32);

/* Initialize the object's graphics animation from the frame-data table at
 * 0x08101884, uploading tiles to VRAM 0x06014000 + tileIndex*0x20 bytes. */
void sub_0809C2F0(s32 obj, s32 anim, s32 tileIndex, s32 allocUnits)
{
    sub_0801147C(obj, anim, 0x08101884, (tileIndex << 5) + 0x06014000, allocUnits);
}
