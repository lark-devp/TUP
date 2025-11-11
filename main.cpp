#include <QApplication>
#include <memory>
#include <QDebug>
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "app/ApplicationController.h"
#include "db/SqliteDatabaseService.h"
#include "calendar/TweekApiServiceImpl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    auto dbService = std::make_unique<SqliteDatabaseService>();

    // Подключаемся к источнику данных
    if (!dbService->connectToSource()) {
        // Можно показать критическую ошибку пользователю
        return -1; // Завершаем приложение, если не удалось подключиться к БД
    }

    auto factory = std::make_unique<MinimalUIFactory>();
    auto tweekService = std::make_unique<TweekApiServiceImpl>();

    ApplicationController controller(std::move(factory), std::move(dbService), std::move(tweekService));
    controller.start();

    return app.exec();
}
