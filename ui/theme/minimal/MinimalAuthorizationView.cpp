#include "MinimalAuthorizationView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QGraphicsDropShadowEffect>

// Вспомогательная функция для создания текстовых ссылок
QLabel* createLink(const QString& text) {
    auto label = new QLabel(text);
    label->setStyleSheet("color: #4a90e2; text-decoration: none; font-size: 12px;");
    label->setCursor(Qt::PointingHandCursor);
    return label;
}


MinimalAuthorizationView::MinimalAuthorizationView(QWidget *parent)
    : IAuthorizationView(parent)
{
    setupUi();
    setupConnections();
    switchState(State::Login); // Устанавливаем начальное состояние
}

void MinimalAuthorizationView::setupUi()
{
    // --- 1. Определение стилей ---
    this->setStyleSheet("background-color: #eef4ff;");
    const QString titleStyle = "font-size: 22px; font-weight: bold; color: #333; padding-bottom: 10px;";
    const QString lineEditStyle = R"(
        QLineEdit { border: 1px solid #dcdcdc; border-radius: 8px; padding: 12px; font-size: 14px; background-color: #ffffff; }
        QLineEdit:focus { border: 1px solid #4a90e2; }
    )";
    const QString linkButtonStyle = R"(
        QPushButton {
            color: #4a90e2;
            text-decoration: none;
            font-size: 12px;
            border: none;
            padding: 0;
            background: transparent; /* Делаем фон прозрачным */
        }
        QPushButton:hover {
            text-decoration: underline;
        }
    )";
    const QString errorLabelStyle = "color: #d9534f; font-size: 12px; font-weight: bold; padding-left: 5px;";
    const QString infoLabelStyle = "color: #28a745; font-size: 12px; font-weight: bold; padding-left: 5px;";


    // --- 2. Создание виджетов ---
    m_titleLabel = new QLabel("Вход в систему");
    m_usernameLineEdit = new QLineEdit();
    m_passwordLineEdit = new QLineEdit();
    m_emailLineEdit = new QLineEdit();
    m_confirmPasswordLineEdit = new QLineEdit();
    m_mainButton = new QPushButton("Войти");
    m_errorLabel = new QLabel("");
    m_infoLabel = new QLabel("");

    // Ссылки
    // Кнопка "Регистрация"
    m_registerLink = new QPushButton("Регистрация");
    m_registerLink->setFlat(true); // Убирает рельеф кнопки, делая ее плоской
    m_registerLink->setCursor(Qt::PointingHandCursor);
    m_registerLink->setStyleSheet(linkButtonStyle);

    // Кнопка "Забыли пароль?"
    m_forgotPasswordLink = new QPushButton("Забыли пароль?");
    m_forgotPasswordLink->setFlat(true);
    m_forgotPasswordLink->setCursor(Qt::PointingHandCursor);
    m_forgotPasswordLink->setStyleSheet(linkButtonStyle);

    // Кнопка "Назад ко входу"
    m_backToLoginLink = new QPushButton("Назад ко входу");
    m_backToLoginLink->setFlat(true);
    m_backToLoginLink->setCursor(Qt::PointingHandCursor);
    m_backToLoginLink->setStyleSheet(linkButtonStyle);
    // Настройка виджетов
    m_usernameLineEdit->setPlaceholderText("Имя пользователя");
    m_passwordLineEdit->setPlaceholderText("Пароль");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_emailLineEdit->setPlaceholderText("Email");
    m_confirmPasswordLineEdit->setPlaceholderText("Подтвердите пароль");
    m_confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);

    m_errorLabel->setVisible(false);
    m_infoLabel->setVisible(false);

    // --- 3. Применение стилей и эффектов ---
    m_titleLabel->setStyleSheet(titleStyle);
    m_usernameLineEdit->setStyleSheet(lineEditStyle);
    m_passwordLineEdit->setStyleSheet(lineEditStyle);
    m_emailLineEdit->setStyleSheet(lineEditStyle);
    m_confirmPasswordLineEdit->setStyleSheet(lineEditStyle);
    m_mainButton->setStyleSheet(linkButtonStyle);
    m_errorLabel->setStyleSheet(errorLabelStyle);
    m_infoLabel->setStyleSheet(infoLabelStyle);

    m_mainButton->setCursor(Qt::PointingHandCursor);
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 70));
    m_mainButton->setGraphicsEffect(shadow);

    // --- 4. Компоновка ---
    auto mainLayout = new QVBoxLayout(this);
    auto formLayout = new QVBoxLayout();
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(30, 30, 30, 30);

    formLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    formLayout->addSpacing(10);
    formLayout->addWidget(m_usernameLineEdit);
    formLayout->addWidget(m_emailLineEdit); // Добавляем все поля, будем управлять видимостью
    formLayout->addWidget(m_passwordLineEdit);
    formLayout->addWidget(m_confirmPasswordLineEdit);
    formLayout->addWidget(m_errorLabel);
    formLayout->addWidget(m_infoLabel);
    formLayout->addSpacing(5);
    formLayout->addWidget(m_mainButton);
    formLayout->addSpacing(10);

    // Компоновка ссылок
    auto linksLayout = new QHBoxLayout();
    linksLayout->addWidget(m_registerLink);
    linksLayout->addStretch();
    linksLayout->addWidget(m_forgotPasswordLink);

    m_linksWidget = new QWidget();
    m_linksWidget->setLayout(linksLayout);

    formLayout->addWidget(m_linksWidget);
    formLayout->addWidget(m_backToLoginLink, 0, Qt::AlignCenter);

    m_mainContainer = new QWidget();
    m_mainContainer->setLayout(formLayout);
    m_mainContainer->setStyleSheet("background-color: #f4f7fa; border-radius: 15px;");
    m_mainContainer->setMaximumWidth(450);

    mainLayout->addStretch();
    mainLayout->addWidget(m_mainContainer, 0, Qt::AlignHCenter);
    mainLayout->addStretch();
    this->setLayout(mainLayout);
}

