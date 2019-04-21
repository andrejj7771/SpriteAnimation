#include <QApplication>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <iostream>
#include <vector>

#include "Animation/AnimationController.h"
#include "Animation/Animation.h"
#include "Animation/Frame.h"
#include "Scene/Scene.h"

#include "Widgets/AnimationWidget/AnimationWidget.h"

int main(int argc, char **argv) {
	QApplication a(argc, argv);
	
	QMainWindow * window = new QMainWindow();
	window->setGeometry(100, 100, 250, 250);
	window->show();
	
	
	Animation::AnimationController * controller = new Animation::AnimationController();
	UI::AnimationWidget * widget = new UI::AnimationWidget(controller);
	window->setCentralWidget(widget);
	
	std::map<QString, int> anims =	{
										{"idle", 7},
										{"victory", 12},
										{"walking", 8}
									};
	
	for (auto pair : anims) {
		const QString & animName = pair.first;
		int frames = pair.second;
		
		Animation::Animation * animation = new Animation::Animation(150);
		animation->setName(animName);
		for (int i = 1; i <= frames; ++i) {
			const QString & fileName = "../data/frames/" + animName + "/" + QString::number(i) + ".png";
			QPixmap frameImage;
			if (!frameImage.load(fileName))
				return -1;
			
			Animation::Frame * frame = new Animation::Frame(frameImage);
			animation->appendFrame(frame);
		}
		controller->appendAnimation(animation);
	}
	
	return a.exec();
}
