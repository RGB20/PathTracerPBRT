#include "mainwindow.h"
#include <QApplication>
#include <thread>

#define WIDTH 800
#define HEIGHT 800

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow mainWindow;
    mainWindow.SetMainWindowDimensions(WIDTH, HEIGHT);
    mainWindow.InitializeImage(WIDTH, HEIGHT);
    mainWindow.InitializeScene();
    mainWindow .show();

    int gridDimX = 16;
    int gridDimY = 16;
    std::vector<std::thread> threads;
    for(int gridIndexX = 0; gridIndexX < gridDimX; gridIndexX++) {
        int startIndexX = gridIndexX * WIDTH / gridDimX;
        int endIndexX = (gridIndexX + 1) * WIDTH / gridDimX - 1;
        for(int gridIndexY = 0; gridIndexY < gridDimY; gridIndexY++) {
            int startIndexY = gridIndexY * HEIGHT / gridDimY;
            int endIndexY = (gridIndexY + 1) * HEIGHT / gridDimY - 1;
            threads.push_back(std::thread(&MainWindow::RenderQuads, &mainWindow, startIndexX, startIndexY, endIndexX, endIndexY));
        }
    }
    // Wait for the threads to complete before exiting
    for(size_t threadIndex = 0; threadIndex < threads.size(); threadIndex++) {
        threads[threadIndex].join();
    }
    mainWindow.UpadateScene();
    return a.exec();
}
