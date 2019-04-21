#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsView>
#include <QPixmap>
#include <QColor>
#include <QSize>
#include <QTimer>

#include <functional>
#include <vector>

class QGraphicsScene;
class QGraphicsPixmapItem;
class QGraphicsItem;

class QWheelEvent;
class QPoint;

namespace Viewport {
	
	class Scene : public QGraphicsView {
		
		Q_OBJECT
		
		QSize m_size;
		QGraphicsScene * m_scene;
		QGraphicsPixmapItem * m_mainItem;
		
		std::vector<QGraphicsItem*> m_items;
		
		QColor m_backgroundColor;
		QPixmap m_backgroundImage;
		
		bool m_mouseGrabbingSupport;
		bool m_keyGrabbingSupport;
		
		QTimer m_updateTimer;
		
	public:
		
		Scene(int width = 0, int height = 0);
		Scene(const QSize & size);
		~Scene() override;
		
		bool appendItem(QGraphicsItem * item);
		
		bool removeItem(QGraphicsItem * item);
		bool removeItem(size_t index);
		
		bool containsItem(QGraphicsItem * item) const;
		
		inline QGraphicsItem * getItem(size_t index) const;
		
		inline size_t getNumItems() const;
		
		void setSize(const QSize & size);
		void setWidth(int width);
		void setHeight(int height);
		
		inline void setMouseGrabbingSupport(bool support);
		inline bool isMouseGrabbingSupport() const;
		
		inline void setKeyGrabbingSupport(bool support);
		inline bool isKeyGrabbingSupport() const;
		
		inline const QSize & getSize() const;
		inline int getWidth() const;
		inline int getHeight() const;
		
		void setBackgroungColor(const QColor & color);
		inline const QColor & getBackgroundColor() const;
		
		void setBackgroundImage(const QPixmap & image, bool repeat = false);
		void setBackgroundImage(const QString & path, bool repeat = false);
		inline const QPixmap & getBackgroundImage() const;
		
		void setWorkImage(const QPixmap & image);
		void setWorkImage(const QString & path);
		QPixmap getWorkImage() const;
		
		void setRepeatBackground(bool value = true) {
			value ? setCacheMode(QGraphicsView::CacheBackground) :
					setCacheMode(QGraphicsView::CacheNone);
		}
		
	private:
		
		void mousePressEvent(QMouseEvent * event) override;
		void mouseReleaseEvent(QMouseEvent * event) override;
		void mouseDoubleClickEvent(QMouseEvent * event) override;
		void mouseMoveEvent(QMouseEvent * event) override;
		
		void keyPressEvent(QKeyEvent * event) override;
		void keyReleaseEvent(QKeyEvent * event) override;
		
		void wheelEvent(QWheelEvent * event) override;
		
		void update();
		
	signals:
		
		void onChangeSize(const QSize & size);
		void onChangeWorkImage(QPixmap image);
		
		void onAppendItem(QGraphicsItem * item);
		
		void onDoubleClick(const QPoint & pos, Qt::MouseButton button);
		void onMouseDown(const QPoint & pos, Qt::MouseButton button);
		void onMouseUp(const QPoint & pos, Qt::MouseButton button);
		void onMouseMove(const QPoint & pos);
		
		void onKeyDown(Qt::Key key);
		void onKeyUp(Qt::Key key);
		
	};
	
	inline QGraphicsItem * Scene::getItem(size_t index) const {
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
	
	inline const QSize & Scene::getSize() const {
		return m_size;
	}
	
	inline int Scene::getWidth() const {
		return m_size.width();
	}
	
	inline int Scene::getHeight() const {
		return m_size.height();
	}
	
	inline const QColor & Scene::getBackgroundColor() const {
		return m_backgroundColor;
	}
	
	inline const QPixmap & Scene::getBackgroundImage() const {
		return m_backgroundImage;
	}
	
}
#endif // SCENE_H
