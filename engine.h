#ifndef ENGINE_H
#define ENGINE_H


class Engine
{
private:
    static bool m_isRunning;
public:
    static const int TILE_SIZE;
    static int getScreenHeight();
    static int getScreenWidth();
    static bool isRunning();
    static void stop();
};

#endif // ENGINE_H
