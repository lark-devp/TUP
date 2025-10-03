#include <QApplication>
#include <memory>
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "app/ApplicationController.h" // Подключаем наш новый контроллер
#include "db/PostgresDatabaseService.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    auto dbService = std::make_unique<PostgresDatabaseService>();
    if (!dbService->connectToSource()) { // Метод connectToSource() вы должны реализовать
        qCritical() << "Не удалось подключиться к базе данных!";
        return -1;
    }

    auto uiFactory = std::make_unique<MinimalUIFactory>();


    ApplicationController controller(std::move(uiFactory), std::move(dbService));

    controller.start();

    return app.exec();
}
