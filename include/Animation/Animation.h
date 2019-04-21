#ifndef ANIMATION_H
#define ANIMATION_H

#include <QObject>
#include <QTimer>

namespace Animation {
	
	class Frame;
	
	enum class PlayingDirection : char {
		Forward		= 0,
		Backward	= 1
	};
	
	class Animation : public QObject {
		
		Q_OBJECT
		
		std::vector<Frame *> m_frames;
		Frame * m_currentFrame;
		
		int m_delay;
		bool m_isPlaying;
		bool m_isLoop;
		
		PlayingDirection m_direction;
		
		QString m_name;
		QTimer m_delayTimer;
		
	public:
		
		explicit Animation(int delay = 150);
		explicit Animation(const std::vector<Frame *> & m_frames, int delay = 150);
		explicit Animation(const Animation & anim);
		
		virtual ~Animation() override;
		
		void setName(const QString & name);
		inline const QString & getName() const;
		
		inline void setLoop(bool value);
		inline bool isLoop() const;
		
		inline size_t getNumFrames() const;
		inline const Frame * getCurrentFrame() const;
		
		void setPlayingDirection(PlayingDirection direction);
		inline PlayingDirection getPlayingDirection() const;
		
		bool appendFrame(Frame * frame);
		bool removeFrame(Frame * frame);
		inline bool removeFrame(size_t index);
		
		inline const Frame * getFrame(size_t index) const;
		inline const std::vector<Frame *> & getFrames() const;
		
		void setDelay(int delay);
		inline int getDelay() const;
		
		inline bool isPlaying() const;
		
		void play();
		void stop();
		void next();
		void prev();
		
		void clear();
		
	private:
		
		void initConnections();
		void setCurrentFrame(Frame * frame);
		
	signals:
		
		void onChangePlayingDirection (PlayingDirection direction);
		void onChangeCurrentFrame (Frame * frame);
		void onChangeName (const QString & name);
		void onChangeDelay (int delay);
		
		void onAppendFrame (Frame * frame);
		
		void onPlay();
		void onStop();
		
	};
	
	inline void Animation::setLoop(bool value) {
		if (m_isLoop == value)
			return;
		
		//TODO: emit signal
		m_isLoop = value;
	}
	
	inline bool Animation::isLoop() const {
		return m_isLoop;
	}
	
	inline const QString & Animation::getName() const {
		return m_name;
	}
	
	inline size_t Animation::getNumFrames() const {
		return m_frames.size();
	}
	
	inline const Frame * Animation::getCurrentFrame() const {
		return m_currentFrame;
	}
	
	inline PlayingDirection Animation::getPlayingDirection() const {
		return m_direction;
	}
	
	inline bool Animation::removeFrame(size_t index) {
		return index >= m_frames.size() ? false : removeFrame(m_frames.at(index));
	}
	
	inline const Frame * Animation::getFrame(size_t index) const {
		return index >= m_frames.size() ? nullptr : m_frames.at(index);
	}
	
	inline const std::vector<Frame *> & Animation::getFrames() const {
		return m_frames;
	}
	
	inline int Animation::getDelay() const {
		return m_delay;
	}
	
	inline bool Animation::isPlaying() const {
		return m_isPlaying;
	}
	
}
#endif // ANIMATION_H
