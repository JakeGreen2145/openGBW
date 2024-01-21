
// Enum for device states
enum GrinderState {
    STATUS_EMPTY = 0,
    STATUS_GRINDING_IN_PROGRESS = 1,
    STATUS_GRINDING_FINISHED = 2,
    STATUS_GRINDING_FAILED = 3,
    STATUS_IN_MENU = 4,
    STATUS_IN_SUBMENU = 5
};

// Enum for menu IDs
enum MenuId {
    NONE = 0,
    MAIN_MENU = 1,
    CUP_WEIGHT_MENU = 2,
    CALIBRATE = 3,
    OFFSET = 4,
    SCALE_MODE = 5,
    GRINDING_MODE = 6,
    SLEEP = 7,
    EXIT = 8,
    RESET = 9
};

class DeviceState {
    private:
        static MenuId activeMenu;
        static GrinderState grinderState;
    public:
        // Setters
        static void setActiveMenu(MenuId activeMenu);
        static void setGrinderState(GrinderState grinderState);

        // Getters
        static MenuId getActiveMenu();
        static GrinderState getGrinderState();
};