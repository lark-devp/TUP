#pragma once

#include "ui/interfaces/ISynchronizationView.h"
#include <QMap>
#include <QVBoxLayout>

class QLineEdit;
class QPushButton;
class QTextEdit;
class QProgressBar;
class QLabel;
class QWidget;
class QComboBox;
class QListWidget;

class MinimalSynchronizationView : public ISynchronizationView
{
    Q_OBJECT

public:
    explicit MinimalSynchronizationView(QWidget *parent = nullptr);
    ~MinimalSynchronizationView() override = default;

    // --- Реализация методов интерфейса ---
    QWidget* getWidget() override;
    void showState(ViewState state) override;
    void updateStatus(const QString& statusMessage) override;
    void logMessage(const QString& message) override;
    void setProgress(int percentage) override;
    void displayCalendars(const QVector<TweekCalendar>& calendars) override;
    void displayTasks(const QVector<TweekTask>& tasks) override;
    void setControlsEnabled(bool enabled) override;

protected:
    bool eventFilter(QObject* watched, QEvent* event) override;

private slots:
    void onConnectClicked();
    void onGetTasksClicked();
    void onConfirmClicked();


private:
    void setupLoginUi();
    void setupSyncUi();

    // Общие виджеты
    QWidget* m_centralWidget;
    QVBoxLayout* m_mainLayout;
    QLabel* m_statusLabel;
    QProgressBar* m_progressBar;
    QTextEdit* m_logView;
    QPushButton* m_closeButton;

    // Виджеты для состояния Login
    QWidget* m_loginWidget = nullptr;
    QLineEdit* m_emailEdit;
    QLineEdit* m_passwordEdit;
    QPushButton* m_connectButton;
    QLabel* m_loginTitle;
    QPushButton* m_closeLoginButton;

    // Виджеты для состояния Sync
    QWidget* m_syncWidget = nullptr;
    QPushButton* m_disconnectButton;
    QComboBox* m_calendarCombo;
    QPushButton* m_getTasksButton;
    QListWidget* m_tasksList;
    QPushButton* m_confirmButton;
    QLabel* m_syncTitle;

    // Для хранения полного объекта задачи
    QMap<QString, TweekTask> m_taskMap;
};
