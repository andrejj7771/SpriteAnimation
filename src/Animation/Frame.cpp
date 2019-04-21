#include "Animation/Frame.h"

namespace Animation {
	
	Frame::Frame() {
		m_parent = nullptr;
		m_size = QSize(0, 0);
	}
	
	Frame::Frame(const QPixmap & frame) {
		m_parent = nullptr;
		m_frameImage = frame;
		
		m_size = frame.size();
	}
	
	Frame::Frame(const Frame & frame) {
		m_parent = frame.m_parent;
		m_frameImage = frame.m_frameImage;
		m_size = frame.m_size;
	}
	 
	Frame::~Frame() {
		m_parent = nullptr;
	}
	
	void Frame::setParent(Animation * parent) {
		if (m_parent == parent || parent == nullptr)
			return;
		
		m_parent = parent;
		emit onChangeParent(parent);
	}
	
	void Frame::setFrameImage(const QPixmap & image) {
		if (compareImages(image))
			return;
		
		m_frameImage = image;
		emit onChangeFrameImage(image);
	}
	
	void Frame::setSize(const QSize & size) {
		if (m_size == size)
			return;
		
		m_size = size;
		emit onChangeSize(size);
	}
	
	void Frame::setWidth(int width) {
		if (m_size.width() == width)
			return;
		
		m_size.setWidth(width);
		emit onChangeSize(m_size);
	}
	
	void Frame::setHeight(int height) {
		if (m_size.height() == height)
			return;
		
		m_size.setHeight(height);
		emit onChangeSize(m_size);
	}
	
	bool Frame::compareImages(const QPixmap & image) {
		if (m_frameImage.size() != image.size())
			return false;
		
		const QImage & _frameImage = m_frameImage.toImage();
		const QImage & _image = image.toImage();
		
		return _frameImage == _image;
	}
	
}
