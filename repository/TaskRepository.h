#ifndef TASKREPOSITORY_H
#define TASKREPOSITORY_H

#include <QList>
#include "../models/Task.h"
#include "../db/DBManager.h"

class TaskRepository {
public:
    TaskRepository() = default;

    // Получить все задачи конкретного пользователя
    QList<Task> getTasks(int userId);

    // Получить задачу по ID
    Task getTaskById(int taskId);

    // Сохранить задачу (INSERT)
    bool saveTask(const Task &task);

    // Обновить задачу
    bool updateTask(const Task &task);

    // Удалить задачу
    bool deleteTask(int taskId);
};

#endif // TASKREPOSITORY_H
