#include <QtTest>
#include <QLineEdit>
#include "KeyboardTranslator.h"

class TestKeyboardEvents : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testLineEditIntegration();
    void testMultipleLineEdits();
    void testInstallUninstall();
    void testEventPropagation();

private:
    QLineEdit* lineEdit;
    KeyboardTranslator* translator;
};

void TestKeyboardEvents::init()
{
    lineEdit = new QLineEdit();
    translator = new KeyboardTranslator();
}

void TestKeyboardEvents::cleanup()
{
    delete lineEdit;
    delete translator;
}

void TestKeyboardEvents::testLineEditIntegration()
{
    translator->installOn(lineEdit);
    
    // Test simple input
    QTest::keyClicks(lineEdit, "&é\"'(-è_çà");
    QCOMPARE(lineEdit->text(), QString("1234567890"));
    
    // Clear and test complex input
    lineEdit->clear();
    QTest::keyClicks(lineEdit, "azerty&é\"");
    QCOMPARE(lineEdit->text(), QString("qwerty123"));
}

void TestKeyboardEvents::testMultipleLineEdits()
{
    QLineEdit* lineEdit2 = new QLineEdit();
    
    // Install on first LineEdit
    translator->installOn(lineEdit);
    QTest::keyClicks(lineEdit, "&é\"");
    QCOMPARE(lineEdit->text(), QString("123"));
    
    // Install on second LineEdit
    translator->installOn(lineEdit2);
    QTest::keyClicks(lineEdit2, "&é\"");
    QCOMPARE(lineEdit2->text(), QString("123"));
    
    // First LineEdit should no longer translate
    QTest::keyClicks(lineEdit, "&é\"");
    QCOMPARE(lineEdit->text(), QString("123&é\""));
    
    delete lineEdit2;
}

void TestKeyboardEvents::testInstallUninstall()
{
    // Test installation
    translator->installOn(lineEdit);
    QTest::keyClicks(lineEdit, "&é\"");
    QCOMPARE(lineEdit->text(), QString("123"));
    
    // Test uninstallation
    translator->installOn(nullptr);
    lineEdit->clear();
    QTest::keyClicks(lineEdit, "&é\"");
    QCOMPARE(lineEdit->text(), QString("&é\""));
}

void TestKeyboardEvents::testEventPropagation()
{
    translator->installOn(lineEdit);
    
    // Test untranslated keys
    QTest::keyClicks(lineEdit, "hello");
    QCOMPARE(lineEdit->text(), QString("hello"));
    
    // Test mixed content
    lineEdit->clear();
    QTest::keyClicks(lineEdit, "hello&é\"");
    QCOMPARE(lineEdit->text(), QString("hello123"));
}

QTEST_MAIN(TestKeyboardEvents)
#include "tst_keyboard_events.moc"
