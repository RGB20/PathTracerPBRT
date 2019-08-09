#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <vector>
#include <stdint.h>

#include "scene.h"
#include "sphere.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetMainWindowDimensions(int width, int height);

    void InitializeImage(int width, int height);

    // Render the image to the screen in quads
    void RenderQuads(int pixelStartPosX, int pixelStartPosY, int pixelEndPosX, int pixelEndPosY);

    void InitializeScene();

private:
    Ui::MainWindow *ui;

    int windowWidth;
    int windowHeight;

    QGraphicsScene* scene;
    QPixmap *pixMap;
    QGraphicsPixmapItem *pixelMapItem;
    QImage* image;
    std::vector<int32_t> pixels;

    std::shared_ptr<Scene> mainScene;
};

#endif // MAINWINDOW_H
