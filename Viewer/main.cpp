#include "dialog.h"

#include <QApplication>

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

using namespace lanXin;
using namespace std;

int main(int argc, char **argv) 
{

	// load point loud
 
	// Read command lines arguments.
	QApplication application(argc, argv);

	// // Instantiate the viewer.
	// Viewer viewer;

	// viewer.setWindowTitle("simpleViewer");

	// // Make the viewer window visible on screen.
	// viewer.show();

	Dialog dialog;
	dialog.show();



	// Run main loop.
	return application.exec();
}
