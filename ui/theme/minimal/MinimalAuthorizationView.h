#pragma once

#include "ui/interfaces/IAuthorizationView.h"


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


    QWidget* getWidget() override;


    void showLoading(bool isLoading) override;
    void showError(const QString& message) override;
    void showInfo(const QString& message) override;
    void clearForm() override;
    void switchState(State state) override;

private:
    void setupUi();
    void setupConnections();



    QLabel* m_titleLabel;
    QLabel* m_errorLabel;
    QLabel* m_infoLabel;
    QWidget* m_mainContainer;
    QPushButton* m_mainButton;

    QLineEdit* m_usernameLineEdit;
    QLineEdit* m_passwordLineEdit;
    QLineEdit* m_confirmPasswordLineEdit;

    QWidget* m_linksWidget;
    QPushButton* m_registerLink;
    QPushButton* m_backToLoginLink;


    State m_currentState = State::Login;
};
