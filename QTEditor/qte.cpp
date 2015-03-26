#include <QtGui>
#include "qte.h"

QTE::QTE()
{
    //
    // Create a text container without frame
    ptxtEdit = new QTextEdit;
    ptxtEdit->setFrameStyle(QFrame::NoFrame);

    //
    // Create a footer of QTE work area
    pLabel = new QLabel("<p>QTE(Qt Text Editor) author - Gribinchuk Vlad |"
                        " 2015, all rights recerved");
    pLabelWorkFile = new QLabel("");
    pButtonSave = new QPushButton("Save");
    connect(pButtonSave,SIGNAL(clicked()),this,SLOT(saveFile()));
    pButtonOpen = new QPushButton("Open");
    connect(pButtonOpen,SIGNAL(clicked()),this,SLOT(openFile()));
    pButtonClear = new QPushButton("Clear");
    connect(pButtonClear,SIGNAL(clicked()),ptxtEdit, SLOT(clear()));

    //
    // Create a wrapper of all work elements
    phbxLayout = new QHBoxLayout;
    phbxLayout->setMargin(5); phbxLayout->setSpacing(10);
    phbxLayout->addWidget(pButtonSave,0);
    phbxLayout->addWidget(pButtonOpen,0);
    phbxLayout->addWidget(pButtonClear,0);
    phbxLayout->addStretch(1);
    pvbxLayout = new QVBoxLayout;
    pvbxLayout->setMargin(5);
    pvbxLayout->setSpacing(10);
    pvbxLayout->addWidget(pLabelWorkFile);
    pvbxLayout->addWidget(ptxtEdit);
    pvbxLayout->addLayout(phbxLayout);
    pvbxLayout->addWidget(pLabel);

    //
    // Create main widget which contain all
    pwgtCentralArea = new QWidget;
    pwgtCentralArea->setLayout(pvbxLayout);
    setCentralWidget(pwgtCentralArea);

    //
    // Create list item for menu (as action)
    createAction = new QAction("&Create",this);
    createAction->setStatusTip("Push to create new .txt file");
    openAction = new QAction("&Open",this);
    openAction->setStatusTip("Push for open .txt file");
    saveAction = new QAction("&Save as...",this);
    saveAction->setStatusTip("Push for save current .txt file");
    quitAction = new QAction("&Quit",this);
    copyAction = new QAction("Copy",this);
    pasteAction = new QAction("Paste",this);
    cutAction = new QAction("Cut",this);
    undoAction = new QAction("Undo <-",this);
    redoAction = new QAction("Redo ->",this);
        // connect with appropriate slots
        connect(createAction, SIGNAL(triggered()), this, SLOT(createFile()));
        connect(openAction, SIGNAL(triggered()), this, SLOT(openFile()));
        connect(saveAction, SIGNAL(triggered()), this, SLOT(saveAsFile()));
        connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
        connect(copyAction, SIGNAL(triggered()), ptxtEdit, SLOT(copy()));
        connect(pasteAction, SIGNAL(triggered()), ptxtEdit, SLOT(paste()));
        connect(cutAction, SIGNAL(triggered()), ptxtEdit, SLOT(cut()));
        connect(undoAction, SIGNAL(triggered()), ptxtEdit, SLOT(undo()));
        connect(redoAction, SIGNAL(triggered()), ptxtEdit, SLOT(redo()));
    //
    // Create a menu
    pMenu = menuBar()->addMenu("&File");
    pMenu->addAction(createAction);
    pMenu->addAction(openAction);
    pMenu->addAction(saveAction);
    pMenu->addSeparator();
    pMenu->addAction(quitAction);
    pMenu = menuBar()->addMenu("&Edit");
    pMenu->addAction(copyAction);
    pMenu->addAction(pasteAction);
    pMenu->addAction(cutAction);
    pMenu->addSeparator();
    pMenu->addAction(undoAction);
    pMenu->addAction(redoAction);

    setWindowTitle("QTE");
    resize(800,500);
    statusBar()->showMessage("Ready");
}

void QTE::createFile()
{
    ptxtEdit->clear();
    workFile = "";
}

void QTE::openFile()
{
    // workFile - will be path to opened file
    workFile = QFileDialog::getOpenFileName(this,"Open file","",
                                              "Text Files (*.txt)");
    if (workFile!=""){
        QFile f(workFile);
        if(!f.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,"fatal error", "couldn\'t open file");
            return;
        }
        QTextStream in(&f);
        ptxtEdit->setText(in.readAll());
        f.close();
        // Output opened file
        pLabelWorkFile->setText(workFile);
        pLabelWorkFile->update();
    }
}


void QTE::saveFile()
{
    if(workFile!=""){
        QFile f(workFile);
        f.open(QIODevice::WriteOnly);
        QTextStream out(&f);
        out << ptxtEdit->toPlainText();
        out.flush();
        f.close();
    }
    else {
        saveAsFile();
    }

}


void QTE::saveAsFile()
{
    workFile = QFileDialog::getSaveFileName(this,"Open file","",
                                              "Text Files (*.txt)");
        if (workFile!="") {
            QFile f(workFile);
            if (!f.open(QIODevice::WriteOnly)) {
                QMessageBox::critical(this,"fatal error", "couldn\'t save file");
            }
            else {
                QTextStream out(&f);
                out << ptxtEdit->toPlainText();
                out.flush();
                f.close();
                pLabelWorkFile->setText(workFile);
                pLabelWorkFile->update();
            }
        }
}


