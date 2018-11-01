#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_qtguiapplication3.h"
#include <QTreeWidgetItem>
#include <QWidget>
#include <QUrl>
#include <QDir>
#include <QNetworkReply>
#include <Qlabel>
#include <QTextEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QLayout>
#include <QSettings>
#include <INI.h>
#include "qftp.h"
#pragma execution_character_set("utf-8")


class QtGuiApplication3 : public QMainWindow
{
	Q_OBJECT

public:
	QtGuiApplication3(QWidget *parent = Q_NULLPTR);
	

	

	void initTreeWidget();

private:
	Ui::QtGuiApplication3Class ui;

private slots:
	void onSetLabelText(QTreeWidgetItem* item, int);
	void confim_clicked();
	
	//网络相关
	void ftpCommandStarted(int);
	void ftpCommandFinished(int, bool);
	void downloadfile();
	void uploadfile();
	
private:


private:
	qint64 fileDownloadSize;
	qint64 lastDownloadSize;
	QUrl url;
	QDir saveDir;
	INI<> *myini;

	QFile *file;//下载文件
	QFile *mfile;//上传文件
	QFtp *ftp;




	//QLabel *urlLabel;
	//QLabel *dirLoactionLabel;
	QLabel *downlaodInfoLabel;
	//QLabel *runningTipLabel;
	QLineEdit *urlTextEdit;
	QLineEdit *dirTextEdit;
	QTextEdit *downloadInfoTextEdit;
	QPushButton *runningTaskButton;
	QPushButton *uploadButton;
	//QPushButton *dirLocationButton;
	//QProgressBar *progressBar;
	//QGridLayout *mainLayout;
};
