#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>

namespace Ui {
class AnimationWidget;
}

namespace Animation {
	class AnimationController;
}

namespace UI {

class AnimationWidget : public QWidget
{
	Q_OBJECT
	
	Animation::AnimationController * m_controller;
	
public:
	explicit AnimationWidget(Animation::AnimationController * controller, QWidget * parent = nullptr);
	~AnimationWidget();
	
	
private:
	
	Ui::AnimationWidget *ui;
	
	void initControllerConnection();
	
};

}

#endif // ANIMATIONWIDGET_H
