#include <QtTest>
#include "KeyboardTranslator.h"
#include <QLineEdit>

class KeyboardTranslatorTests : public QObject
{
    Q_OBJECT

private slots:
    void testCharTranslation();
    void testStringTranslation();
    void testLineEditIntegration();
};

void KeyboardTranslatorTests::testCharTranslation()
{
    KeyboardTranslator translator;

    // Test des chiffres
    QCOMPARE(translator.translateChar('&'), '1');
    QCOMPARE(translator.translateChar(u'é'), '2');
    QCOMPARE(translator.translateChar('"'), '3');
    QCOMPARE(translator.translateChar('\''), '4');
    QCOMPARE(translator.translateChar('('), '5');
    QCOMPARE(translator.translateChar('-'), '6');
    QCOMPARE(translator.translateChar(u'è'), '7');
    QCOMPARE(translator.translateChar('_'), '8');
    QCOMPARE(translator.translateChar(u'ç'), '9');
    QCOMPARE(translator.translateChar(u'à'), '0');

    // Test des lettres
    QCOMPARE(translator.translateChar('a'), 'q');
    QCOMPARE(translator.translateChar('z'), 'w');
    QCOMPARE(translator.translateChar('q'), 'a');
    QCOMPARE(translator.translateChar('w'), 'z');

    // Test des majuscules
    QCOMPARE(translator.translateChar('A'), 'Q');
    QCOMPARE(translator.translateChar('Z'), 'W');
    QCOMPARE(translator.translateChar('Q'), 'A');
    QCOMPARE(translator.translateChar('W'), 'Z');
}

void KeyboardTranslatorTests::testStringTranslation()
{
    KeyboardTranslator translator;

    // Test des séquences de chiffres
    QCOMPARE(translator.translateString("-&_éààà&éç'_è"), QString("6182000129487"));
    QCOMPARE(translator.translateString("çè\"àè&é_à\"ç("), QString("6973071280395"));
    QCOMPARE(translator.translateString("'è&à_(ààé'&è("), QString("4710850024175"));
    QCOMPARE(translator.translateString("&é\"'(-è_çà"), QString("1234567890"));

    // Test des lettres inchangées
    QCOMPARE(translator.translateString("fghjkl,zxcvbn"), QString("fghjkl,zxcvbn"));

    // Test des lettres traduites
    QCOMPARE(translator.translateString("qwertyuiopasd"), QString("azertyuiopqsd"));
}

void KeyboardTranslatorTests::testLineEditIntegration()
{
    QLineEdit lineEdit;
    KeyboardTranslator translator;
    translator.installOn(&lineEdit);

    // Simule une entrée utilisateur
    QTest::keyClicks(&lineEdit, "&é\"'(-è_çà");
    QCOMPARE(lineEdit.text(), QString("1234567890"));
}

QTEST_MAIN(KeyboardTranslatorTests)
//#include "KeyboardTranslatorTests.moc"
