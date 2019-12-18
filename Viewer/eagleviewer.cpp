#include "eagleviewer.h"


#include <vector>
#include <string>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <thread>

#include <thread> 
#include <memory>

using namespace std;

// Draws a helix

Viewer::Viewer(QWidget *parent) : QGLViewer(parent)
    , point_size(2)
{

    inner_data = ColorCloud::Ptr(new ColorCloud);

	// Create a helix cloud;        glColor3f(1.0f, 1.0f, 1.0f);
	const float delta = 0;
	for (float angle = delta; angle <= M_PI * 40 + delta; angle += 0.02 * M_PI)
	{
		ColorPoint vx;
		const float r = 1 + 0.021 * angle;
		vx.x = 0.1*cos(angle) * r;
		vx.y = 0.1*sin(angle) * r;
		vx.z = 0.006 * angle;

		vx.r = vx.g = vx.b = 255;	
		inner_data->points.push_back(vx);
	}
	inner_data->width = inner_data->points.size();
	inner_data->height = 1;
	inner_data->is_dense = true;


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(heart_beat()));
    timer->start(100);
}

void Viewer::updateCloud(ColorCloud::Ptr input)
{
 
    if (input.get() && !input->points.empty())
    {
        PCL_WARN("Point cloud update -- %d\n", (int)input->points.size());
        *inner_data = *input;

        update();
    }
}

void Viewer::draw() 
{
    float x,y,z;  
    glPointSize(point_size * 1.f);   
    glBegin(GL_POINTS);     


    // printf("point size: %d\n", inner_data->points.size());
    if (inner_data->points.size() > 0)
    {

        std::lock_guard<std::mutex> lk(data_mutex);
        for(auto& vx : inner_data->points)
        {
            glColor3f(1. * vx.r/255, 1. * vx.g/255, 1. * vx.b / 255);
            glVertex3f(vx.x, vx.y, vx.z);
        }
    }
    else
    {

    }
    glEnd();  


	//// -- test axis
	//glPushMatrix();
	//glTranslatef(0.2f, 0.2f, 0.1f);
	//drawAxis();
	//glPopMatrix();
}

void Viewer::init() 
{
    // Restore previous viewer state.
    restoreStateFromFile();
 
    glDisable(GL_LIGHTING);
    // Opens help window
    //help();

    // build UI
}

void Viewer::heart_beat()
{
    update();
}

/**/
QString Viewer::helpString() const 
{
    QString text("<h2>S i m p l e V i e w e r</h2>");
    text += "Use the mouse to move the camera around the object. ";
    text += "You can respectively revolve around, zoom and translate with the "
          "three mouse buttons. ";
    text += "Left and middle buttons pressed together rotate around the camera "
          "view direction axis<br><br>";
    text += "Pressing <b>Alt</b> and one of the function keys "
          "(<b>F1</b>..<b>F12</b>) defines a camera keyFrame. ";
    text += "Simply press the function key again to restore it. Several "
          "keyFrames define a ";
    text += "camera path. Paths are saved when you quit the application and "
          "restored at next start.<br><br>";
    text +=
      "Press <b>F</b> to display the frame rate, <b>A</b> for the world axis, ";
    text += "<b>Alt+Return</b> for full screen mode and <b>Control+S</b> to save "
          "a snapshot. ";
    text += "See the <b>Keyboard</b> tab in this window for a complete shortcut "
          "list.<br><br>";
    text += "Double clicks automates single click actions: A left button double "
          "click aligns the closer axis with the camera (if close enough). ";
    text += "A middle button double click fits the zoom of the camera and the "
          "right button re-centers the scene.<br><br>";
    text += "A left button double click while holding right button pressed "
          "defines the camera <i>Revolve Around Point</i>. ";
    text += "See the <b>Mouse</b> tab and the documentation web pages for "
          "details.<br><br>";
    text += "Press <b>Escape</b> to exit the viewer.";
    return text;
}
