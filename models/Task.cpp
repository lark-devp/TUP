#include "Task.h"


// Конструктор по умолчанию
Task::Task()
    : m_id(0),
    m_userId(0),
    m_name(""),
    m_color(""),
    m_description(""),
    m_createdAt(""),
    m_updatedAt(""),
    m_status("")
{
}

// Конструктор с параметрами (только один раз!)
Task::Task(int id,
           int userId,
           const QString& name,
           const QString& color,
           const QString& description,
           const QString& createdAt,
           const QString& updatedAt,
           const QString& status)
    : m_id(id),
    m_userId(userId),
    m_name(name),
    m_color(color),
    m_description(description),
    m_createdAt(createdAt),
    m_updatedAt(updatedAt),
    m_status(status)
{
}

int Task::id() const { return m_id; }
int Task::userId() const { return m_userId; }
QString Task::name() const { return m_name; }
QString Task::color() const { return m_color; }
QString Task::description() const { return m_description; }
QString Task::createdAt() const { return m_createdAt; }
QString Task::updatedAt() const { return m_updatedAt; }
QString Task::status() const { return m_status; }

void Task::setUserId(int userId) { m_userId = userId; }
void Task::setName(const QString& name) { m_name = name; }
void Task::setColor(const QString& color) { m_color = color; }
void Task::setDescription(const QString& description) { m_description = description; }
void Task::setStatus(const QString& status) { m_status = status; }
