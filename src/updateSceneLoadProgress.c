struct SceneLoadWorkspace {
    u8 _0[0x14B4];
    u32 areaId;            /* 0x14B4 */
    u32 areaParam;         /* 0x14B8 */
    u8 _14BC[0x388];
    u32 loadFlags;         /* 0x1844: kind-loaded / scene-init progress bits */
    u8 _1848[4];
    u32 objKind07Root;     /* 0x184C */
    u32 objKind08Root;     /* 0x1850 */
    u32 objKind09Root;     /* 0x1854 */
    u32 objKind0ARoot;     /* 0x1858 */
    u32 objKind0BRoot;     /* 0x185C */
    u32 objKind0CRoot;     /* 0x1860 */
    u32 objKind0DRoot;     /* 0x1864 */
    u32 objKind0ERoot;     /* 0x1868 */
    u32 objKind0FRoot;     /* 0x186C */
    u32 objKind10Root;     /* 0x1870 */
    u32 objKind11Root;     /* 0x1874 */
    u32 objKind12Root;     /* 0x1878 */
    u32 objKind13Root;     /* 0x187C */
    u32 objKind14Root;     /* 0x1880 */
    u32 _1884;
    u32 objKind16Root;     /* 0x1888: kind 0x11 */
    u8 _188C[8];
    u32 stepCounterA;      /* 0x1894 */
    u32 stepCounterB;      /* 0x1898 */
    u32 stepCounterC;      /* 0x189C */
    u32 stepCounterD;      /* 0x18A0 */
};

struct SceneStepObj {
    u8 _0[0x14];
    void *unk14;
    u8 _18[0xA];
    s16 stepIndex;         /* 0x22 */
    u8 _24[4];
};

void updateObjectTree(u32);
void selectSceneMode(void);
void loadSceneGraphics(void);
volatile int sub_080C31E4(void *, void *, s32);
extern struct SceneLoadWorkspace gMainWorkspace;
extern s32 gMainObjTimerCallbacks;

/* Step the scene-load object trees according to the load flags, count off the
 * delayed steps, and reset the workspace for a fresh scene once every flag is set. */
void updateSceneLoadProgress(void *entity) {
    s32 count;

    if ((gMainWorkspace.loadFlags & 0x40200000) == 0x200000) updateObjectTree(gMainWorkspace.objKind07Root);
    if (!(gMainWorkspace.loadFlags & 0x20000000)) updateObjectTree(gMainWorkspace.objKind08Root);
    if (!(gMainWorkspace.loadFlags & 0x10000000)) updateObjectTree(gMainWorkspace.objKind09Root);
    if (!(gMainWorkspace.loadFlags & 0x08000000)) updateObjectTree(gMainWorkspace.objKind0ARoot);
    if (!(gMainWorkspace.loadFlags & 0x04000000)) updateObjectTree(gMainWorkspace.objKind0BRoot);
    updateObjectTree(gMainWorkspace.objKind0CRoot);
    gMainWorkspace.stepCounterA += 1;
    if ((gMainWorkspace.loadFlags & 0x41000000) == 0x40000000) updateObjectTree(gMainWorkspace.objKind0DRoot);
    if ((gMainWorkspace.loadFlags & 0x00C00000) == 0x00400000) {
        updateObjectTree(gMainWorkspace.objKind0ERoot);
        count = gMainWorkspace.stepCounterB + 1;
        gMainWorkspace.stepCounterB = count;
        if (count > 1) gMainWorkspace.loadFlags |= 0x00800000;
    }
    if ((gMainWorkspace.loadFlags & 0x04400000) == 0x04000000) updateObjectTree(gMainWorkspace.objKind0FRoot);
    if ((gMainWorkspace.loadFlags & 0x00600000) == 0x00400000) {
        updateObjectTree(gMainWorkspace.objKind10Root);
        count = gMainWorkspace.stepCounterC + 1;
        gMainWorkspace.stepCounterC = count;
        if (count > 1) gMainWorkspace.loadFlags |= 0x00200000;
    }
    if ((gMainWorkspace.loadFlags & 0x00420000) == 0x00400000) {
        updateObjectTree(gMainWorkspace.objKind14Root);
        count = gMainWorkspace.stepCounterD + 1;
        gMainWorkspace.stepCounterD = count;
        if (count > 1) gMainWorkspace.loadFlags |= 0x00020000;
    }
    if (!(gMainWorkspace.loadFlags & 0x00100000)) updateObjectTree(gMainWorkspace.objKind11Root);
    if (!(gMainWorkspace.loadFlags & 0x00080000)) updateObjectTree(gMainWorkspace.objKind12Root);
    if (!(gMainWorkspace.loadFlags & 0x00040000)) updateObjectTree(gMainWorkspace.objKind13Root);
    updateObjectTree(gMainWorkspace.objKind16Root);
    if (gMainWorkspace.loadFlags == 0x7FFE0000) {
        gMainWorkspace.loadFlags = 0;
        selectSceneMode();
        loadSceneGraphics();
        gMainWorkspace.areaParam = (gMainWorkspace.areaId & 0xF0) | 8;
        updateObjectTree(gMainWorkspace.objKind07Root);
        updateObjectTree(gMainWorkspace.objKind0BRoot);
        updateObjectTree(gMainWorkspace.objKind0CRoot);
        gMainWorkspace.stepCounterA += 1;
        updateObjectTree(gMainWorkspace.objKind0DRoot);
        gMainWorkspace.areaId = 0;
        gMainWorkspace.areaParam = 0;
        *(u8 *)((u8 *)entity + ((struct SceneStepObj *)entity)->stepIndex * 2 + 0x19) = 0;
        {
            s32 *callback = &gMainObjTimerCallbacks;
            sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
        }
    }
}
