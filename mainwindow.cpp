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
    image->fill(qRgb(0,0,0));
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
    std::shared_ptr<Sphere> simpleSphere = std::make_shared<Sphere>();
    simpleSphere->modelMatrix =  glm::mat4(1.0f);
    simpleSphere->invModelMatrix = glm::mat4(1.0f);
    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -50.0f));
    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(4.0f, 4.0f, 4.0f));
    simpleSphere->modelMatrix = translate * rotate * scale;
    simpleSphere->invModelMatrix = glm::inverse((simpleSphere->modelMatrix));
    // Setup, initialize and assign the mesh with a material
    std::shared_ptr<Diffuse> diffuseMaterial = std::make_shared<Diffuse>();
    diffuseMaterial->albedo = glm::vec3(255.0f, 0.0f, 0.0f);
    simpleSphere->material = diffuseMaterial;
    mainScene->InsertShape(simpleSphere);

    // 2. Add a plane to the scene
//    std::shared_ptr<Plane> simplePlane = std::make_shared<Plane>();
//    simplePlane->modelMatrix = glm::mat4(1.0f);
//    simplePlane->invModelMatrix = glm::mat4(1.0f);
//    glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//    glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
//    glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
//    simplePlane->modelMatrix = translate * rotate * scale;
//    simplePlane->invModelMatrix = glm::inverse((simplePlane->modelMatrix));
//    // Setup, initialize and assign the mesh with a material
//    std::shared_ptr<Diffuse> diffuseMaterial = std::make_shared<Diffuse>();
//    diffuseMaterial->albedo = glm::vec3(255.0f, 0.0f, 0.0f);
//    simplePlane->material = diffuseMaterial;
//    mainScene->InsertShape(simplePlane);

    // 3. Add a polygonal mesh to the scene
//        std::vector<glm::vec3> meshPoints;
//        meshPoints.push_back(glm::vec3(-0.5f, -0.5f, 0.0f));
//        meshPoints.push_back(glm::vec3(0.0f, 0.5f, 0.0f));
//        meshPoints.push_back(glm::vec3(0.5f, -0.5f, 0.0f));
//        std::vector<int> triangulatedMeshIndixes;
//        triangulatedMeshIndixes.push_back(0);
//        triangulatedMeshIndixes.push_back(1);
//        triangulatedMeshIndixes.push_back(2);
//        bool backfaceCulling = true;
//        bool clockwiseTriangulation = false;
//        std::shared_ptr<Polygon> simplePolygonalMesh = std::make_shared<Polygon>(meshPoints, triangulatedMeshIndixes, backfaceCulling, clockwiseTriangulation);
//        simplePolygonalMesh->modelMatrix = glm::mat4(1.0f);
//        simplePolygonalMesh->invModelMatrix = glm::mat4(1.0f);
//        glm::mat4 rotate = glm::rotate(glm::mat4(1.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
//        glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
//        glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 2.0f));
//        simplePolygonalMesh->modelMatrix = translate * rotate * scale;
//        simplePolygonalMesh->invModelMatrix = glm::inverse((simplePolygonalMesh->modelMatrix));
//    // Setup, initialize and assign the mesh with a material
//        std::shared_ptr<Diffuse> diffuseMaterial = std::make_shared<Diffuse>();
//        diffuseMaterial->albedo = glm::vec3(255.0f, 0.0f, 0.0f);
//        simplePolygonalMesh->material = diffuseMaterial;
//        mainScene->InsertShape(simplePolygonalMesh);
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
            int indexX = 410;
            int indexY = 389;
#endif
            float ndcPixelX = (2.0f * indexX / windowWidth) - 1.0f;
            float ndcPixelY = 1.0f - (2.0f * indexY / windowHeight);
            glm::vec4 pointOnfarClip = glm::inverse(mainScene->camera->viewMatrix) * glm::inverse(mainScene->camera->projectionMatrix) * (glm::vec4(ndcPixelX, ndcPixelY, 1.0f, 1.0f) * mainScene->camera->farClip);
            glm::vec3 rayDirection = glm::normalize(glm::vec3(pointOnfarClip) - mainScene->camera->cameraPos);
            std::shared_ptr<Ray> ray = std::make_shared<Ray>(mainScene->camera->cameraPos, rayDirection);
            glm::vec3 col = mainScene->Color(ray);
            image->setPixel(indexX, indexY, qRgb(col[0], col[1], col[2]));
        }
    }
}

void MainWindow::UpadateScene() {
    pixMap = new QPixmap(QPixmap::fromImage(*image));
    pixelMapItem->setPixmap(*pixMap);
}

MainWindow::~MainWindow()
{
    delete image;
    delete ui;
}

