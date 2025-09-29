#include <QApplication>
#include <memory> // для std::unique_ptr

// 1. Подключаем ТОЛЬКО ИНТЕРФЕЙСЫ и КОНКРЕТНУЮ ФАБРИКУ
#include "ui/interfaces/IUIFactory.h"
#include "ui/interfaces/ITaskSelectionView.h"
#include "ui/theme/minimal/MinimalUIFactory.h"
// ВАЖНО: мы больше не подключаем "MinimalistTaskSelectionView.h" напрямую!

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // 2. Создаем экземпляр нужной нам фабрики.
    // Если захотим сменить стиль, нужно будет поменять только эту строчку.
    // Например: auto uiFactory = std::make_unique<CyberpunkUIFactory>();
    auto uiFactory = std::make_unique<MinimalUIFactory>();

    // 3. Просим фабрику создать для нас главное окно.
    // Обратите внимание, тип переменной - это указатель на ИНТЕРФЕЙС,
    // а не на конкретный класс.
    std::unique_ptr<ITaskSelectionView> mainWindow = uiFactory->createTaskListWindow();

    // 4. Получаем из интерфейса указатель на конкретный QWidget и показываем его.
    // Для этого и нужен был метод getWidget() в базовом интерфейсе IView.
    if (mainWindow && mainWindow->getWidget()) {
        mainWindow->getWidget()->show();
    } else {
        // Обработка ошибки, если окно не было создано
        return -1;
    }

    // 5. Запускаем приложение
    return app.exec();
}
