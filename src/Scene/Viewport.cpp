#include "Scene/Viewport.h"

#include <QGraphicsPixmapItem>

namespace Viewport {
	
	Viewport::Viewport(int width, int height) {
		m_scene = new QGraphicsScene(nullptr);
		setScene(m_scene);
		m_size.setWidth(width);
		m_size.setHeight(height);
		
		m_updateTimer.start(1000 / 60);
		connect(&m_updateTimer, &QTimer::timeout, this, &Viewport::update);
		
		m_mainItem = new QGraphicsPixmapItem();
		m_scene->addItem(m_mainItem);
	}
	
	Viewport::Viewport(const QSize & size) {
		m_scene = new QGraphicsScene(nullptr);
		setScene(m_scene);
		m_size = size;
		
		m_updateTimer.start(1000 / 60);
		connect(&m_updateTimer, &QTimer::timeout, this, &Viewport::update);
		
		m_mainItem = new QGraphicsPixmapItem();
		m_scene->addItem(m_mainItem);
	}
	
	Viewport::~Viewport() {
		delete m_mainItem;
		delete m_scene;
	}
	
	void Viewport::setSize(const QSize & size) {
		if (m_size == size)
			return;
		
		m_size = size;
		emit onChangeSize(size);
	}
	
	void Viewport::setWidth(int width) {
		if (m_size.width() == width)
			return;
		
		m_size.setWidth(width);
		emit onChangeSize(m_size);
	}
	
	void Viewport::setHeight(int height) {
		if (m_size.height() == height)
			return;
		
		m_size.setHeight(height);
		emit onChangeSize(m_size);
	}
	
	void Viewport::setBackgroundImage(const QPixmap & image, bool repeat) {
		m_backgroundImage = image;
		setBackgroundBrush(QBrush(image));
		setRepeatBackground(repeat);
	}
	
	void Viewport::setBackgroundImage(const QString & imagePath, bool repeat) {
		QPixmap image;
		if (!image.load(imagePath)) {
			printf("E: %s -> Can't load image\n", __FUNCTION__);
			return;
		}
		
		m_backgroundImage = image;
		setBackgroundBrush(QBrush(image));
		setRepeatBackground(repeat);
	}
	
	void Viewport::setWorkImage(const QPixmap & image) {
		m_mainItem->setPixmap(image);
		emit onChangeWorkImage(image);
	}
	
	void Viewport::setWorkImage(const QString & path) {
		QPixmap image;
		if (!image.load(path)) {
			printf("E: %s -> Can't load image\n", __FUNCTION__);
			return;
		}
		
		m_mainItem->setPixmap(image);
		emit onChangeWorkImage(image);
	}
	
	QPixmap Viewport::getWorkImage() const {
		return m_mainItem->pixmap();
	}
	
	void Viewport::update() {
		m_mainItem->update();
	}
	
}

