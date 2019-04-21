#ifndef FRAME_H
#define FRAME_H

#include <QObject>
#include <QPixmap>
#include <QSize>

class QXmlStreamWriter;
class QByteArray;

namespace Animation {
	
	class Animation;
	
	class Frame : public QObject {
		
		Q_OBJECT
		
		Animation * m_parent;
		
		QPixmap m_frameImage;
		QSize m_size;
		
	public:
		
		explicit Frame();
		explicit Frame(const QPixmap & frame);
		explicit Frame(const Frame & frame);
		~Frame();
		
		void setParent(Animation * parent);
		inline Animation * getParent() const;
		
		void setFrameImage(const QPixmap & image);
		inline const QPixmap & getFrameImage() const;
		
		void setSize(const QSize & size);
		void setWidth(int width);
		void setHeight(int height);
		
		inline const QSize & getSize() const;
		inline int getWidth() const;
		inline int getHeight() const;
		
	private:
		
		bool compareImages(const QPixmap & image);
		
	signals:
		
		void onChangeParent(Animation * parent);
		void onChangeFrameImage(const QPixmap & image);
		void onChangeSize(const QSize & size);
		
	};
	
	inline Animation * Frame::getParent() const {
		return m_parent;
	}
	
	inline const QPixmap & Frame::getFrameImage() const {
		return m_frameImage;
	}
	
	inline const QSize & Frame::getSize() const {
		return m_size;
	}
	
	inline int Frame::getWidth() const {
		return m_size.width() ;
	}
	
	inline int Frame::getHeight() const {
		return m_size.height() ;
	}
	
}
#endif // FRAME_H
