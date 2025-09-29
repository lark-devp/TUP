#include <QApplication>
#include <memory>
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "app/ApplicationController.h" // Подключаем наш новый контроллер

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 1. Создаем нужную фабрику
    auto uiFactory = std::make_unique<MinimalUIFactory>();

    // 2. Создаем Контроллер и передаем ему фабрику
    ApplicationController controller(std::move(uiFactory));

    // 3. Запускаем логику приложения
    controller.start();

    // Приложение работает, пока не закроются все окна.
    // Поскольку ApplicationController создан на стеке в main,
    // он будет жить до конца работы app.exec().
    return app.exec();
}
