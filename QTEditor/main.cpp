#include <QtGui>
#include "qte.h"

int main(int argv, char** args )
{
    QApplication app(argv, args);

    QTE TxtEditor;
    TxtEditor.show();

    return app.exec();
}
