#include <QApplication>
#include <memory>
#include <QDebug>
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "app/ApplicationController.h"
#include "db/PostgresDatabaseService.h"
#include "calendar/TweekApiServiceImpl.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);


    auto dbService = std::make_unique<PostgresDatabaseService>();
    if (!dbService->connectToSource()) {
        qCritical() << "Критическая ошибка: не удалось подключиться к базе данных!";
        return -1;
    }


    auto uiFactory = std::make_unique<MinimalUIFactory>();


    auto tweekApiService = std::make_unique<TweekApiServiceImpl>();


    ApplicationController controller(
        std::move(uiFactory),
        std::move(dbService),
        std::move(tweekApiService)
        );


    controller.start();

    return app.exec();
}
