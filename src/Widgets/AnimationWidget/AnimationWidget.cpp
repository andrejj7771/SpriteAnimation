#include "Widgets/AnimationWidget/AnimationWidget.h"
#include "ui_AnimationWidget.h"

#include "Animation/AnimationController.h"
#include "Animation/Animation.h"

#include "Scene/Scene.h"

#include <QComboBox>

namespace UI {
	
	AnimationWidget::AnimationWidget(Animation::AnimationController * controller, QWidget *parent) :
		QWidget(parent),
		ui(new Ui::AnimationWidget)
	{
		ui->setupUi(this);
		
		if (!controller) {
			printf_s("E:%s -> AnimationContoller is nullptr. Abort.\n", __FUNCTION__);
			abort();
		}
		
		m_controller = controller;
		m_controller->getScene()->show();
		
		ui->SceneFrame->setLayout(new QVBoxLayout());
		ui->SceneFrame->layout()->addWidget(m_controller->getScene());
		
		ui->DirectionBox->addItem("Normal");
		ui->DirectionBox->addItem("Reverse");
		ui->DelaySpin->setMinimum(0);
		ui->DelaySpin->setMaximum(1000);
		
		initControllerConnection();
	}
	
	AnimationWidget::~AnimationWidget() {
		delete ui;
	}
	
	void AnimationWidget::initControllerConnection() {
		connect(m_controller, &Animation::AnimationController::onAppendAnimation, this, [this](Animation::Animation * animation){
			ui->AnimationList->addItem(animation->getName());
		});
		
		connect(m_controller, &Animation::AnimationController::onChangeCurrentAnimation, this, [this](Animation::Animation * animation){
			ui->DelaySpin->setValue(animation->getDelay());
			ui->DirectionBox->setCurrentIndex(static_cast<int>(animation->getPlayingDirection()));
			ui->LoopCheckBox->setChecked(animation->isLoop());
			
			connect(animation, &Animation::Animation::onStop, this, [this](){
				ui->PlayButton->setText("Play");
			});
		});
	
		connect(ui->PrevButton, &QPushButton::pressed, this, [this](){
			if (!m_controller || !m_controller->getCurrentAnimation())
				return;
			
			Animation::Animation * animation = m_controller->getCurrentAnimation();
			animation->prev();
		});
		
		connect(ui->NextButton, &QPushButton::pressed, this, [this](){
			if (!m_controller || !m_controller->getCurrentAnimation())
				return;
			
			Animation::Animation * animation = m_controller->getCurrentAnimation();
			animation->next();
		});
		
		connect(ui->PlayButton, &QPushButton::pressed, this, [this](){
			if (!m_controller || !m_controller->getCurrentAnimation())
				return;
			
			Animation::Animation * animation = m_controller->getCurrentAnimation();
			if (animation->isPlaying()) {
				ui->PlayButton->setText("Play");
				animation->stop();
			} else {
				ui->PlayButton->setText("Stop");
				animation->play();
			}
		});
		
		connect(ui->LoopCheckBox, &QCheckBox::clicked, this, [this](bool value){
			m_controller->getCurrentAnimation()->setLoop(value);
		});
		
		connect(ui->DelaySpin, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, [this](int value){
			m_controller->getCurrentAnimation()->setDelay(value);
		});
		
		connect(ui->DirectionBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int index){
			Animation::Animation * animation = m_controller->getCurrentAnimation();
			animation->setPlayingDirection(static_cast<Animation::PlayingDirection>(index));
		});
		
		connect(ui->AnimationList, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, [this](int index){
			Animation::Animation * animation = m_controller->getAnimation(size_t(index));
			m_controller->setCurrentAnimation(animation);
		});
	}
	
}
