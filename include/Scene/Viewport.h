#ifndef VIEWPORT_H
#define VIEWPORT_H

#include <QGraphicsView>
#include <QTimer>

namespace Viewport {
	
	class Viewport : public QGraphicsView {
			
			Q_OBJECT
			
			QSize m_size;
			QPixmap m_backgroundImage;
			
			QTimer m_updateTimer;
			
		protected:
			
			QGraphicsScene * m_scene;
			QGraphicsPixmapItem * m_mainItem;
			
		public:
			
			Viewport(int w, int h);
			Viewport(const QSize & size);
			virtual ~Viewport() override;
			
			void setSize(const QSize & size);
			void setWidth(int width);
			void setHeight(int height);
			
			inline const QSize & getSize() const;
			inline int getWidth() const;
			inline int getHeight() const;
			
			void setBackgroundImage(const QPixmap & image, bool repeat = false);
			void setBackgroundImage(const QString & path, bool repeat = false);
			inline const QPixmap & getBackgroundImage() const;
			
			virtual void setWorkImage(const QPixmap & image);
			virtual void setWorkImage(const QString & path);
			QPixmap getWorkImage() const;
			
			inline void setRepeatBackground(bool value = true);
			
			virtual void update();
			
		signals:
			
			void onChangeSize(const QSize & size);
			void onChangeWorkImage(QPixmap image);
			
	};
	
	inline const QSize & Viewport::getSize() const {
		return m_size;
	}
	
	inline int Viewport::getWidth() const {
		return m_size.width();
	}
	
	inline int Viewport::getHeight() const {
		return m_size.height();
	}
	
	inline const QPixmap & Viewport::getBackgroundImage() const {
		return m_backgroundImage;
	}
	
	inline void Viewport::setRepeatBackground(bool value) {
		value ? setCacheMode(QGraphicsView::CacheBackground) :
				setCacheMode(QGraphicsView::CacheNone);
	}
	
}

#endif // VIEWPORT_H
