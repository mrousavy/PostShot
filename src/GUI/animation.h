#ifndef ANIMATION_H
#define ANIMATION_H
#include <QWidget>
#include <QPropertyAnimation>

namespace Animation
{

/*!
 * \brief fadeIn Fade the selected widget in
 * \param duration The duration of the animation in milliseconds
 * \param endValue The value to animate to (opacity, min: 0.0, max: 1.0)
 * \param func The std::function callback on animation finish
 * \return The created playing QPropertyAnimation
 */
template <typename F>
void fade(QObject* widget, int duration,
          double startValue, double endValue, F func = nullptr)
{
    QPropertyAnimation* animation = new QPropertyAnimation(widget, "windowOpacity");
    animation->setDuration(duration);
    animation->setStartValue(startValue);
    animation->setEndValue(endValue);
    animation->setEasingCurve(QEasingCurve::Linear);
    animation->start(QPropertyAnimation::DeleteWhenStopped);
    if (func != nullptr)
        QObject::connect(animation, &QPropertyAnimation::finished, func);
}

}

#endif // ANIMATION_H
