#include <QtTest>
#include "KeyboardTranslator.h"

class TestKeyboardSimple : public QObject
{
    Q_OBJECT

private slots:
    void testSingleCharTranslation_data();
    void testSingleCharTranslation();
    void testBasicStringTranslation_data();
    void testBasicStringTranslation();
    void testUnchangedCharacters();
};

void TestKeyboardSimple::testSingleCharTranslation_data()
{
    QTest::addColumn<QChar>("input");
    QTest::addColumn<QChar>("expected");

    QTest::newRow("number_1") << QChar('&') << QChar('1');
    QTest::newRow("number_2") << QChar(u'é') << QChar('2');
    QTest::newRow("number_3") << QChar('"') << QChar('3');
    QTest::newRow("number_4") << QChar('\'') << QChar('4');
    QTest::newRow("number_5") << QChar('(') << QChar('5');
    QTest::newRow("number_6") << QChar('-') << QChar('6');
    QTest::newRow("number_7") << QChar(u'è') << QChar('7');
    QTest::newRow("number_8") << QChar('_') << QChar('8');
    QTest::newRow("number_9") << QChar(u'ç') << QChar('9');
    QTest::newRow("number_0") << QChar(u'à') << QChar('0');
}

void TestKeyboardSimple::testSingleCharTranslation()
{
    QFETCH(QChar, input);
    QFETCH(QChar, expected);

    KeyboardTranslator translator;
    QCOMPARE(translator.translateChar(input), expected);
}

void TestKeyboardSimple::testBasicStringTranslation_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("expected");

    QTest::newRow("numbers_1") << QString("&é\"'(-è_çà") << QString("1234567890");
    QTest::newRow("numbers_2") << QString("-&_éààà&éç'_è") << QString("6182000129487");
    QTest::newRow("numbers_3") << QString("çè\"àè&é_à\"ç(") << QString("973071280395");
    QTest::newRow("numbers_4") << QString("'è&à_(ààé'&è(") << QString("4710850024175");
}

void TestKeyboardSimple::testBasicStringTranslation()
{
    QFETCH(QString, input);
    QFETCH(QString, expected);

    KeyboardTranslator translator;
    QCOMPARE(translator.translateString(input), expected);
}

void TestKeyboardSimple::testUnchangedCharacters()
{
    KeyboardTranslator translator;
    QString input = "fghjkl,;:!/.§µ*$^¨#@";
    QCOMPARE(translator.translateString(input), input);
}

QTEST_MAIN(TestKeyboardSimple)
#include "tst_keyboard_simple.moc"
