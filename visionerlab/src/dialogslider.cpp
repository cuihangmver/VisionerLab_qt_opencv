#include "dialogslider.h"
#include "ui_dialogslider.h"

DialogSlider::DialogSlider(QWidget *parent, int nDepth) :
    QDialog(parent),
    ui(new Ui::DialogSlider)
{
    ui->setupUi(this);
    m_parent = parent;
    int nMin = 0;
    int nMax = 0;
    int nSingleStep = 0;
    if(1 == nDepth)
    {
        nMin = 0;
        nMax = 255;
        nSingleStep = 1;
    }
    else if(2 == nDepth)
    {
        nMin = 0;
        nMax = 65535;
        nSingleStep = 1;
    }


    qButtonVer = new QVBoxLayout;
    qSliderHor1 = new QHBoxLayout;
    pLabel1 = new QLabel(this);
    pLabel1->setText("Level");
    // 微调框
    pSpinBox = new QSpinBox(this);
    pSpinBox->setMinimum(nMin);  // 最小值
    pSpinBox->setMaximum(nMax);  // 最大值
    pSpinBox->setSingleStep(nSingleStep);  // 步长

    // 滑动条
    pSlider = new QSlider(this);
    pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    pSlider->setMinimum(nMin);  // 最小值
    pSlider->setMaximum(nMax);  // 最大值
    pSlider->setSingleStep(nSingleStep);  // 步长
    qSliderHor1->addWidget(pLabel1);
    qSliderHor1->addWidget(pSpinBox);
    qSliderHor1->addWidget(pSlider);
    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));
    connect(pSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ManualThresholdChangeSlot(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), this, SLOT(ManualThresholdChangeSlot(int)));
    pSpinBox->setValue(125);

    qSliderHor2 = new QHBoxLayout;
    pLabel2 = new QLabel(this);
    pLabel2->setText("Negative");
    pCheckBox1 = new QCheckBox(this);
    qSliderHor2->addWidget(pLabel2);
    qSliderHor2->addWidget(pCheckBox1);

    qSliderHor3 = new QHBoxLayout;
    pLabel3 = new QLabel(this);
    pLabel3->setText("Preview");
    pCheckBox2 = new QCheckBox(this);
    qSliderHor3->addWidget(pLabel3);
    qSliderHor3->addWidget(pCheckBox2);


    qSliderHor4 = new QHBoxLayout;

    button = new QDialogButtonBox(parent);
    button->addButton( "OK", QDialogButtonBox::YesRole);
    button->addButton( "NO", QDialogButtonBox::NoRole);
    connect(button, SIGNAL(accepted()), parent, SLOT(OKThresholdSliderSelectImg()));
    connect(button, SIGNAL(rejected()), parent, SLOT(CancelThresholdSliderSelectImg()));

    qSliderHor4->addWidget(button);

    qButtonVer->addLayout(qSliderHor1);
    qButtonVer->addLayout(qSliderHor2);
    qButtonVer->addLayout(qSliderHor3);
    qButtonVer->addLayout(qSliderHor4);
    this->setLayout(qButtonVer);
}

DialogSlider::~DialogSlider()
{

}

void DialogSlider::ManualThresholdChangeSlot(int nValue)
{
    connect(this, SIGNAL(sendManualThresholdChange(int )), m_parent, SLOT(ManualThresholdChangeSlot(int)));
    emit sendManualThresholdChange(nValue);
    // 不加断开链接，执行第次越多，后面执行次数越多
    disconnect(this, 0, m_parent, 0);
}
void DialogSlider::closeEvent(QCloseEvent *event)
{
    this->close();
}
