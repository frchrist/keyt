#include <QApplication>
#include <QLineEdit>
#include "KeyboardTranslator.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QLineEdit lineEdit;
    KeyboardTranslator translator{&lineEdit};
    translator.installOn(&lineEdit);

    lineEdit.show();
    return app.exec();
}
