/*************************************** 
* 
* LanXin TECH, All Rights Reserverd. 
* Created at Wed Dec 11 16:59:58 2019
* Contributor: Ling Shi, Ph.D 
* Email: lshi@robvision.cn 
* 
***************************************/ 

#include "dialog.h"
#include "eagleviewer.h"


#include <QCheckBox>
#include <QSpinBox>
#include <QDebug>
#include <QPushButton>
#include <QFileDialog>
#include <QGroupBox>
#include <QScreen>
#include <QApplication>

#include <pcl/io/pcd_io.h>
#include <pcl/io/ply_io.h>


namespace lanXin {

Dialog::Dialog(QWidget *parent)
{
	// create ui	
	layout = new QHBoxLayout(this);
	setLayout(layout);
	setWindowTitle("Great Clouding");

	QScreen *screen= QApplication::primaryScreen ();
	QRect mm=screen->availableGeometry() ;
	int screen_width = mm.width();
	int screen_height = mm.height();
	// qDebug()<<screen_width<<screen_height; 
 
	if (screen_width > 2000)
	{
		resize(1600, 1200);
	}
	else
		resize(800, 600);
	
	setMinimumSize(320, 240);

	//setModal(false);
	viewer = new Viewer(this);
	viewer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	
	{

		auto left_layout = new QVBoxLayout;
		layout->addLayout(left_layout);
		left_layout->addWidget(viewer);

		// tool bar
		auto tools = new QHBoxLayout;
		left_layout->addLayout(tools);
		tools->addWidget(new QLabel("=="));

		auto axisCheck = new QCheckBox;
		//axisCheck->setChecked(showaxis == 1);
		connect(axisCheck, SIGNAL(toggled(bool)), viewer, SLOT(setAxisIsDrawn(bool)));		 
		axisCheck->setText(QStringLiteral("显示坐标轴"));
		tools->addWidget(axisCheck);

		// grid
		auto axisGrid = new QCheckBox;
		connect(axisGrid, SIGNAL(toggled(bool)), viewer, SLOT(setGridIsDrawn(bool)));	 
		axisGrid->setText(QStringLiteral("显示X-Y平面"));
		tools->addWidget(axisGrid);

		// fps
		auto axisFPS = new QCheckBox;
		connect(axisFPS, SIGNAL(toggled(bool)), viewer, SLOT(setFPSIsDisplayed(bool)));	 
		axisFPS->setText(QStringLiteral("显示帧率"));
		tools->addWidget(axisFPS);

		// point size
		{
			auto group1 = new QHBoxLayout;
			auto boxPointSize = new QSpinBox;
			connect(boxPointSize, SIGNAL(valueChanged(int)), this, SLOT(updatePointSize(int)));
			boxPointSize->setValue(2);
			group1->addWidget(new QLabel(QStringLiteral("点尺寸")));
			group1->addWidget(boxPointSize);
			tools->addLayout(group1);
		}
		tools->addWidget(new QLabel("==="));

		
	}

	{

		auto right_layout = new QVBoxLayout;
		layout->addLayout(right_layout);

		right_layout->addWidget(new QLabel("Add Widgets Here"));

		auto btn = new QPushButton(this);
		right_layout->addWidget(btn);
		btn->setText(QStringLiteral("载入点云"));
		connect(btn, SIGNAL(clicked()), this, SLOT(onbtnLoadCloudPressed()));

		btn = new QPushButton(this);
		right_layout->addWidget(btn);
		btn->setText(QStringLiteral("上色"));
		connect(btn, SIGNAL(clicked()), this, SLOT(onbtnColorPressed()));

		right_layout->addStretch();

		//// Eagle Part
		//auto group = new QGroupBox;
		//right_layout->addWidget(group);
		//group->setTitle("Eagle Fly");
		//group->setLayout(new QVBoxLayout);
		//group->layout()->addWidget(new QLabel("Closed"));
		//btn = new QPushButton(this);
		//btn->setText(QStringLiteral("打开相机"));
		//group->layout()->addWidget(btn);
		//// to do: add slots



		right_layout->addStretch();
	}


	#if 0
	QWidget wgt;
	wgt.setWindowTitle("Simple Cloud");

	auto layout = new QHBoxLayout(&wgt);
	wgt.setLayout(layout);

	auto viewer = new Viewer;

	if (argc >= 2)
	{
		auto filename = std::string(argv[1]);
		ColorCloud::Ptr cloud(new ColorCloud); 
		printf("filename: %s\n", filename.c_str());
		auto ret = pcl::io::loadPCDFile(filename, *cloud); 
		if(ret >= 0)
		{
			viewer->updateCloud(cloud);
		}
	}

	layout->addWidget(viewer);
	if(1)
	{
		auto label = new QLabel("Start");
		label->setStyleSheet("QLabel { color : blue; }");
		layout->addWidget(label);   		
	}


	wgt.show();


	#endif
 
}

void Dialog::updatePointSize(int ps)
{
	// qDebug() << "--- " << ps;
	viewer->updatePointSize(ps);
}

void Dialog::onbtnLoadCloudPressed()
{
	qDebug() << "ccc clicked.";
	QString file_name = QFileDialog::getOpenFileName(nullptr,
		tr("Load File (*.pcd, *.ply)"),
		"",
		tr("Point Cloud Files(*.pcd *.ply)"),
		0);

	qDebug() << "TRY to load: ";
	qDebug() << file_name;
	ColorCloud::Ptr cloud(new ColorCloud);

	int ret = -1;
	if (file_name.endsWith(".pcd"))
	{
		ret = pcl::io::loadPCDFile(file_name.toStdString(), *cloud);
	}
	else if (file_name.endsWith(".ply"))
	{
		ret = pcl::io::loadPLYFile(file_name.toStdString(), *cloud);
	}

	qDebug() << "total point size: " << cloud->points.size() <<". Ret:" << ret;
	
	// 如果点云过大，可能导致显示不流畅
	if (0 == ret)
	{
		viewer->updateCloud(cloud);
	}
/*
	if (0 == ret)
	{
		QFileInfo f(file_name);
		logx("Loading cloud %s successed.", f.baseName().constData());
		// render_widget->addPointCloud(cloud, f.baseName().toStdString().c_str());
		render_widget->updatePointCloud(cloud);
		logx("cloud size: %d by %d", cloud->width, cloud->height);
		if (cloud->isOrganized())
		{
			detect_im.create(cloud->height, cloud->width, CV_8UC3);
			int idx = 0;
			for (auto& vx : cloud->points)
			{
				detect_im.at<Vec3b>(idx++) = Vec3b(vx.b, vx.g, vx.r);
			}
			cv::Mat t = cv::Mat();
			showPictures(detect_im, t);
		}
	}
	else
	{
		QMessageBox::warning(this, QStringLiteral("警告"), QStringLiteral("载入点云文件失败，请重试"));
		putLog(QStringLiteral("载入点云文件失败，请重试！"), LOG_ORANGE);
	}
	*/
}

void Dialog::onbtnColorPressed()
{
	qDebug() << "上色啦";
}



} /* End of namespace lanXin */ 

