#include "Scene/Scene.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QMouseEvent>
#include <QKeyEvent>

namespace Viewport {
	
	Scene::Scene(int width, int height) {
		m_scene = new QGraphicsScene(nullptr);
		setScene(m_scene);
		m_size.setWidth(width);
		m_size.setHeight(height);
		
		m_mouseGrabbingSupport = true;
		m_keyGrabbingSupport = true;
		
		m_updateTimer.start(1000 / 60);
		connect(&m_updateTimer, &QTimer::timeout, this, &Scene::update);
		
		m_mainItem = new QGraphicsPixmapItem();
		m_scene->addItem(m_mainItem);
	}
	
	Scene::Scene(const QSize & size) {
		m_scene = new QGraphicsScene(nullptr);
		setScene(m_scene);
		m_size = size;
		
		m_updateTimer.start(1000 / 60);
		connect(&m_updateTimer, &QTimer::timeout, this, &Scene::update);
		
		m_mainItem = new QGraphicsPixmapItem();
		m_scene->addItem(m_mainItem);
	}
	
	Scene::~Scene() {
		for (auto item : m_items)
			delete item;
		m_items.clear();
		
		delete m_scene;
	}
	
	bool Scene::appendItem(QGraphicsItem * item) {
		if (std::find(m_items.begin(), m_items.end(), item) != m_items.end())
			return false;
		
		m_scene->addItem(item);
		emit onAppendItem(item);
		return true;
	}
	
	bool Scene::removeItem(QGraphicsItem * item) {
		auto itemIterator = std::find(m_items.begin(), m_items.end(), item);
		if (itemIterator == m_items.end())
			return false;
		
		m_scene->removeItem(item);
		m_items.erase(itemIterator);
		return true;
	}
	
	bool Scene::removeItem(size_t index) {
		if (index >= m_items.size())
			return false;
		
		QGraphicsItem * item = m_items.at(index);
		if (!item)
			return false;
		
		m_scene->removeItem(item);
		m_items.erase(m_items.begin() + int(index));
		return true;
	}
	
	bool Scene::containsItem(QGraphicsItem * item) const {
		return std::find(m_items.begin(), m_items.end(), item) != m_items.end();
	}
	
	void Scene::setSize(const QSize & size) {
		if (m_size == size)
			return;
		
		m_size = size;
		emit onChangeSize(size);
	}
	
	void Scene::setWidth(int width) {
		if (m_size.width() == width)
			return;
		
		m_size.setWidth(width);
		emit onChangeSize(m_size);
	}
	
	void Scene::setHeight(int height) {
		if (m_size.height() == height)
			return;
		
		m_size.setHeight(height);
		emit onChangeSize(m_size);
	}
	
	void Scene::setBackgroungColor(const QColor & color) {
		m_backgroundColor = color;
		setBackgroundBrush(QBrush(color));
	}
	
	void Scene::setBackgroundImage(const QPixmap & image, bool repeat) {
		m_backgroundImage = image;
		setBackgroundBrush(QBrush(image));
		repeat ? setCacheMode(QGraphicsView::CacheBackground) : 
				 setCacheMode(QGraphicsView::CacheNone);
	}
	
	void Scene::setBackgroundImage(const QString & imagePath, bool repeat) {
		QPixmap image;
		if (!image.load(imagePath)) {
			printf("E: %s -> Can't load image\n", __FUNCTION__);
			return;
		}
		
		m_backgroundImage = image;
		setBackgroundBrush(QBrush(image));
		repeat ? setCacheMode(QGraphicsView::CacheBackground) : 
				 setCacheMode(QGraphicsView::CacheNone);
	}
	
	void Scene::setWorkImage(const QPixmap & image) {
		if (getWorkImage().toImage() == image.toImage())
			return;
		
		m_mainItem->setPixmap(image);
		m_mainItem->setPos(0, -image.height());
		
		emit onChangeWorkImage(image);
	}
	
	void Scene::setWorkImage(const QString & path) {
		QPixmap image;
		if (!image.load(path)) {
			printf("E: %s -> Can't load image\n", __FUNCTION__);
			return;
		}
		
		m_mainItem->setPixmap(image);
		m_mainItem->setPos(0, -image.height());
		
		emit onChangeWorkImage(image);
	}
	
	QPixmap Scene::getWorkImage() const {
		return m_mainItem->pixmap();
	}
	
	void Scene::mousePressEvent(QMouseEvent * event) {
		if (!m_mouseGrabbingSupport)
			return;
		
		emit onMouseDown(event->pos(), event->button());
	}
	
	void Scene::mouseReleaseEvent(QMouseEvent * event) {
		if (!m_mouseGrabbingSupport)
			return;
		
		emit onMouseUp(event->pos(), event->button());
	}
	
	void Scene::mouseDoubleClickEvent(QMouseEvent * event) {
		if (!m_mouseGrabbingSupport)
			return;
		
		emit onDoubleClick(event->pos(), event->button());
	}
	
	void Scene::mouseMoveEvent(QMouseEvent * event) {
		if (!m_mouseGrabbingSupport)
			return;
		
		emit onMouseMove(event->pos());
	}
	
	void Scene::keyPressEvent(QKeyEvent * event) {
		if (!m_keyGrabbingSupport)
			return;
		
		emit onKeyDown(static_cast<Qt::Key>(event->key()));
	}
	
	void Scene::keyReleaseEvent(QKeyEvent * event) {
		if (!m_keyGrabbingSupport)
			return;
		
		emit onKeyUp(static_cast<Qt::Key>(event->key()));
	}
	
	void Scene::wheelEvent(QWheelEvent * event) {
		if (!m_mouseGrabbingSupport)
			return;
		
		int delta = event->delta();
		if (delta > 0)
			scale(1.1, 1.1);
		else if (delta < 0)
			scale(0.9, 0.9);
	}
	
	void Scene::update() {
		m_mainItem->update();
		for (const auto & item : m_items)
			item->update();
	}
	
}