void MinimalAuthorizationView::setupConnections()
{
    // Главная кнопка действует в зависимости от текущего состояния
    connect(m_mainButton, &QPushButton::clicked, this, [this](){
        clearForm(); // Очищаем сообщения
        switch (m_currentState) {
        case State::Login:
            emit loginRequested(m_usernameLineEdit->text(), m_passwordLineEdit->text());
            break;
        case State::Register:
            if (m_passwordLineEdit->text() != m_confirmPasswordLineEdit->text()) {
                showError("Пароли не совпадают!");
                return;
            }
            emit registrationSubmitted(m_usernameLineEdit->text(), m_emailLineEdit->text(), m_passwordLineEdit->text());
            break;
        case State::PasswordRecovery:
            emit recoverySubmitted(m_emailLineEdit->text());
            break;
        }
    });

    // Ссылки
    connect(m_registerLink, &QPushButton::clicked, this, [this](){ switchState(State::Register); });
    connect(m_forgotPasswordLink, &QPushButton::clicked, this, [this](){ switchState(State::PasswordRecovery); });
    connect(m_backToLoginLink, &QPushButton::clicked, this, [this](){ emit backToLoginRequested(); });

    // Удобство для пользователя: скрываем ошибку, как только он начинает вводить новые данные
    connect(m_usernameLineEdit, &QLineEdit::textChanged, this, &MinimalAuthorizationView::clearForm);
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, &MinimalAuthorizationView::clearForm);
    connect(m_emailLineEdit, &QLineEdit::textChanged, this, &MinimalAuthorizationView::clearForm);
    connect(m_confirmPasswordLineEdit, &QLineEdit::textChanged, this, &MinimalAuthorizationView::clearForm);
}

void MinimalAuthorizationView::switchState(State state)
{
    m_currentState = state;
    clearForm();

    if (state == State::Login) {
        m_titleLabel->setText("Вход в систему");
        m_mainButton->setText("Войти");
        m_usernameLineEdit->setVisible(true);
        m_passwordLineEdit->setVisible(true);
        m_emailLineEdit->setVisible(false);
        m_confirmPasswordLineEdit->setVisible(false);
        m_linksWidget->setVisible(true);
        m_backToLoginLink->setVisible(false);
        m_usernameLineEdit->setFocus();
    } else if (state == State::Register) {
        m_titleLabel->setText("Регистрация");
        m_mainButton->setText("Зарегистрироваться");
        m_usernameLineEdit->setVisible(true);
        m_passwordLineEdit->setVisible(true);
        m_emailLineEdit->setVisible(true);
        m_confirmPasswordLineEdit->setVisible(true);
        m_linksWidget->setVisible(false);
        m_backToLoginLink->setVisible(true);
        m_usernameLineEdit->setFocus();
    } else if (state == State::PasswordRecovery) {
        m_titleLabel->setText("Восстановление пароля");
        m_mainButton->setText("Отправить ссылку");
        m_usernameLineEdit->setVisible(false);
        m_passwordLineEdit->setVisible(false);
        m_emailLineEdit->setVisible(true);
        m_confirmPasswordLineEdit->setVisible(false);
        m_linksWidget->setVisible(false);
        m_backToLoginLink->setVisible(true);
        m_emailLineEdit->setFocus();
    }
}

QWidget* MinimalAuthorizationView::getWidget() { return this; }

void MinimalAuthorizationView::showLoading(bool isLoading)
{
    m_usernameLineEdit->setEnabled(!isLoading);
    m_passwordLineEdit->setEnabled(!isLoading);
    m_emailLineEdit->setEnabled(!isLoading);
    m_confirmPasswordLineEdit->setEnabled(!isLoading);
    m_mainButton->setEnabled(!isLoading);
    m_mainButton->setText(isLoading ? "Обработка..." : m_mainButton->text());
}

void MinimalAuthorizationView::showError(const QString& message)
{
    m_infoLabel->setVisible(false);
    m_errorLabel->setText(message);
    m_errorLabel->setVisible(!message.isEmpty());
}

void MinimalAuthorizationView::showInfo(const QString& message)
{
    m_errorLabel->setVisible(false);
    m_infoLabel->setText(message);
    m_infoLabel->setVisible(!message.isEmpty());
}

void MinimalAuthorizationView::clearForm()
{
    // Очищаем только сообщения, а не поля ввода
    showError("");
    showInfo("");
}
