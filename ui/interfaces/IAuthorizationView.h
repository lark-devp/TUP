#pragma once

#include "IView.h"
#include <QObject>
#include <QString>

/**
 * @brief Интерфейс для окна авторизации пользователя.
 * Определяет контракт для взаимодействия с логикой приложения,
 * не завися от конкретной визуальной реализации.
 */
class IAuthorizationView : public IView
{
    Q_OBJECT

public:
    // Перечисление для управления состояниями окна
    enum class State {
        Login,
        Register,
    };

    explicit IAuthorizationView(QWidget * parent = nullptr) : IView(parent) {}
    ~IAuthorizationView() override = default;

    // --- Методы для управления видом извне ---

    virtual void showLoading(bool isLoading) = 0;
    virtual void showError(const QString& message) = 0;
    virtual void showInfo(const QString& message) = 0; // Для некритичных сообщений
    virtual void clearForm() = 0;

    /**
     * @brief Переключает вид в одно из состояний (вход, регистрация и т.д.).
     * @param state Новое состояние вида.
     */
    virtual void switchState(State state) = 0;


signals:
    // --- Сигналы о действиях пользователя ---

    /**
     * @brief Испускается, когда пользователь нажимает кнопку "Войти".
     * @param username Введенное имя пользователя.
     * @param password Введенный пароль.
     */
    void loginRequested(const QString& username, const QString& password);

    /**
     * @brief Испускается, когда пользователь отправляет форму регистрации.
     * @param username Введенное имя.
     * @param email Введенная почта.
     * @param password Введенный пароль.
     */
    void registrationSubmitted(const QString& username, const QString& email, const QString& password);


    /**
     * @brief Испускается при нажатии на ссылку/кнопку для перехода на экран входа.
     */
    void backToLoginRequested();

};
