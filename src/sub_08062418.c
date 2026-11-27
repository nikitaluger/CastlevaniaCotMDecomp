void copyBytes(void *, const void *, s32);
void resetMapRender(void);
void setLayerTilemap(s32, s32);
void setMapLayerParams(u8, s32, s32);
void setScreenTransition(s32);
void sub_0805FEC8(u16);

extern const u8 D_080DBE20[];
extern const u16 D_080CFEBC[];
extern const u16 D_080CE388[];

/* Set up a message-window scene: reset the script engine, load tileset 0x89,
 * select the window layer (2 or 3) for the given scene type, then run the
 * script id chosen by the index from that type's script table. */
void sub_08062418(u8 sceneType, u8 scriptIndex) {
    u8 layer[4];
    u8 type;
    u8 index;

    type = sceneType;
    index = scriptIndex;
    copyBytes(layer, D_080DBE20, 2);
    resetMapRender();
    setLayerTilemap(0, 0x89);
    setMapLayerParams(layer[type], 1, 1);
    setScreenTransition(0);
    if (type != 0) {
        sub_0805FEC8(D_080CFEBC[index]);
    } else {
        sub_0805FEC8(D_080CE388[index * 2]);
    }
}
