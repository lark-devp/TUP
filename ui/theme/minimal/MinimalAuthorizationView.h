#pragma once

#include "ui/interfaces/IAuthorizationView.h" // Убедитесь, что путь к вашему интерфейсу верный

// Предварительные объявления классов Qt
class QLineEdit;
class QPushButton;
class QLabel;
class QWidget;

/**
 * @brief Минималистичная конкретная реализация интерфейса окна авторизации.
 * Создает простой, но стильный UI с помощью кода, без использования .ui файлов.
 * Логика разделена на создание UI (setupUi) и соединение сигналов (setupConnections).
 */
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
    void clearForm() override;

private:
    /**
     * @brief Создает и настраивает все UI-элементы окна.
     */
    void setupUi();

    /**
     * @brief Соединяет сигналы от UI-элементов со слотами этого класса.
     */
    void setupConnections();

    // --- Указатели на UI-элементы ---
    QLabel* m_titleLabel;
    QLineEdit* m_usernameLineEdit;
    QLineEdit* m_passwordLineEdit;
    QPushButton* m_loginButton;
    QLabel* m_errorLabel;

    // Главный виджет-контейнер для стилизации и компоновки
    QWidget* m_mainContainer;
};
