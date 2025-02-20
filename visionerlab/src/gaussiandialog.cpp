#include "gaussiandialog.h"
#include "ui_gaussiandialog.h"

GaussianDialog::GaussianDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GaussianDialog)
{
    m_qButtonVer = new QVBoxLayout;
    m_qSliderHor1 = new QHBoxLayout;
    m_qSliderHor2 = new QHBoxLayout;
    m_pLabel = new QLabel(this);
    m_pLabel->setText("Level");
    m_parent = parent;
    int nMin = 3;
    int nMax = 51;
    int nSingleStep = 2;
    // 微调框
    m_pSpinBox = new QSpinBox(this);
    m_pSpinBox->setMinimum(nMin);  // 最小值
    m_pSpinBox->setMaximum(nMax);  // 最大值
    m_pSpinBox->setSingleStep(nSingleStep);  // 步长


    // 滑动条
    m_pSlider = new QSlider(this);
    m_pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    m_pSlider->setMinimum(nMin);  // 最小值
    m_pSlider->setMaximum(nMax);  // 最大值
    m_pSlider->setSingleStep(nSingleStep);  // 步长
    //m_pSlider->setPageStep(nSingleStep);
    m_qSliderHor1->addWidget(m_pLabel);
    m_qSliderHor1->addWidget(m_pSpinBox);
    m_qSliderHor1->addWidget(m_pSlider);

    // 连接信号槽（相互改变）
    connect(m_pSpinBox, SIGNAL(valueChanged(int)), m_pSlider, SLOT(setValue(int)));
    connect(m_pSlider, SIGNAL(valueChanged(int)), m_pSpinBox, SLOT(setValue(int)));
    connect(m_pSpinBox, SIGNAL(valueChanged(int)), this, SLOT(ManualGaussianChangeSlot(int)));
    connect(m_pSlider, SIGNAL(valueChanged(int)), this, SLOT(ManualGaussianChangeSlot(int)));
    m_pSpinBox->setValue(21);
    button = new QDialogButtonBox(parent);
    button->addButton( "OK", QDialogButtonBox::YesRole);
    button->addButton( "NO", QDialogButtonBox::NoRole);
    connect(button, SIGNAL(accepted()), parent, SLOT(OKGaussianSliderSelectImg()));
    connect(button, SIGNAL(rejected()), parent, SLOT(CancelGaussianSliderSelectImg()));

    m_qSliderHor2->addWidget(button);
    m_qButtonVer->addLayout(m_qSliderHor1);
    m_qButtonVer->addLayout(m_qSliderHor2);
    this->setLayout(m_qButtonVer);
    ui->setupUi(this);

}

GaussianDialog::~GaussianDialog()
{

}
void GaussianDialog::ManualGaussianChangeSlot(int nValue)
{
    connect(this, SIGNAL(sendManualGaussianChange(int )), m_parent, SLOT(ManualGaussianChangeSlot(int)));
    emit sendManualGaussianChange(nValue);
    // 不加断开链接，执行第次越多，后面执行次数越多
    disconnect(this, 0, m_parent, 0);
}
void GaussianDialog::closeEvent(QCloseEvent *event)
{
    this->close();
}
