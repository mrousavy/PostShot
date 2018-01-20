#ifndef KEYSEQUENCE_H
#define KEYSEQUENCE_H

#include <QObject>
#include <QString>
#include <QVector>
#include <QStringList>
#include <QKeyEvent>

#include "globals.h"

class HOTKEY_EXPORT KeySequence : public QObject
{
    Q_OBJECT
public:
    explicit KeySequence(QObject *parent = 0);
    explicit KeySequence(const QString& str, QObject *parent = 0);
    void FromString(const QString& str);
    QString ToString();
    void AddKey(int key);
    void AddKey(const QString& key);
    void AddModifiers(Qt::KeyboardModifiers mod);
    void AddKey(const QKeyEvent* event);

    inline size_t Size() const
    {
        return Keys.size();
    }
    inline int operator [] (size_t n) const
    {
        if ((int)n > Keys.size())
            throw std::exception("Out of bounds");
        return Keys[n];
    }
    QVector<int> GetSimpleKeys() const;
    QVector<int> GetModifiers() const;
private:
    QVector<int> Keys;
};


#endif // KEYSEQUENCE_H
