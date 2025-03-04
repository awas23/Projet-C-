#include "notification.h"
#include <QSystemTrayIcon>

notification::notification(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint |        // Disable window decoration
                   Qt::Tool |                       // Discard display in a separate window
                   Qt::WindowStaysOnTopHint);       // Set on top of all windows
    setAttribute(Qt::WA_TranslucentBackground);     // Indicates that the background will be transparent
    setAttribute(Qt::WA_ShowWithoutActivating);     // At the show, the widget does not get the focus automatically

    animation.setTargetObject(this);                // Set the target animation
    animation.setPropertyName("popupOpacity");      //
    connect(&animation, &QAbstractAnimation::finished, this, &notification::hide);

    label.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    label.setStyleSheet("QLabel { color : white; "
                        "margin-top: 60px;"
                        "margin-bottom: 60px;"
                        "margin-left: 60px;"
                        "margin-right: 60px; }");

    layout.addWidget(&label, 0, 0);
    setLayout(&layout);

    timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &notification::hideAnimation);
}

void notification::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    QRect roundedRect;
    roundedRect.setX(rect().x() + 5);
    roundedRect.setY(rect().y() + 5);
    roundedRect.setWidth(rect().width() - 10);
    roundedRect.setHeight(rect().height() - 10);

    painter.setBrush(QBrush(QColor(0,0,0,180)));
    painter.setPen(Qt::NoPen);

    painter.drawRoundedRect(roundedRect, 10, 10);
}

void notification::setPopupText(const QString &text)
{
    label.setText(text);    // Set the text in the Label
    adjustSize();           // With the recalculation notice sizes
}

void notification::show()
{
    setWindowOpacity(0.0);  // Set the transparency to zero

    animation.setDuration(4000);     // Configuring the duration of the animation
    animation.setStartValue(0.0);   // The start value is 0 (fully transparent widget)
    animation.setEndValue(1.0);     // End - completely opaque widget

    setGeometry(QApplication::desktop()->availableGeometry().width() - 36 - width() + QApplication::desktop() -> availableGeometry().x(),
                QApplication::desktop()->availableGeometry().height() - 36 - height() + QApplication::desktop() -> availableGeometry().y(),
                width(),
                height());
    QWidget::show();

    animation.start();
    timer->start(8500);
}

void notification::hideAnimation()
{
    timer->stop();
    animation.setDuration(3000);
    animation.setStartValue(1.0);
    animation.setEndValue(0.0);
    animation.start();
}

void notification::hide()
{
    // If the widget is transparent, then hide it
    if(getPopupOpacity() == 0.0){
        QWidget::hide();
    }
}

void notification::setPopupOpacity(float opacity)
{
    popupOpacity = opacity;

    setWindowOpacity(opacity);
}

float notification::getPopupOpacity() const
{
    return popupOpacity;
}

