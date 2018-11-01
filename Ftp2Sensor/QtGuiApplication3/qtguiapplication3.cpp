#include "qtguiapplication3.h"
#include "qstrANDstr.h"
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QFile>
#include <INI.h>
#include <string>
#include <QSettings>
#include "qdebug.h"
#include <QVBoxLayout>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QObject> 

#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QGridLayout>
#include <QFileDialog>

#include <QUrl>
#include <QDir>
#include <QFile>
#include <QTimer>
#include <QFileInfo>
#include <QMetaEnum>
#include <QNetworkAccessManager>
#include <String>






QtGuiApplication3::QtGuiApplication3(QWidget *parent)
	: QMainWindow(parent), fileDownloadSize(0),lastDownloadSize(0),file(Q_NULLPTR)
{
	ui.setupUi(this);

	ui.treeWidget->setHeaderLabel("MyTree");

	connect(ui.treeWidget, SIGNAL(itemClicked(QTreeWidgetItem*, int)), this, SLOT(onSetLabelText(QTreeWidgetItem*, int)));

	initTreeWidget();


	
	runningTaskButton = new QPushButton;
	runningTaskButton->setText("Download");
	connect(runningTaskButton, SIGNAL(clicked(bool)), SLOT(downloadfile()));

	uploadButton=new QPushButton;
	uploadButton->setText("Upload");
	connect(uploadButton, SIGNAL(clicked(bool)), SLOT(uploadfile()));

	

	
	downlaodInfoLabel = new QLabel;
	downlaodInfoLabel->setText(tr("Ftp Info:"));

	downloadInfoTextEdit = new QTextEdit;
	downloadInfoTextEdit->setReadOnly(true);
	downlaodInfoLabel->setBuddy(downloadInfoTextEdit);

	
	
	ui.mainLayout->setColumnStretch(0, 1);
	ui.mainLayout->setColumnStretch(1, 3);
	ui.mainLayout->setColumnStretch(2, 1);
	ui.mainLayout->setMargin(15);
	ui.mainLayout->setColumnMinimumWidth(2, 15);

	
	ui.mainLayout->addWidget(runningTaskButton, 0, 0);
	ui.mainLayout->addWidget(uploadButton, 0, 1);
	ui.mainLayout->addWidget(downlaodInfoLabel, 2, 0, 1, 1);
	ui.mainLayout->addWidget(downloadInfoTextEdit, 3, 0, 3, 3);


}


#pragma region initTreeWidget()初始化树形控件

void QtGuiApplication3::initTreeWidget() { 
	
	QString text;
	QSettings *iniTest;
	iniTest=new QSettings("Config.ini", QSettings::IniFormat);
	iniTest->setIniCodec("GB2312");

	myini = new INI<>("Config.ini", 1);
    QStringList groupList = iniTest->childGroups();

	for each(QString group in groupList)//遍历ini文件
	{
		iniTest->beginGroup(group); 
		text = str2qstr(group.toStdString());
		QTreeWidgetItem *tree1 = new QTreeWidgetItem(ui.treeWidget);
		tree1->setText(0, text);

		myini->select(group.toStdString());
		
		QStringList keyList = iniTest->childKeys();
		
		for each(QString key in keyList)
		{
			
			QTreeWidgetItem *child = new QTreeWidgetItem(tree1);
			//child->setText(0, tr(key.toStdString().c_str())+"="+ tr(iniTest->value(key).toString().section(' ',0,0).toStdString().c_str())); 旧方法
			
			child->setText(0, str2qstr(key.toStdString()) + "=" + str2qstr(myini->get(key.toStdString())).section(' ',0,0));
			
		}
		
		iniTest->endGroup();
	}

 

}

#pragma endregion

#pragma region clearall(QLayout *layout)清空布局
void clearall(QLayout *layout) {
	/*
	QLayoutItem *child;
	
	while (child = layout->layout()->takeAt(0)) {
		if (!(layout->layout()->takeAt(1))) {
			break;
		}
		layout->removeItem(child);
	}
	*/

	QLayoutItem *item;
	while ((item = layout->takeAt(0)) != 0) {
		//删除widget
		if (item->widget()) {
			delete item->widget();
			//item->widget()->deleteLater();
		}
		//删除子布局
		QLayout *cLayout = item->layout();
		if (cLayout) {
			clearall(cLayout);
		}
		delete item;
	}


}
#pragma endregion

