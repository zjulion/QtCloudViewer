#ifndef LX_EAGLEVIEWER
#define LX_EAGLEVIEWER 
#include <QGLViewer/qglviewer.h>

#include <pcl/common/common_headers.h>
#include <pcl/common/transforms.h>
#include <pcl/point_types.h>   
#include <>
typedef pcl::PointXYZRGB ColorPoint;
typedef pcl::PointCloud<ColorPoint> ColorCloud;

#include <QTimer>
#include <mutex>

class Viewer : public QGLViewer 
{
	Q_OBJECT
public:
	Viewer(QWidget *parent = nullptr);
	// Open PCD cloud.
	void updateCloud(ColorCloud::Ptr input);


private:
	ColorCloud::Ptr inner_data;
	std::mutex		data_mutex;

	QTimer	*timer;

	// thread to start openning eagle camera
	int start_eagle();

	int point_size;

public:
	void redraw() {}

	void updatePointSize(int v) { point_size = v;}

private slots:
	void heart_beat();

protected:
	virtual void draw();
	virtual void init();
	virtual QString helpString() const;
};

#endif