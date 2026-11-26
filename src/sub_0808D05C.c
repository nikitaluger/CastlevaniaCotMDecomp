void sub_08005FC4(s32, u16, s32, u16, void *);

struct SoundVolume {
    u8 pad0[0x14DC];
    u16 volume;       /* current volume, stepped toward volumeTarget */
    u16 volumeTarget;
};
extern struct SoundVolume gMainWorkspace;

/* Set the volume of sound group arg0 to arg1: store it as both the current and
 * the target volume, then apply it at once through the per-group track callback. */
void sub_0808D05C(u16 arg0, u16 arg1)
{
    gMainWorkspace.volume = arg1;
    gMainWorkspace.volumeTarget = arg1;
    sub_08005FC4(1, arg0, 0xFFFF, arg1, (void *)0x080C129D);
}
