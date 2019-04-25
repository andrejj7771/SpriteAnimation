#include "Scene/AnimationScene.h"

namespace Viewport {
	
	AnimationScene::AnimationScene(int width, int height) : Viewport (width, height) {}
	
	AnimationScene::AnimationScene(const QSize & size) : Viewport (size) {}
	
	void AnimationScene::setWorkImage(const QPixmap & image) {
		Viewport::setWorkImage(image);
		m_mainItem->setPos(0, -image.height());
	}
	
	void AnimationScene::setWorkImage(const QString & path) {
		Viewport::setWorkImage(path);
		const QPixmap & image = getWorkImage();
		m_mainItem->setPos(0, -image.height());
	}
	
}
