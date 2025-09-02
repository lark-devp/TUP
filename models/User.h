#ifndef USER_H
#define USER_H
#include <QString>

class User {
private:
    int userId;
    QString username;
    QString email;
    QString tweekToken;

public:
    User() = default;
    User(int userId, const QString &username,
         const QString &email, const QString &token);

    int getUserId() const;
    void setUserId(int id);

    QString getUsername() const;
    void setUsername(const QString &name);

    QString getEmail() const;
    void setEmail(const QString &mail);

    QString getTweekToken() const;
    void setTweekToken(const QString &token);
};

#endif // USER_H
