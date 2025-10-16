#include <QApplication>
#include <memory>
#include <QDebug> // Для вывода ошибок



// Подключаем все необходимые компоненты
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "app/ApplicationController.h"
#include "db/PostgresDatabaseService.h"
#include "calendar/TweekApiServiceImpl.h" // <-- 1. Подключаем реализацию сервиса API

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

<<<<<<< HEAD
    // --- 1. Создание сервиса базы данных ---
    auto dbService = std::make_unique<PostgresDatabaseService>();
    if (!dbService->connectToSource()) {
        qCritical() << "Критическая ошибка: не удалось подключиться к базе данных!";
        return -1;
    }

    // --- 2. Создание UI фабрики ---
    auto uiFactory = std::make_unique<MinimalUIFactory>();

    // --- 3. Создание сервиса API (календаря) ---
    auto tweekApiService = std::make_unique<TweekApiServiceImpl>(); // <-- 2. Создаем экземпляр

    // --- 4. Создание главного контроллера с передачей ВСЕХ зависимостей ---
    ApplicationController controller(
        std::move(uiFactory),
        std::move(dbService),
        std::move(tweekApiService) // <-- 3. Передаем созданный сервис третьим аргументом
        );

    // --- 5. Запуск приложения ---
    controller.start();

=======
    MainWindow window;
    window.show();
>>>>>>> 4949d55e1d4276526d42de2e905266b4b0da814d
    return app.exec();
}
