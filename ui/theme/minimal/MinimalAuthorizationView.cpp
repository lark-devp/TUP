#include "MinimalAuthorizationView.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QFont>
#include <QGraphicsDropShadowEffect>

MinimalAuthorizationView::MinimalAuthorizationView(QWidget *parent)
    : IAuthorizationView(parent)
{
    setupUi();
    setupConnections();
}

void MinimalAuthorizationView::setupUi()
{
    // --- 1. Определение стилей ---

    // Стиль для фона всего окна
    this->setStyleSheet("background-color: #eef4ff;");

    const QString titleStyle = R"(
        font-size: 22px;
        font-weight: bold;
        color: #333;
        padding-bottom: 10px;
    )";

    const QString lineEditStyle = R"(
        QLineEdit {
            border: 1px solid #dcdcdc;
            border-radius: 8px;
            padding: 12px;
            font-size: 14px;
            background-color: #ffffff;
        }
        QLineEdit:focus {
            border: 1px solid #4a90e2;
        }
    )";

    const QString buttonStyle = R"(
        QPushButton {
           background-color: #4a90e2;
           color: white;
           border-radius: 8px;
           font-size: 14px;
           font-weight: bold;
           padding: 12px;
           border: none;
        }
        QPushButton:hover {
           background-color: #5aa1f2;
        }
        QPushButton:pressed {
           background-color: #3a80d2;
        }
        QPushButton:disabled {
           background-color: #dcdcdc;
           color: #a0a0a0;
        }
    )";

    const QString errorLabelStyle = R"(
        color: #d9534f; /* Красный цвет для ошибки */
        font-size: 12px;
        font-weight: bold;
        padding-left: 5px;
    )";


    // --- 2. Создание виджетов ---
    m_titleLabel = new QLabel("Вход в систему");
    m_usernameLineEdit = new QLineEdit();
    m_passwordLineEdit = new QLineEdit();
    m_loginButton = new QPushButton("Войти");
    m_errorLabel = new QLabel(""); // Изначально пустой

    // Настройка виджетов
    m_usernameLineEdit->setPlaceholderText("Имя пользователя");
    m_passwordLineEdit->setPlaceholderText("Пароль");
    m_passwordLineEdit->setEchoMode(QLineEdit::Password);
    m_errorLabel->setVisible(false); // Скрываем метку ошибки по умолчанию


    // --- 3. Применение стилей и эффектов ---
    m_titleLabel->setStyleSheet(titleStyle);
    m_usernameLineEdit->setStyleSheet(lineEditStyle);
    m_passwordLineEdit->setStyleSheet(lineEditStyle);
    m_loginButton->setStyleSheet(buttonStyle);
    m_errorLabel->setStyleSheet(errorLabelStyle);
    m_errorLabel->setAlignment(Qt::AlignCenter);

    m_loginButton->setCursor(Qt::PointingHandCursor);

    // Добавляем тень к кнопке для придания "глубины"
    auto shadow = new QGraphicsDropShadowEffect(this);
    shadow->setBlurRadius(25);
    shadow->setOffset(0, 5);
    shadow->setColor(QColor(0, 0, 0, 70));
    m_loginButton->setGraphicsEffect(shadow);


    // --- 4. Компоновка ---
    auto mainLayout = new QVBoxLayout(this); // Главный компоновщик для всего окна
    auto formLayout = new QVBoxLayout();    // Компоновщик для элементов формы
    formLayout->setSpacing(15);
    formLayout->setContentsMargins(30, 30, 30, 30);

    formLayout->addWidget(m_titleLabel, 0, Qt::AlignHCenter);
    formLayout->addSpacing(10);
    formLayout->addWidget(m_usernameLineEdit);
    formLayout->addWidget(m_passwordLineEdit);
    formLayout->addWidget(m_errorLabel);
    formLayout->addSpacing(5);
    formLayout->addWidget(m_loginButton);

    // Оборачиваем форму в контейнер для стилизации и центрирования
    m_mainContainer = new QWidget();
    m_mainContainer->setLayout(formLayout);
    m_mainContainer->setStyleSheet("background-color: #f4f7fa; border-radius: 15px;");
    m_mainContainer->setMaximumWidth(450);

    // Центрируем контейнер формы на окне
    mainLayout->addStretch();
    mainLayout->addWidget(m_mainContainer, 0, Qt::AlignHCenter);
    mainLayout->addStretch();

    this->setLayout(mainLayout);
}

void MinimalAuthorizationView::setupConnections()
{
    // Когда пользователь нажимает на кнопку, мы испускаем сигнал интерфейса
    connect(m_loginButton, &QPushButton::clicked, this, [this](){
        // Сначала убираем старую ошибку, чтобы не смущать пользователя
        showError("");
        // ИСПУСКАЕМ СИГНАЛ для "Режиссера"
        emit loginRequested(m_usernameLineEdit->text(), m_passwordLineEdit->text());
    });

    // Удобство для пользователя: скрываем ошибку, как только он начинает вводить новые данные
    connect(m_usernameLineEdit, &QLineEdit::textChanged, this, [this](){ showError(""); });
    connect(m_passwordLineEdit, &QLineEdit::textChanged, this, [this](){ showError(""); });
}

// --- Реализация методов интерфейсов (остается без изменений) ---

QWidget* MinimalAuthorizationView::getWidget()
{
    return this;
}

void MinimalAuthorizationView::showLoading(bool isLoading)
{
    m_usernameLineEdit->setEnabled(!isLoading);
    m_passwordLineEdit->setEnabled(!isLoading);
    m_loginButton->setEnabled(!isLoading);
    m_loginButton->setText(isLoading ? "Вход..." : "Войти");
}

void MinimalAuthorizationView::showError(const QString& message)
{
    m_errorLabel->setText(message);
    m_errorLabel->setVisible(!message.isEmpty());
}

void MinimalAuthorizationView::clearForm()
{
    m_usernameLineEdit->clear();
    m_passwordLineEdit->clear();
    m_usernameLineEdit->setFocus(); // Устанавливаем фокус на поле имени пользователя
    showError(""); // Скрываем сообщение об ошибке
}
