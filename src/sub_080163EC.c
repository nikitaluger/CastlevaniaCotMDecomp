struct CameraTarget { struct CameraTarget *self; u16 x; u16 y; };
extern struct CameraTarget D_020202B8;

/* Set the global view target from two world coordinates: convert each to
 * 32-pixel units (the fixed bias recenters the X origin), store them, and
 * point the node back at itself. */
void sub_080163EC(s32 worldX, u32 worldY) {
    D_020202B8.x = (u16)((u32)(worldX + (s32)0xF9FF0000) >> 5);
    D_020202B8.y = (u16)(worldY >> 5);
    D_020202B8.self = &D_020202B8;
}
