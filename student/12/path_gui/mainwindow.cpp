
#include "mainwindow.hh"
#include "ui_mainwindow.h"

#include <QTimer>
#include <QKeyEvent>
#include <QGraphicsEllipseItem>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsEffect>
#include <QMessageBox>

PathWindow::PathWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::PathWindow)
    , board_(new PathBoard)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw the gameboard
    scene_ = board_;

    // Connecting buttons and formatting the elements
    setupUI();

    // Connecting graphicsView to the scene
    ui->graphicsView->setScene(scene_);

    // The dimensions of the scene
    scene_->setSceneRect(0, 0, SCENE_WIDTH, SCENE_HEIGHT);

    // Defining the board and backgroundcolour
    InitBoard();
    setBackgroundColor();

    // Setting up UI elements
    setupColorSliders();
    setupTimers();

    ui->resetButton->setDisabled(true);
}

// Destructor to remove pointers for ui and gameboard
PathWindow::~PathWindow()
{
    delete ui;
    delete board_;
}

// Rest of the methods remain unchanged...
