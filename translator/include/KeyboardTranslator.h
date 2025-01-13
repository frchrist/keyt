#ifndef KEYBOARDTRANSLATOR_H
#define KEYBOARDTRANSLATOR_H

#include <QObject>
#include <QMap>
#include <QString>
#include <QLineEdit>

class KeyboardTranslator : public QObject {
    Q_OBJECT

public:
    explicit KeyboardTranslator(QObject* parent = nullptr);

    // Installe le traducteur sur un QLineEdit
    void installOn(QLineEdit* lineEdit);

    // Traduit une chaîne complète (utile pour les tests)
    QString translateString(const QString& input) const;

    // Traduit un seul caractère
    QChar translateChar(const QChar& input) const;

protected:
    // Gère les événements du QLineEdit
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    // Initialise la table de correspondance AZERTY -> QWERTY
    void initializeTranslationMap();

    // Table de correspondance des caractères
    QMap<QChar, QChar> translationMap;

    // Référence vers le QLineEdit actuel
    QLineEdit* currentLineEdit;
};

#endif // KEYBOARDTRANSLATOR_H