#pragma region onSetLabelText(QTreeWidgetItem *item, int)点击树形控件展示列表

void QtGuiApplication3::onSetLabelText(QTreeWidgetItem *item, int)
{
	
	if (item->parent()) {
		item = item->parent();
	}

	clearall(ui.mylayout);//清空子布局
	
	QHBoxLayout *Hlayout=new QHBoxLayout();//创建一个新的水平布局
	ui.mylayout->insertLayout(0, Hlayout);
	
	
	
	
	QString SecName = item->text(0);

	
	QLabel *sec1 = new QLabel();
	sec1->setText(SecName);
	Hlayout->insertWidget(0, sec1);
	/*
	ui.mygrid->addWidget(sec1,0,0);
	ui.mygrid->addWidget(sec2, 0, 1);
	*/
	
	int num = item->childCount();
	QTreeWidgetItem *child = new QTreeWidgetItem();
	for (int i = 0; i < num; i++) {
		child = item->child(i);

		QLabel *child1 = new QLabel();
		QLineEdit *child2 = new QLineEdit();

		QString str = child->text(0);

		QString strkey = str.section('=',0,0);
		QString strval = str.section('=', 1, 1);

		child1->setText(strkey);
		child2->setText(strval);

		QHBoxLayout *Hlayout0 = new QHBoxLayout();//创建一个新的行
		ui.mylayout->addLayout(Hlayout0);
		Hlayout0->addWidget(child1);
		Hlayout0->addWidget(child2);
	}




	

	QHBoxLayout *Hlayout2 = new QHBoxLayout();//创建一个新的行
	ui.mylayout->addLayout(Hlayout2);

	QPushButton *confirmBtn = new QPushButton("修改");
	
	Hlayout2->addWidget(confirmBtn);
	connect(confirmBtn, SIGNAL(clicked()), this, SLOT(confim_clicked()));
	
	
}

#pragma endregion

#pragma region confim_clicked()修改配置文件
void QtGuiApplication3::confim_clicked() {
	QTreeWidgetItem *selectedItem = ui.treeWidget->selectedItems().first();
	
	if (selectedItem->parent()) {
		selectedItem = selectedItem->parent();
	}

	myini->select(selectedItem->text(0).toStdString());//new

	QLayoutItem *item;
	QLabel *label0=new QLabel();
	QLineEdit *textbox = new QLineEdit();

	//int num = 0;
	int i = 1;
	while (ui.mylayout->itemAt(i+1)!=0)
	{
		item = ui.mylayout->itemAt(i);
		QLayout *childLayout = item->layout();

		label0 = qobject_cast<QLabel *>(childLayout->itemAt(0)->widget());
		string aa = label0->text().toStdString();
		textbox = qobject_cast<QLineEdit *>(childLayout->itemAt(1)->widget());


		selectedItem->child(i-1)->setText(0, label0->text() + "=" + textbox->text());

		myini->set(qstr2str(label0->text()), qstr2str(textbox->text())); 


		i++;
		
	}
	/*
	while ((item = ui.mylayout->takeAt(0)) != 0) {
	
		QLayout *childLayout = item->layout();

		if (childLayout&&childLayout->itemAt(1)) {
			
			label0 = qobject_cast<QLabel *>(childLayout->itemAt(0)->widget());
			string aa = label0->text().toStdString();
			textbox = qobject_cast<QLineEdit *>(childLayout->itemAt(1)->widget());
			
			
			selectedItem->child(num)->setText(0,label0->text()+"="+textbox->text());
			
			myini->set(qstr2str(label0->text()), qstr2str(textbox->text())); //new


			num++;
		}
		
	}
	*/
	myini->save("Config.ini");
	
	
}

#pragma endregion

