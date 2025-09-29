#pragma once

#include <QWidget> // Включаем полный заголовочный файл для QWidget

/**
 * @brief Базовый интерфейс для любого окна ("вида") в приложении.
 * Определяет основной контракт для всех UI-компонентов.
 */
class IView : public QWidget
{
public:
     explicit IView(QWidget* parent = nullptr) : QWidget(parent) {}
    virtual ~IView() = default;

    /**
     * @brief Возвращает указатель на виджет для его отображения или встраивания.
     * @return Указатель на QWidget.
     */
    virtual QWidget* getWidget() = 0;

    /**
     * @brief Показывает вид.
     */
    virtual void showView() { if(getWidget()) getWidget()->show(); }

    /**
     * @brief Скрывает вид.
     */
    virtual void hideView() { if(getWidget()) getWidget()->hide(); }
};
