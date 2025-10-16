#ifndef TASK_H
#define TASK_H

#include <QString>

class Task {
public:
    Task(int id,
         int userId,
         const QString& name,
         const QString& color,
         const QString& description,
         const QString& createdAt,
         const QString& updatedAt,
         const QString& status);
    Task();
    // Геттеры
    int id() const;
    int userId() const;
    QString name() const;
    QString color() const;
    QString description() const;
    QString createdAt() const;
    QString updatedAt() const;
    QString status() const;

    // Сеттеры (если нужно менять)
    void setUserId(int userId);
    void setName(const QString& name);
    void setColor(const QString& color);
    void setDescription(const QString& description);
    void setStatus(const QString& status);

private:
    int m_id;
    int m_userId;
    QString m_name;
    QString m_color;
    QString m_description;
    QString m_createdAt;
    QString m_updatedAt;
    QString m_status;
};

#endif // TASK_H
