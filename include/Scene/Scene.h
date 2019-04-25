#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsRectItem>

#include <vector>

#include "Scene/Viewport.h"

class QGraphicsScene;
class QGraphicsPixmapItem;
class QGraphicsItem;

class QWheelEvent;
class QPoint;

namespace Viewport {
	
	namespace Object {
		class ViewportItem;
	}
	
	class Scene : public Viewport {
		
		Q_OBJECT
		
		std::vector<Object::ViewportItem*> m_items;
		
		bool m_mouseGrabbingSupport;
		bool m_keyGrabbingSupport;
		
	public:
		
		Scene(int width = 0, int height = 0);
		Scene(const QSize & size);
		~Scene() override;
		
		bool appendItem(Object::ViewportItem * item);
		bool removeItem(Object::ViewportItem * item);
		bool removeItem(size_t index);
		
		inline bool containsItem(Object::ViewportItem * item) const;
		
		inline Object::ViewportItem * getItem(size_t index) const;
		
		inline size_t getNumItems() const;
		
		inline void setMouseGrabbingSupport(bool support);
		inline bool isMouseGrabbingSupport() const;
		
		inline void setKeyGrabbingSupport(bool support);
		inline bool isKeyGrabbingSupport() const;
		
		void setWorkImage(const QPixmap & image) override;
		void setWorkImage(const QString & path) override;
		
	private:
		
		void mousePressEvent(QMouseEvent * event) override;
		void mouseReleaseEvent(QMouseEvent * event) override;
		void mouseDoubleClickEvent(QMouseEvent * event) override;
		void mouseMoveEvent(QMouseEvent * event) override;
		
		void keyPressEvent(QKeyEvent * event) override;
		void keyReleaseEvent(QKeyEvent * event) override;
		
		void wheelEvent(QWheelEvent * event) override;
		
		void update() override;
		
	signals:
		
		void onAppendItem(Object::ViewportItem * item);
		
		void onDoubleClick(const QPoint & pos, Qt::MouseButton button);
		void onMouseDown(const QPoint & pos, Qt::MouseButton button);
		void onMouseUp(const QPoint & pos, Qt::MouseButton button);
		void onMouseMove(const QPoint & pos);
		
		void onKeyDown(Qt::Key key);
		void onKeyUp(Qt::Key key);
		
	};
	
	inline bool Scene::containsItem(Object::ViewportItem * item) const {
		return std::find(m_items.begin(), m_items.end(), item) != m_items.end();
	}
	
	inline Object::ViewportItem * Scene::getItem(size_t index) const {
		return index >= m_items.size() ? nullptr : m_items.at(index);
	}
	
	inline size_t Scene::getNumItems() const {
		return m_items.size();
	}
	
	inline void Scene::setMouseGrabbingSupport(bool support) {
		m_mouseGrabbingSupport = support;
	}
	
	inline bool Scene::isMouseGrabbingSupport() const {
		return m_mouseGrabbingSupport;
	}
	
	inline void Scene::setKeyGrabbingSupport(bool support) {
		m_keyGrabbingSupport = support;
	}
	
	inline bool Scene::isKeyGrabbingSupport() const {
		return m_keyGrabbingSupport;
	}
	
}
#endif // SCENE_H
