#pragma once

#include "IView.h"
#include <QObject>
#include <QString>

/**
 * @brief Интерфейс для окна процесса синхронизации с календарем.
 */
class ISynchronizationView : public IView
{
    Q_OBJECT

public:
    ~ISynchronizationView() override = default;

    // Методы для управления видом
    virtual void updateStatus(const QString& statusMessage) = 0;
    virtual void logMessage(const QString& message) = 0;
    virtual void setProgress(int percentage) = 0;
    virtual void setCloseButtonEnabled(bool enabled) = 0;

signals:
    // Сигналы о действиях пользователя
    void closeRequested();
};
