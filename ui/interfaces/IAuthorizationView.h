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
    explicit IAuthorizationView(QWidget * parent = nullptr) : IView(parent) {}
    ~IAuthorizationView() override = default;

    // --- Методы для управления видом извне (команды от "Режиссера") ---

    /**
     * @brief Отображает состояние загрузки.
     * Должно блокировать UI (например, делать кнопку "Войти" неактивной)
     * и, возможно, показывать анимацию.
     * @param isLoading true, если процесс входа выполняется, иначе false.
     */
    virtual void showLoading(bool isLoading) = 0;

    /**
     * @brief Показывает сообщение об ошибке аутентификации.
     * @param message Текст ошибки (например, "Неверный логин или пароль").
     */
    virtual void showError(const QString& message) = 0;

    /**
     * @brief Очищает поля ввода и сообщение об ошибке.
     */
    virtual void clearForm() = 0;

signals:
    // --- Сигналы о действиях пользователя (реплики для "Режиссера") ---

    /**
     * @brief Испускается, когда пользователь нажимает кнопку "Войти".
     * @param username Введенное имя пользователя.
     * @param password Введенный пароль.
     */
    void loginRequested(const QString& username, const QString& password);

    /**
     * @brief (Опционально) Испускается при нажатии на ссылку/кнопку "Регистрация".
     */
    void registrationRequested();

    /**
     * @brief (Опционально) Испускается при нажатии на ссылку/кнопку "Забыли пароль?".
     */
    void passwordRecoveryRequested();
};
