#include "Animation/Animation.h"
#include "Animation/Frame.h"

namespace Animation {
	
	Animation::Animation(int delay) {
		m_currentFrame = nullptr;
		m_isPlaying = false;
		m_delay = delay;
		
		m_delayTimer.setInterval(m_delay);
		m_delayTimer.setSingleShot(false);
		
		m_direction = PlayingDirection::Forward;
		
		m_name = "DefaultAnimation";
		m_isLoop = false;
		
		initConnections();
	}
	
	Animation::Animation(const std::vector<Frame *> & frames, int delay) {
		m_frames = frames;
		m_currentFrame = *m_frames.begin();
		m_delay = delay;
		m_isPlaying = false;
		
		m_delayTimer.setInterval(m_delay);
		m_delayTimer.setSingleShot(false);
		
		m_direction = PlayingDirection::Forward;
		
		m_name = "DefaultAnimation";
		
		initConnections();
	}
	
	Animation::Animation(const Animation & anim) {
		for (Frame * frame : anim.m_frames) {
			Frame * _frame = new Frame(*frame);
			m_frames.push_back(_frame);
		}
		Frame * _curr = new Frame(*anim.m_currentFrame);
		m_currentFrame = _curr;
		
		m_delay = anim.m_delay;
		m_isPlaying = false;
		
		m_direction = anim.m_direction;
		
		m_name = anim.m_name;
		
		initConnections();
	}
	
	Animation::~Animation() {
		clear();
	}
	
	void Animation::setName(const QString & name) {
		if (m_name == name)
			return;
		
		m_name = name;
		emit onChangeName(name);
	}
	
	void Animation::setPlayingDirection(PlayingDirection direction) {
		if (m_direction == direction)
			return;
		
		m_direction = direction;
		emit onChangePlayingDirection(direction);
	}
	
	bool Animation::appendFrame(Frame * frame) {
		if (!frame)
			return false;
		
		auto frameIterator = std::find(m_frames.begin(), m_frames.end(), frame);
		if (frameIterator != m_frames.end())
			return false;
		
		m_frames.push_back(frame);
		frame->setParent(this);
		emit onAppendFrame(frame);
		
		if (m_currentFrame == nullptr)
			setCurrentFrame(frame);
		
		return true;
	}
	
	bool Animation::removeFrame(Frame * frame) {
		if (!frame)
			return false;
		
		auto frameIterator = std::find(m_frames.begin(), m_frames.end(), frame);
		if (frameIterator == m_frames.end())
			return false;
		
		if (m_currentFrame == frame)
			m_currentFrame = nullptr;
		
		m_frames.erase(frameIterator);
		delete frame;
		return true;
	}
	
	void Animation::setDelay(int delay) {
		if (m_delay == delay)
			return;
		
		m_delay = delay;
		m_delayTimer.setInterval(m_delay);
		emit onChangeDelay(delay);
	}
	
	void Animation::play() {
		if (m_isPlaying || !m_frames.size())
			return;
		
		if (m_currentFrame == m_frames.at(m_frames.size() - 1) && !m_isLoop)
			m_currentFrame = *m_frames.begin();
		
		m_isPlaying = true;
		m_delayTimer.start();
		
		emit onPlay();
	}
	
	void Animation::stop() {
		if (m_isPlaying == false)
			return;
		
		m_isPlaying = false;
		m_delayTimer.stop();
		
		emit onStop();
	}
	
	void Animation::next() {
		auto it = std::find(m_frames.begin(), m_frames.end(), m_currentFrame);
		if (it == m_frames.end())
			return;
		
		if (it == m_frames.end() - 1) {
			if (!m_isLoop && m_isPlaying) {
				stop();
				return;
			}
			
			setCurrentFrame(*m_frames.begin());
			return;
		}
		
		setCurrentFrame(*(it + 1));
	}
	
	void Animation::prev() {
		auto it = std::find(m_frames.begin(), m_frames.end(), m_currentFrame);
		if (it == m_frames.end())
			return;
		
		if (it == m_frames.begin()) {
			if (!m_isLoop && m_isPlaying) {
				stop();
				return;
			}
			
			it = m_frames.end();
		}
		setCurrentFrame(*(it - 1));
	}
	
	void Animation::clear() {
		stop();
		
		m_delay = 0;
		m_currentFrame = nullptr;
		
		for (Frame * frame : m_frames)
			delete frame;
		m_frames.clear();
	}
	
	void Animation::initConnections() {
		connect(&m_delayTimer, &QTimer::timeout, this, &Animation::next);
		connect(this, &Animation::onChangePlayingDirection, this, [this](PlayingDirection direction) {
			if (direction == PlayingDirection::Forward) {
				disconnect(&m_delayTimer, &QTimer::timeout, this, &Animation::prev);
				connect(&m_delayTimer, &QTimer::timeout, this, &Animation::next);
			} else {
				disconnect(&m_delayTimer, &QTimer::timeout, this, &Animation::next);
				connect(&m_delayTimer, &QTimer::timeout, this, &Animation::prev);
			}
		});
	}
	
	void Animation::setCurrentFrame(Frame * frame) {
		if (m_currentFrame == frame)
			return;
		
		m_currentFrame = frame;
		emit onChangeCurrentFrame(frame);
	}
	
}
