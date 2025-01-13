#include "KeyboardTranslator.h"
#include <QKeyEvent>

KeyboardTranslator::KeyboardTranslator(QObject* parent)
    : QObject(parent)
    , currentLineEdit(nullptr)
{
    initializeTranslationMap();
}

void KeyboardTranslator::installOn(QLineEdit* lineEdit)
{
    if (currentLineEdit) {
        currentLineEdit->removeEventFilter(this);
    }

    currentLineEdit = lineEdit;
    if (currentLineEdit) {
        currentLineEdit->installEventFilter(this);
    }
}

void KeyboardTranslator::initializeTranslationMap()
{
    // Mapping des chiffres AZERTY -> QWERTY
    translationMap['&'] = '1';
    translationMap[u'é'] = '2';
    translationMap['"'] = '3';
    translationMap['\''] = '4';
    translationMap['('] = '5';
    translationMap['-'] = '6';
    translationMap[u'è'] = '7';
    translationMap['_'] = '8';
    translationMap[u'ç'] = '9';
    translationMap[u'à'] = '0';

    // Mapping des lettres AZERTY -> QWERTY
    translationMap['a'] = 'q';
    translationMap['z'] = 'w';
    translationMap['q'] = 'a';
    translationMap['w'] = 'z';

    // Mapping des majuscules
    translationMap['A'] = 'Q';
    translationMap['Z'] = 'W';
    translationMap['Q'] = 'A';
    translationMap['W'] = 'Z';
}

QString KeyboardTranslator::translateString(const QString& input) const
{
    QString result;
    for (const QChar& c : input) {
        result.append(translateChar(c));
    }
    return result;
}

QChar KeyboardTranslator::translateChar(const QChar& input) const
{
    return translationMap.contains(input) ? translationMap[input] : input;
}

bool KeyboardTranslator::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == currentLineEdit && event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        QString text = keyEvent->text();

        if (!text.isEmpty()) {
            QString translated = translateString(text);
            if (translated != text) {
                // Empêche l'événement original
                currentLineEdit->insert(translated);
                return true;
            }
        }
    }

    return QObject::eventFilter(obj, event);
}
