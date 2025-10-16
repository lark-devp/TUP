#pragma once

#include "ui/interfaces/IAuthorizationView.h"

// Предварительные объявления классов Qt
class QLineEdit;
class QPushButton;
class QLabel;
class QWidget;
class QStackedWidget;

class MinimalAuthorizationView : public IAuthorizationView
{
    Q_OBJECT

public:
    explicit MinimalAuthorizationView(QWidget *parent = nullptr);
    ~MinimalAuthorizationView() override = default;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСА IView ---
    QWidget* getWidget() override;

    // --- РЕАЛИЗАЦИЯ МЕТОДОВ ИНТЕРФЕЙСА IAuthorizationView ---
    void showLoading(bool isLoading) override;
    void showError(const QString& message) override;
    void showInfo(const QString& message) override;
    void clearForm() override;
    void switchState(State state) override;

private:
    void setupUi();
    void setupConnections();

    // --- Указатели на UI-элементы ---
    // Общие
    QLabel* m_titleLabel;
    QLabel* m_errorLabel;
    QLabel* m_infoLabel;
    QWidget* m_mainContainer;
    QPushButton* m_mainButton; // Основная кнопка (Войти / Регистрация / Отправить)

    // Поля ввода
    QLineEdit* m_usernameLineEdit;
    QLineEdit* m_passwordLineEdit;
    QLineEdit* m_emailLineEdit;
    QLineEdit* m_confirmPasswordLineEdit;

    // Кнопки-ссылки
    QWidget* m_linksWidget; // Контейнер для ссылок
    QPushButton* m_registerLink;
    QPushButton* m_forgotPasswordLink;
    QPushButton* m_backToLoginLink;


    State m_currentState = State::Login;
};
