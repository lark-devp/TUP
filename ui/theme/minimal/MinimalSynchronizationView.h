#pragma once

#include "ui/interfaces/ISynchronizationView.h"

class QLineEdit;
class QPushButton;
class QTextEdit;
class QProgressBar;
class QLabel;

class MinimalSynchronizationView : public ISynchronizationView
{
    Q_OBJECT

public:
    explicit MinimalSynchronizationView(QWidget *parent = nullptr);
    ~MinimalSynchronizationView() override = default;

    // --- Реализация методов интерфейса ---
    QWidget* getWidget() override;
    void updateStatus(const QString& statusMessage) override;
    void logMessage(const QString& message) override;
    void setProgress(int percentage) override;
    void setCloseButtonEnabled(bool enabled) override;

private slots:
    void onConnectClicked();

private:
    QLineEdit* m_emailEdit;
    QLineEdit* m_passwordEdit;
    QPushButton* m_connectButton;
    QPushButton* m_closeButton;
    QTextEdit* m_logView;
    QProgressBar* m_progressBar;
    QLabel* m_statusLabel;
};
