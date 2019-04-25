#include "Scene/Scene.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <QMouseEvent>
#include <QKeyEvent>

#include "../items.h"

namespace Viewport {

	Scene::Scene(int width, int height) : Viewport (width, height) {
		m_mouseGrabbingSupport = true;
		m_keyGrabbingSupport = true;
	}
	
	Scene::Scene(const QSize & size) : Viewport (size) {
		m_mouseGrabbingSupport = true;
		m_keyGrabbingSupport = true;
	}
	
	Scene::~Scene() {
		for (auto item : m_items)
			delete item;
	}
	
	bool Scene::appendItem(Object::ViewportItem * item) {
		if (std::find(m_items.begin(), m_items.end(), item) != m_items.end())
			return false;
		
		m_items.push_back(item);
		m_scene->addItem(item);
		item->setScene(this);
		emit onAppendItem(item);
		return true;
	}
	
	bool Scene::removeItem(Object::ViewportItem * item) {
		auto itemIterator = std::find(m_items.begin(), m_items.end(), item);
		if (itemIterator == m_items.end())
			return false;
		
		item->setScene(nullptr);
		m_scene->removeItem(item);
		m_items.erase(itemIterator);
		return true;
	}
	
	bool Scene::removeItem(size_t index) {
		if (index >= m_items.size())
			return false;
		
		Object::ViewportItem * item = m_items.at(index);
		if (!item)
			return false;
		
		item->setScene(nullptr);
		m_scene->removeItem(item);
		m_items.erase(m_items.begin() + int(index));
		return true;
	}
	
	void Scene::setWorkImage(const QPixmap & image) {
		Viewport::setWorkImage(image);
		setSceneRect(0, 0, image.width(), image.height());
	}
	
	void Scene::setWorkImage(const QString & path) {
		Viewport::setWorkImage(path);
		const QPixmap & image = getWorkImage();
		setSceneRect(0, 0, image.width(), image.height());
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
		Viewport::update();
		for (Object::ViewportItem * item : m_items)
			item->update();
	}
	
}
