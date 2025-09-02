#include "TaskRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>

// Получить все задачи для пользователя
QList<Task> TaskRepository::getTasks(int userId) {
    QList<Task> tasks;
    QSqlQuery query(DBManager::instance().database());

    query.prepare(R"(
        SELECT id, user_id, name, color, description, created_at, updated_at, status
        FROM tasks
        WHERE user_id = :user_id
        ORDER BY id
    )");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qWarning() << "Ошибка при получении задач:" << query.lastError().text();
        return tasks;
    }

    while (query.next()) {
        Task t(
            query.value("id").toInt(),
            query.value("user_id").toInt(),
            query.value("name").toString(),
            query.value("color").toString(),
            query.value("description").toString(),
            query.value("created_at").toString(),
            query.value("updated_at").toString(),
            query.value("status").toString()
            );
        tasks.append(t);
    }

    return tasks;
}

// Получить одну задачу по ID
Task TaskRepository::getTaskById(int taskId) {
    QSqlQuery query(DBManager::instance().database());

    query.prepare(R"(
        SELECT id, user_id, name, color, description, created_at, updated_at, status
        FROM tasks
        WHERE id = :id
    )");
    query.bindValue(":id", taskId);

    if (!query.exec() || !query.next()) {
        qWarning() << "Ошибка при получении задачи:" << query.lastError().text();
        return Task(); // пустая задача
    }

    return Task(
        query.value("id").toInt(),
        query.value("user_id").toInt(),
        query.value("name").toString(),
        query.value("color").toString(),
        query.value("description").toString(),
        query.value("created_at").toString(),
        query.value("updated_at").toString(),
        query.value("status").toString()
        );
}

// Сохранить задачу (новую или существующую)
bool TaskRepository::saveTask(const Task &task) {
    QSqlQuery query(DBManager::instance().database());

    if (task.id() == 0) {
        // Новая задача
        query.prepare(R"(
            INSERT INTO tasks (user_id, name, color, description, created_at, updated_at, status)
            VALUES (:user_id, :name, :color, :description, :created_at, :updated_at, :status)
        )");
    } else {
        // Обновление существующей задачи
        query.prepare(R"(
            UPDATE tasks
            SET user_id = :user_id,
                name = :name,
                color = :color,
                description = :description,
                created_at = :created_at,
                updated_at = :updated_at,
                status = :status
            WHERE id = :id
        )");
        query.bindValue(":id", task.id());
    }

    query.bindValue(":user_id", task.userId());
    query.bindValue(":name", task.name());
    query.bindValue(":color", task.color());
    query.bindValue(":description", task.description());
    query.bindValue(":created_at", task.createdAt());
    query.bindValue(":updated_at", task.updatedAt());
    query.bindValue(":status", task.status());

    if (!query.exec()) {
        qWarning() << "Ошибка при сохранении задачи:" << query.lastError().text();
        return false;
    }

    return true;
}

// Обновить задачу (только существующую)
bool TaskRepository::updateTask(const Task &task) {
    if (task.id() == 0) {
        qWarning() << "Невозможно обновить задачу с id = 0";
        return false;
    }

    QSqlQuery query(DBManager::instance().database());
    query.prepare(R"(
        UPDATE tasks
        SET name = :name,
            color = :color,
            description = :description,
            created_at = :created_at,
            updated_at = :updated_at,
            status = :status,
            user_id = :user_id
        WHERE id = :id
    )");

    query.bindValue(":name", task.name());
    query.bindValue(":color", task.color());
    query.bindValue(":description", task.description());
    query.bindValue(":created_at", task.createdAt());
    query.bindValue(":updated_at", task.updatedAt());
    query.bindValue(":status", task.status());
    query.bindValue(":user_id", task.userId());
    query.bindValue(":id", task.id());

    if (!query.exec()) {
        qWarning() << "Ошибка при обновлении задачи:" << query.lastError().text();
        return false;
    }

    return true;
}

// Удалить задачу по ID
bool TaskRepository::deleteTask(int taskId) {
    QSqlQuery query(DBManager::instance().database());

    query.prepare("DELETE FROM tasks WHERE id = :id");
    query.bindValue(":id", taskId);

    if (!query.exec()) {
        qWarning() << "Ошибка при удалении задачи:" << query.lastError().text();
        return false;
    }

    return true;
}
