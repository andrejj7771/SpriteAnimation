#ifndef ANIMATIONCONTROLLER_H
#define ANIMATIONCONTROLLER_H

#include <QObject>
#include <vector>

class QString;

namespace Viewport {
	class AnimationScene;
}


namespace Animation {
	
	class Animation;
	class Frame;
	
	class AnimationController : public QObject {
		
		Q_OBJECT
		
		std::vector<Animation*> m_animations;
		Animation * m_currentAnimation;
		
		Viewport::AnimationScene * m_scene;
		
	public:
		
		AnimationController();
		~AnimationController();
		
		void appendAnimation(Animation * animation);
		
		Animation * getAnimation(const QString & name) const;
		inline Animation * getAnimation(size_t index) const;
		
		bool removeAnimation(size_t index);
		bool removeAnimation(const QString & name);
		
		void setCurrentAnimation(Animation * animation);
		inline Animation * getCurrentAnimation() const;
		inline size_t getNumAnimations() const;
		
		inline Viewport::AnimationScene * getScene() const;
		
	private:
		
		void currectAnimationConnection(Frame * frame);
		
	signals:
		
		void onAppendAnimation(Animation * animation);
		void onChangeCurrentAnimation(Animation * animation);
		
	};
	
	inline Animation * AnimationController::getAnimation(size_t index) const {
		return index >= m_animations.size() ? nullptr : m_animations.at(index);
	}
	
	inline Animation * AnimationController::getCurrentAnimation() const {
		return m_currentAnimation;
	}
	
	inline size_t AnimationController::getNumAnimations() const {
		return m_animations.size();
	}
	
	inline Viewport::AnimationScene * AnimationController::getScene() const {
		return m_scene;
	}
	
}
#endif // ANIMATIONCONTROLLER_H
