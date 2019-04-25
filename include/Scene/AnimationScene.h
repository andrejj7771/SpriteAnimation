#ifndef ANIMATIONSCENE_H
#define ANIMATIONSCENE_H

#include "Scene/Scene.h"

namespace Viewport {
	
	class AnimationScene : public Viewport {
			
		public:
			
			AnimationScene(int width, int height);
			AnimationScene(const QSize & size);
			
			void setWorkImage(const QPixmap & image) override;
			void setWorkImage(const QString & path) override;
			
	};
	
}

#endif // ANIMATIONSCENE_H
