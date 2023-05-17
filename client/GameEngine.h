
#include <string>

class GameEngine 
{
    public:
    GameEngine() = default;
    void run();

    private:
    void updateView(std::string& newView);
    void runViewUpdater();
    void runServerStateUpdater();
};
