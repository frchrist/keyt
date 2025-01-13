#include <QtTest>
#include "KeyboardTranslator.h"

class TestKeyboardComplex : public QObject
{
    Q_OBJECT

private slots:
    void testMixedContent_data();
    void testMixedContent();
    void testLetterTranslation_data();
    void testLetterTranslation();
    void testCasePreservation();
    void testEmptyAndSpecialCases();
};

void TestKeyboardComplex::testMixedContent_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("expected");

    QTest::newRow("mix_1") << QString("a&z_é") << QString("q1w82");
    QTest::newRow("mix_2") << QString("qwerty&é\"") << QString("azerty123");
    QTest::newRow("mix_3") << QString("A&Z_É") << QString("Q1W82");
}

void TestKeyboardComplex::testMixedContent()
{
    QFETCH(QString, input);
    QFETCH(QString, expected);

    KeyboardTranslator translator;
    QCOMPARE(translator.translateString(input), expected);
}

void TestKeyboardComplex::testLetterTranslation_data()
{
    QTest::addColumn<QString>("input");
    QTest::addColumn<QString>("expected");

    QTest::newRow("qwerty") << QString("qwertyuiopasd") << QString("azertyuiopqsd");
    QTest::newRow("azerty") << QString("azertyuiopqsd") << QString("qwertyuiopazd");
}

void TestKeyboardComplex::testLetterTranslation()
{
    QFETCH(QString, input);
    QFETCH(QString, expected);

    KeyboardTranslator translator;
    QCOMPARE(translator.translateString(input), expected);
}

void TestKeyboardComplex::testCasePreservation()
{
    KeyboardTranslator translator;
    
    // Test upper case
    QCOMPARE(translator.translateString("AZERTY"), QString("QWERTY"));
    QCOMPARE(translator.translateString("QWERTY"), QString("AZERTY"));
    
    // Test mixed case
    QCOMPARE(translator.translateString("AzErTy"), QString("QwErTy"));
    QCOMPARE(translator.translateString("QwErTy"), QString("AzErTy"));
}

void TestKeyboardComplex::testEmptyAndSpecialCases()
{
    KeyboardTranslator translator;
    
    // Test empty string
    QCOMPARE(translator.translateString(""), QString(""));
    
    // Test spaces
    QCOMPARE(translator.translateString("a z"), QString("q w"));
    
    // Test special characters mixed with translations
    QCOMPARE(translator.translateString("a&z!"), QString("q1w!"));
}

QTEST_MAIN(TestKeyboardComplex)
#include "tst_keyboard_complex.moc"
