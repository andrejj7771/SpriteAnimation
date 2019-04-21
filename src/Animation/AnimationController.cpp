#include "Animation/AnimationController.h"
#include "Animation/Animation.h"
#include "Animation/Frame.h"

#include "Scene/Scene.h"

namespace Animation {
	
	AnimationController::AnimationController() {
		m_currentAnimation = nullptr;
		
		m_scene = new Viewport::Scene(250, 250);
		m_scene->setMouseGrabbingSupport(false);
		m_scene->setKeyGrabbingSupport(false);
		m_scene->setBackgroundImage(":/resources/checker.png", true);
		m_scene->show();
	}
	
	AnimationController::~AnimationController() {
		m_currentAnimation = nullptr;
		for (auto animation : m_animations)
			delete animation;
		m_animations.clear();
		
		delete m_scene;
	}
	
	void AnimationController::appendAnimation(Animation * animation) {
		if (!animation)
			return;
		
		auto animIterator = std::find(m_animations.begin(), m_animations.end(), animation);
		if (animIterator != m_animations.end())
			return;
		
		m_animations.push_back(animation);
		if (m_currentAnimation == nullptr)
			setCurrentAnimation(animation);
		
		emit onAppendAnimation(animation);
	}
	
	Animation * AnimationController::getAnimation(const QString & name) const {
		if (name.isEmpty())
			return nullptr;
		
		auto animIterator = std::find_if(m_animations.begin(), m_animations.end(), [name](Animation * anim) -> bool {
			if (anim->getName() == name)
				return true;
			return false;
		});
		
		if (animIterator != m_animations.end())
			return *animIterator;
		return nullptr;
	}
	
	bool AnimationController::removeAnimation(size_t index) {
		if (index >= m_animations.size())
			return false;
		
		Animation * animation = m_animations.at(index);
		const auto & animationIterator = std::find(m_animations.begin(), m_animations.end(), animation);
		m_animations.erase(animationIterator);
		
		return true;
	}
	
	bool AnimationController::removeAnimation(const QString & name) {
		if (name.isEmpty())
			return false;
		
		auto animIterator = std::find_if(m_animations.begin(), m_animations.end(), [name](Animation * anim) -> bool {
			if (anim->getName() == name)
				return true;
			return false;
		});
		
		if (animIterator == m_animations.end())
			return false;
	
		m_animations.erase(animIterator);
		return true;
	}
	
	void AnimationController::setCurrentAnimation(Animation * animation) {
		if (m_currentAnimation) {
			m_currentAnimation->stop();
			disconnect(m_currentAnimation, &Animation::onChangeCurrentFrame, this, &AnimationController::currectAnimationConnection);
		}
		m_currentAnimation = animation;
		
		if (animation->getNumFrames() != 0)
			m_scene->setWorkImage(animation->getFrame(0)->getFrameImage());
		connect(m_currentAnimation, &Animation::onChangeCurrentFrame, this, &AnimationController::currectAnimationConnection);
		
		emit onChangeCurrentAnimation(animation);
	}
	
	void AnimationController::currectAnimationConnection(Frame * frame) {
		m_scene->setWorkImage(frame->getFrameImage());
	}
	
}
