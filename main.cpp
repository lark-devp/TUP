#include <QApplication>
#include <QIcon>
#include <QPixmap>
#include <QPainter>
#include <QFont>
#include <QColor>

#include "app/ApplicationController.h"
#include "db/SqliteDatabaseService.h"
#include "ui/theme/minimal/MinimalUIFactory.h"
#include "calendar/TweekApiServiceImpl.h"

QIcon createAppIcon()
{
    QPixmap pixmap(64, 64);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(pixmap.rect());

    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 40, QFont::Bold));
    painter.drawText(pixmap.rect(), Qt::AlignCenter, "T");

    return QIcon(pixmap);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(createAppIcon());

    auto factory = std::make_unique<MinimalUIFactory>();
    auto dbService = std::make_unique<SqliteDatabaseService>();
    auto tweekService = std::make_unique<TweekApiServiceImpl>();

    if (!dbService->connectToSource()) {
        return 1;
    }

    ApplicationController controller(std::move(factory), std::move(dbService), std::move(tweekService));
    controller.start();

    return a.exec();
}
