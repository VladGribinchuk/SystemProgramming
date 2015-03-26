#ifndef QTE_H
#define QTE_H

#include <QtGui>

class QTE : public QMainWindow
{
    Q_OBJECT

public:
    QTE();
    void initQTE();

private slots:
    // Processing of menu item
    void createFile();
    void openFile();
    void saveFile();
    void saveAsFile();

private:
    QWidget     *pwgtCentralArea;
    QTextEdit   *ptxtEdit;
    QMenu       *pMenu;

    QAction     *createAction;
    QAction     *openAction;
    QAction     *saveAction;
    QAction     *quitAction;
    QAction     *copyAction;
    QAction     *pasteAction;
    QAction     *cutAction;
    QAction     *undoAction;
    QAction     *redoAction;

    QPushButton *pButtonSave;
    QPushButton *pButtonOpen;
    QPushButton *pButtonClear;
    QLabel      *pLabel;
    QLabel      *pLabelWorkFile;
    QVBoxLayout *pvbxLayout;
    QHBoxLayout *phbxLayout;
    QGridLayout *pgrdLayout;

    // current file path
    QString     workFile;

};

#endif // QTE_H