#pragma region 网络操作
//下载文件
void QtGuiApplication3::downloadfile() {
	file = new QFile("E:/QtProject/Ftp2Sensor/QtGuiApplication3/Config.ini");//下载到所在的文件
	if (!file->open(QIODevice::WriteOnly))
	{
		delete file;
		return;
	}
	ftp = new QFtp(this);
	ftp->connectToHost("192.168.1.136", 21); //连接到服务器
	ftp->login("ZhuHai", "ZhuHai");   //登录
	ftp->cd("/");   //跳转目录
	ftp->get("Config.ini", file); //下载文件
	ftp->close();   //关闭连接
	
	// 当每条命令开始执行时发出相应的信号
	connect(ftp, SIGNAL(commandStarted(int)),
		this, SLOT(ftpCommandStarted(int)));

	// 当每条命令执行结束时发出相应的信号
	connect(ftp, SIGNAL(commandFinished(int, bool)),
		this, SLOT(ftpCommandFinished(int, bool)));

}
//上传文件
void QtGuiApplication3::uploadfile() {
	mfile = new QFile("E:/QtProject/Ftp2Sensor/QtGuiApplication3/Config.ini", this);//上传的文件
	if (!mfile->open(QIODevice::ReadOnly)) {
		downloadInfoTextEdit->append("无法找到上传文件");
		return;
	}

	ftp = new QFtp(this);
	ftp->connectToHost("192.168.1.136", 21); //连接到服务器
	ftp->login("ZhuHai", "ZhuHai");   //登录
	ftp->cd("/");   //跳转目录
	ftp->put(mfile, "Config.ini");  //上传文件
	ftp->close();   //关闭连接

	// 当每条命令开始执行时发出相应的信号
	connect(ftp, SIGNAL(commandStarted(int)),
		this, SLOT(ftpCommandStarted(int)));

	// 当每条命令执行结束时发出相应的信号
	connect(ftp, SIGNAL(commandFinished(int, bool)),
		this, SLOT(ftpCommandFinished(int, bool)));

}
//接收返回开始指令
void QtGuiApplication3::ftpCommandStarted(int)
{
	if (ftp->currentCommand() == QFtp::ConnectToHost) {
		//ui.label->setText(tr("正在连接到服务器..."));
		downloadInfoTextEdit->append("connecting...");
	}
	if (ftp->currentCommand() == QFtp::Login) {
		//ui.label->setText(tr("正在登录..."));
		downloadInfoTextEdit->append("logining...");
	}
	if (ftp->currentCommand() == QFtp::Get) {
		//ui.label->setText(tr("正在下载..."));
		downloadInfoTextEdit->append("downloading...");
	}
	if (ftp->currentCommand() == QFtp::Put) {
		//ui.label->setText(tr("正在上传..."));
		downloadInfoTextEdit->append("uploading...");
	}
	/*
	else if (ftp->currentCommand() == QFtp::Close) {
		//ui.label->setText(tr("正在关闭连接..."));
		downloadInfoTextEdit->append("closing...");
	}
	*/
}
//接收返回结束指令
void QtGuiApplication3::ftpCommandFinished(int, bool error)
{
	if (ftp->currentCommand() == QFtp::ConnectToHost) {
		if (error) {
			//ui.label->setText(tr("连接服务器出现错误：%1").arg(ftp->errorString()));
			downloadInfoTextEdit->append("connect failed");
		}
		else {
			//ui.label->setText(tr("连接到服务器成功"));
			downloadInfoTextEdit->append("connect success");
		}
	}
	if (ftp->currentCommand() == QFtp::Login) {
		if (error) {
			//ui.label->setText(tr("登录出现错误：%1").arg(ftp->errorString()));
			downloadInfoTextEdit->append("login failed");
		}
		else {
			//ui.label->setText(tr("登录成功"));
			downloadInfoTextEdit->append("login success");
		}
	}
	if (ftp->currentCommand() == QFtp::Get) {
		if (error) {
			//ui.label->setText(tr("download error").arg(ftp->errorString()));
			downloadInfoTextEdit->append("download error"+ ftp->errorString());
		}
		else {
			//ui.label->setText(tr("download success"));
			downloadInfoTextEdit->append("download success");
			file->close();
			ui.treeWidget->clear();
			initTreeWidget();
			clearall(ui.mylayout);
		}
	}
	if (ftp->currentCommand() == QFtp::Put) {
		if (error) {
			//ui.label->setText(tr("upload error").arg(ftp->errorString()));
			downloadInfoTextEdit->append("upload error"+ ftp->errorString());
		}
		else {
			//ui.label->setText(tr("upload success"));
			downloadInfoTextEdit->append("upload success");
			mfile->close();
		}
	}
	/*
	else if (ftp->currentCommand() == QFtp::Close) {
		//ui.label->setText(tr("close connection"));
		//downloadInfoTextEdit->append("close connection");
		//initTreeWidget();
	}
	*/
	
}


#pragma endregion


