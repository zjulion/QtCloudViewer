/*************************************** 
* 
* LanXin TECH, All Rights Reserverd. 
* Created at Wed Dec 11 16:59:58 2019
* Contributor: Ling Shi, Ph.D 
* Email: lshi@robvision.cn 
* 
***************************************/ 

#ifndef LX_DIALOG_H
#define LX_DIALOG_H 

#include <QDialog>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCheckBox>

class Viewer;

namespace lanXin {


class Dialog : public QDialog
{
	Q_OBJECT
	
public:
	Dialog(QWidget *parent = nullptr);

private slots:
	void updatePointSize(int ps);

	void onbtnLoadCloudPressed();

	// 上色
	void onbtnColorPressed();

protected:
	// the main layout
	class QHBoxLayout* 			layout;
	class Viewer*				viewer;
	
};





} /* End of namespace lanXin */ 


#endif