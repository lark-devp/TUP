#pragma once

#include "ui/interfaces/ISynchronizationView.h" // Убедитесь, что путь к вашему интерфейсу верный

// Предварительные объявления классов Qt для минимизации зависимостей в заголовке
class QLabel;
class QTextEdit;
class QProgressBar;
class QPushButton;

/**
 * @brief Минималистичная реализация окна процесса синхронизации.
 *
 * Отображает статус, лог, прогресс и кнопку для закрытия.
 */
class MinimalSynchronizationView : public ISynchronizationView
{
    Q_OBJECT

public:
    explicit MinimalSynchronizationView(QWidget *parent = nullptr);
    ~MinimalSynchronizationView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСОВ ---
    // Из IView
    QWidget* getWidget() override;

    // Из ISynchronizationView
    void updateStatus(const QString& statusMessage) override;
    void logMessage(const QString& message) override;
    void setProgress(int percentage) override;
    void setCloseButtonEnabled(bool enabled) override;

private:
    // Указатели на UI-элементы
    QLabel* m_titleLabel;
    QLabel* m_statusLabel;
    QTextEdit* m_logEdit;
    QProgressBar* m_progressBar;
    QPushButton* m_closeButton;
};
