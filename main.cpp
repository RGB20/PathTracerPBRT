#include "mainwindow.h"
#include <QApplication>

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
    for(int gridIndexX = 0; gridIndexX < gridDimX; gridIndexX++) {
        int startIndexX = gridIndexX * WIDTH / gridDimX;
        int endIndexX = (gridIndexX + 1) * WIDTH / gridDimX - 1;
        for(int gridIndexY = 0; gridIndexY < gridDimY; gridIndexY++) {
            int startIndexY = gridIndexY * HEIGHT / gridDimY;
            int endIndexY = (gridIndexY + 1) * HEIGHT / gridDimY - 1;
            mainWindow.RenderQuads(startIndexX, startIndexY, endIndexX, endIndexY);
        }
    }
    return a.exec();
}
