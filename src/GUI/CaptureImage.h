#ifndef CAPTUREIMAGE_H
#define CAPTUREIMAGE_H

#include <QWidget>
#include <QPixmap>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QShortcut>

#include "Modules/WindowHelper.h"


class CaptureImage : public QWidget
{
	Q_OBJECT
public:
	/*!
	 * Create a new object of the Capture Image Window
	 */
	explicit CaptureImage(QWidget* parent = nullptr);
	~CaptureImage();

	void showNormal() = delete;
	void showMinimized() = delete;
	void showMaximized() = delete;
	void showFullScreen() = delete;
	void show();
	void close();
signals:

public slots:

private:
	QGraphicsScene* scene;
	QGraphicsView* view;
	QLayout* layout;
	QGraphicsRectItem* rect;
	QShortcut* shortcut;
	QPixmap image;
	QList<WindowHelper::Window> windows;
	QPoint start, end;
	QRect capture;

private:
	bool onKeyDown(QEvent* event);
	bool onMouseMove(QMouseEvent* event);
	bool onMouseDown(QMouseEvent* event);
	bool onMouseUp(QMouseEvent* event);

	void updateCapture();
	void captureFinish();
	void captureAll();

protected:
	bool eventFilter(QObject* obj, QEvent* event);
};

#endif // CAPTUREIMAGE_H
