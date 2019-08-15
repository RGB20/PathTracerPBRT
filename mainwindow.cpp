#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "glm/vec3.hpp"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::InitializeImage(int width, int height) {
    // Fill the pixels for the image
    for(int index = 0; index < (width*height); index++) {
        pixels.push_back(qRgb(0,0,0));
    }
    image = new QImage(width, height, QImage::Format_ARGB32);// (QImage((uchar *)pixels.data(), width, height, QImage::Format_ARGB32));
    image->fill(qRgb(0,0,255));
    scene = new QGraphicsScene(ui->graphicsView);
    pixMap = new QPixmap(QPixmap::fromImage(*image));
    pixelMapItem = scene->addPixmap(*pixMap);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void MainWindow::SetMainWindowDimensions(int width, int height) {
    windowWidth = width;
    windowHeight = height;

    // We apply the padding so that the graphics view item shows up without scroll bars
    int paddingWidth = 30;
    int paddingHeight = 60;
    setFixedSize(width + paddingWidth, height + paddingHeight);
}

void MainWindow::InitializeScene() {
    mainScene = std::make_shared<Scene>(windowWidth, windowHeight);

    // Process and add the shapes to the scene
    // 1. Add a sphere to the scene
//    std::shared_ptr<Sphere> simpleSphere = std::make_shared<Sphere>();
//    simpleSphere->modelMatrix = new glm::mat4(1.0f);
//    simpleSphere->invModelMatrix = new glm::mat4(1.0f);
//    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 45.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
//    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 8.0f, 4.0f));
//    (*simpleSphere->modelMatrix) = translate * rotate * scale;
//    (*simpleSphere->invModelMatrix) = glm::inverse((*simpleSphere->modelMatrix));
//    mainScene->InsertShape(simpleSphere);

    // 2. Add a plane to the scene
    std::shared_ptr<Plane> simplePlane = std::make_shared<Plane>();
    simplePlane->modelMatrix = new glm::mat4(1.0f);
    simplePlane->invModelMatrix = new glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    (*simplePlane->modelMatrix) = translate * rotate * scale;
    (*simplePlane->invModelMatrix) = glm::inverse((*simplePlane->modelMatrix));
    mainScene->InsertShape(simplePlane);
}

//#define DEBUG
void MainWindow::RenderQuads(int pixelStartPosX, int pixelStartPosY, int pixelEndPosX, int pixelEndPosY) {
#ifndef DEBUG
    for(int indexY = pixelStartPosY; indexY <= pixelEndPosY; indexY++) {
        for(int indexX = pixelStartPosX; indexX <= pixelEndPosX; indexX++) {
//          Calculate the ray origin and direction for the given pixel coordinates
#else
    {
        {
            int indexX = 399;
            int indexY = 399;
#endif
            float ndcPixelX = (2.0f * indexX / windowWidth) - 1.0f;
            float ndcPixelY = 1.0f - (2.0f * indexY / windowHeight);
            glm::vec4 pointOnfarClip = glm::inverse(mainScene->camera->viewMatrix) * glm::inverse(mainScene->camera->projectionMatrix) * (glm::vec4(ndcPixelX, ndcPixelY, 1.0f, 1.0f) * mainScene->camera->farClip);
            glm::vec3 rayDirection = glm::normalize(glm::vec3(pointOnfarClip) - mainScene->camera->cameraPos);
            std::shared_ptr<Ray> ray = std::make_shared<Ray>(mainScene->camera->cameraPos, rayDirection);
            glm::vec3 col = mainScene->Color(ray);
            image->setPixel(indexX, indexY, qRgb(col[0] , col[1] , col[2]));

        }
    }
    pixMap = new QPixmap(QPixmap::fromImage(*image));
    pixelMapItem->setPixmap(*pixMap);
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}

