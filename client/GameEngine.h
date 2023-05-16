class GameEngine 
{
    public:
    GameEngine() = default;
    void run();

    private:
    void updateView(char* newView);
    void runViewUpdater();
    void runServerStateUpdater();
};
