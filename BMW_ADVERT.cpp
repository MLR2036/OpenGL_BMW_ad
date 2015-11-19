// BMW_ADVERT.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include "glut.h"
#include <math.h>
#include <Windows.h>

int frame=0;
int no_points=46;


class BMW{
public:  float x,y,z;
};

BMW i8[46]={/*boot of car*/{74.94,298.56,0}, {136.41,310.19,0}, {177.95,320.16,0},
{217.83,333.45,0}, {266.01,340.09,0}, {307.54,350.06,0}, {375.66,358.37,0},
/*mid top of car*/{428.360,360.03,0}, {501.93,355.05,0}, {556.76,338.43,0}, 
/*mid windscreen*/{604.94,320.16,0}, {653.12,300.22,0}, {701.31,291.91,0}, 
{744.5,291.91,0}, {786.04,283.61,0},/*mid bonnet*/{829.24,271.97,0},{865.79,255.36,0},
{908.99,232.1,0}, /* front reg plate*/{923.94,188.9,0}, {908.99,135.74,0}, 
{887.39,115.8,0}, /*front wheel frame bottom right*/{867.45,120.78,0},
{870.77,173.95,0}, {860.8,212.16,0}, {837.54,237.08,0},
/*top mid of front wheel frame*/{794.35,248.71,0}, {754.47,242.07,0}, {709.61,217.15,0},
{696.32,165.64,0}, /*bottom left of front wheel frame*/ {696.32,117.46,0},
{551.78,117.46,0}, /* mid of bottom of car */{398.92,117.46,0}, {305.88,117.46,0},
/*bottom right of back wheel frame*/ {232.78,119.48,0}, {244.41,163.98,0}, {232.78,202.19,0},
{207.86,230.44,0}, /*top mid of back wheel frame*/{161.34,245.39,0}, {116.48,233.76,0}, {84.91,187.24,0},
{76.6,159,0}, /*bottom left of back wheel frame*/{84.91, 117.46,0}, {56.67,117.46,0},
{28.42,149.03,0}, /*back reg plate*/{18.45,190.56,0}, {21.77,242.07,0}};

BMW bed[46]={/*bottom left of mattress */{132.82,178.21,0},{230.5,196.65,0}, 
{297.44,211.68,0},/*mid of left side of mattress*/{356.87,225.34,0}, 
{398.9,234.86,0},/*top of left side of mattress*/ {449.77,245.15,0},{451.36,321.16,0},
/*top left of head board*/{453.06,370.24,0}, {513.98,392.24,0}, /*mid of top of head board*/{578.28,399.01},
{640.9,395.62,0}, {695.05,382.09,0},/*right top of head board*/ {750.89,365.16,0}, {749.2,277.17,0},
/*top right of mattress*/ {747.51,234.86,0}, /*top right of bottom of devan*/{745.87,137.42,0}, {719.13,125.96,0},
{682.21,111.96,0},/*mid bottom of devan*/{627.46,90.31,0}, {585.45,73.76,0}, {585.45,73.76,0}, {519.25,45.75,0}, 
/*bottom right of bottom of devan*/{475.06, 26.71,0}, /*bottom right of top of devan*/{471.67,99.48,0},
/*left mid of top of devan */{568.13,133.32,0}, /*top right of top of devan*/{745.82,199.32,0}, 
/*bottom right of bottom of mattress*/{471.67,99.48,0}, /*bottom right of top of mattress*/ {469.98,141.78,0}, 
/*top left of top of mattress*/{747.51,233.17,0}, {630.74,195.94,0}, /*left mid of top of mattress */{581.67,179.01,0},
/*bottom left of top of mattress*/{469.92,141.72,0}, {471.37,114.54,0}, /*bottom right of bottom of devan*/{473.36,25.02,0},
{389.61,35.26,0}, {318.09,45.75,0}, /*mid bottom of dvan*/{255.11,54.9,0}, {189.5,66.12,0}, 
/*bottom left of bottom of devan*/{132.94,74.05,0}, /*top left of top of devan*/{132.56,138.1,0},
/*bottom right of bottom of mattress*/{471.67,99.48,0}, /*bottom left of bottom of mattress*/{132.56,137.91,0}, 
{132.82,178.21,0}, /*top right of top of mattress*/{468.89,141.33,0}, {415.61,147.47,0},
/*top mid of bottom of mattress*/ {284.46,161.13,0}};




BMW dis[46];
BMW tweenShape[46];
float proportion = 0.0;
int mode;

float sx=1.0, sy=1.0;
float sx1=1.0, sy1=1.0;
float translate = 0.00;// speed control for roadlines
float translate1 = 1440.00;// speed control for roadlines1
float theta = 0.0; // speed control for hub caps
float theta1 = 0.0; // speed control for monuments


void tween(BMW shape1[46], BMW shape2[46], int xPoints, double proportion, BMW tweenShape[46])
{
	for(int i = 0; i < xPoints; i++)
	{
		//get points of shape1
		double shape1X = shape1[i].x;
		double shape1Y = shape1[i].y;
		double shape1Z = shape1[i].z;

		//get points of shape2
		double shape2X = shape2[i].x;
		double shape2Y = shape2[i].y;
		double shape2Z = shape2[i].z;

	 // get the difference between source and destination
 	    double differenceX = (shape2X - shape1X);
 	    double differenceY = (shape2Y - shape1Y);
		double differenceZ = (shape2Z - shape1Z);

	// tween point is source position + proportion
    // of distance between source and destination
 	    double tweenX = shape1X + ( differenceX * proportion );
 	    double tweenY = shape1Y + ( differenceY * proportion );
		double tweenZ = shape1Z + ( differenceZ * proportion );

	// create point with tween co-ordinates in tween array
		tweenShape[i].x = tweenX;
		tweenShape[i].y = tweenY;
		tweenShape[i].z = tweenZ;

	}
}
void drawCircle(float x_centre, float y_centre, float r,float R,float G,float B)
		{
	int x, y;
	int i;
	int num = 40; // number of lines to be generated to draw the circle
	
		//glColor3f (1.0, 1.0, 1.0);//line color
	//glClearColor(rand()%255/255.0, rand()%255/255.0, rand()%255/255.0,rand()%255/255.0);
		glColor3f(R, G, B);
		
		glBegin(GL_LINE_LOOP);
		 
				for (i=1; i<=num; i++)
				{
					
					x = x_centre + r *cos(i*2.0*3.14/num);
					y = y_centre + r *sin(i*2.0*3.14/num);
					glVertex2i(x,y);
				}

				
		      
		glEnd();
		}

void drawPCircle(float x_centre, float y_centre, float r)
		{
	int x, y;
	int i;
	int num = 40; // number of lines to be generated to draw the circle
	
		//glColor3f (1.0, 1.0, 1.0);//line color
	//glClearColor(rand()%255/255.0, rand()%255/255.0, rand()%255/255.0,rand()%255/255.0);
		
		
		glBegin(GL_POLYGON);
		 
				for (i=1; i<=num; i++)
				{
					
					x = x_centre + r *cos(i*2.0*3.14/num);
					y = y_centre + r *sin(i*2.0*3.14/num);
					glVertex2i(x,y);
				}

				
		      
		glEnd();
		}

void renderSpacedBitmapString(float x, float y, void *font, char *string) {
  char *c;
  int x1=x;
  for (c=string; *c != '\0'; c++) {
	glRasterPos2f(x1,y);
    	glutBitmapCharacter(font, *c);
	x1 = x1 + glutBitmapWidth(font,*c);
  }
}


	


void person()
{
	glColor3f(0.0, 0.0,0.0);
	drawPCircle(475.0,240,25);
	
	glColor3f(1.0,1.0,1.0);
	glLineWidth(2.0);
	glBegin(GL_LINES);	
	glVertex3f(465.0,245.0,0.0);//left eye
	glVertex3f(468.0,245.0,0.0);

	glVertex3f(485.0,245.0,0.0);//right eye
	glVertex3f(488.0,245.0,00);	
	
	glVertex3f(475.0,237.0,0.0);//nose
	glVertex3f(478.0,237.0,0.0);

	glVertex3f(466.0,230.0,0.0);//mouth
	glVertex3f(486.0,230.0,0.0);

	 glEnd();

	

}


void bedColor()
{
	glColor3f(1.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(745.87,137.42,0);//devan right
	glVertex3f(745.87,199.32,0);
	glVertex3f(470.56,125.1,0);
	glVertex3f(470.56,25.05,0);
	
    glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(132.94,74.05,0);//devan bottom
	glVertex3f(132.56,138.1,0);
	glVertex3f(470.56,125.1,0);
	glVertex3f(470.56,25.05,0);
	
    glEnd();

	glColor3f(0.0,0.5,1.0);
	glBegin(GL_POLYGON);
		glVertex3f(453.02,242.67,0.0);//bedheadleft
		glVertex3f(450.81,370.06,0.0);
		glVertex3f(518.38,391.78,0.0);
		glVertex3f(536.11,247.1,0.0);

	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(515.06,392.24,0.0);//bedheadmidleft
		glVertex3f(600.00,400.00,0.0);
		glVertex3f(638.38,238.35,0.0);
		glVertex3f(528.21,245.99,0.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(600.0,400.0,0.0);//bedheadmidright
		glVertex3f(635.13,239.21,0.0);
		glVertex3f(742.15,232.89,0.0);
		glVertex3f(638.34,393.32,0.0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(635.23,395.54,0.0);//bedheadright
		glVertex3f(751.01,364.52,0.0);
		glVertex3f(745.04,228.67,0.0);
	glEnd();



}

void sheet()
{
	glColor3f(0.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(456.0,250.0,0.0);
	glVertex3f(750.0,233.0,0.0);
	glVertex3f(554.0,164.0,0.0);
	glVertex3f(406.0,228.0,0.0);
    glEnd();

	glColor3f(0.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(752.33,233.62,0.0);
	glVertex3f(752.33,197.71,0.0);
	glVertex3f(472.01,97.23,0.0);
	glVertex3f(472.01,142.43,0.0);
    glEnd();

	glColor3f(0.0,1.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(130.82,178.21,0);
	glVertex3f(472.98,141.78,0);
	glVertex3f(472.67,96.48,0);
	glVertex3f(130.56,134.91,0);
    glEnd();
}

void pillow()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(459.0,272.0,0.0);
	glVertex3f(564.0,261.0,0.0);
	glVertex3f(543.0,222.0,0.0);
	glVertex3f(437.0,240.0,0.0);
    glEnd();

	glBegin(GL_POLYGON);
	glVertex3f(577.09,243.78,0.0);
	glVertex3f(562.69,260.0,0.0);
	glVertex3f(540.0,220.73,0.0);
	glEnd();



}

void covers()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(390.9,229.86,0.0);
	glVertex3f(628.74,194.94,0.0);
	glVertex3f(469.98,141.78,0.0);
	glVertex3f(125.82,178.21,0.0);
	glEnd();

}

void body()
{
	glColor3f(0.0,0.0,1.0);
	glBegin(GL_POLYGON);
	glVertex3f(458.22,199.32,0.0);
	glVertex3f(437.88,238.82,0.0);
	glVertex3f(395.6,243.85,0.0);
	glVertex3f(269.43,222.37,0.0);
	glVertex3f(213.78,171.6,0.0);
glEnd();
}

void dreamBubble()
{
	glLineWidth(10.0);//line width
	glColor3f(1.0, 1.0, 1.0);//colour
	glBegin(GL_LINE_LOOP);
	glVertex3f(323.42,322.12,0.0);
	glVertex3f(259.17,314.37,0.0);
	glVertex3f(195.57,313.29,0.0);
	glVertex3f(162.79,340.96,0.0);
	glVertex3f(147.29,380.84,0.0);
	glVertex3f(153.93,434.01,0.0);
	glVertex3f(191.03,472.5,0.0);
	glVertex3f(242.55,491.61,0.0);
	glVertex3f(286.86,497.15,0.0);
	glVertex3f(333.39,497.15,0.0);
	glVertex3f(385.45,498.26,0.0);
	glVertex3f(419.79,481.64,0.0);
	glVertex3f(443.05,440.65,0.0);
	glVertex3f(445.27,405.21,0.0);
	glVertex3f(417.58,369.76,0.0);
	glVertex3f(389.88,347.6,0.0);
glEnd();
}


void carColour()
{
	glColor3f(0.753, 0.753, 0.753);
	glBegin(GL_POLYGON);
		glVertex3f(217.83,333.45,0);
		glVertex3f(709.61,248.15,0);
		glVertex3f(709.61,217.15,0);
		glVertex3f(232.78,202.19,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(217.83,333.45,0);
		glVertex3f(207.86,230.44,0);
		glVertex3f(232.78,202.19,0);		
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(177.95,320.16,0);
		glVertex3f(260.12,311.85,0);
		glVertex3f(307.54,350.06,0);		
	glEnd();

	

	glColor3f(0.0, 0.753, 0.753);
	glBegin(GL_POLYGON);
		glVertex3f(198.66,243.95,0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(289.27,343.50,0);//window	
		glVertex3f(362.37,358.50,0);		
		glVertex3f(490.3,356.71,0);
		glColor3f(0.0, 0.0, 0.0);
		glVertex3f(556.76,338.43,0);
		glVertex3f(634.85,310.70,0);		
		glVertex3f(723.68,248.93,0);		
	glEnd();

	glColor3f(0.753, 0.753, 0.753);
	

	
	glBegin(GL_POLYGON);
		glVertex3f(76.6,159.0,0);
		glVertex3f(84.91,117.46,0);
		glVertex3f(56.67,117.46,0);
		glVertex3f(28.42,149.03,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(45.04,268.65,0);
		glVertex3f(76.6,159.0,0);
		glVertex3f(28.42,149.03,0);
		glVertex3f(18.45,190.56,0);
		glColor3f(1.0,0.0,0.3);
		glVertex3f(21.77,242.07,0);
	glEnd();

	glColor3f(0.753, 0.753, 0.753);
	glBegin(GL_POLYGON);
		glVertex3f(45.04,268.65,0);
		glVertex3f(76.6,159.0,0);
		glVertex3f(84.91,187.24,0);
		glVertex3f(116.48,233.76,0);
		glVertex3f(74.94,298.56,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(74.94,298.56,0);
		glVertex3f(116.48,233.76,0);
		glVertex3f(161.34,245.39,0);
		glVertex3f(136.41,310.19,0);		
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(136.41,310.19,0);
		glVertex3f(116.48,233.76,0);
		glVertex3f(161.34,245.39,0);
		glVertex3f(177.95,320.16,0);		
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(177.95,320.16,0);
		glVertex3f(161.34,245.39,0);
		glVertex3f(207.86,230.44,0);
		glVertex3f(217.83,333.45,0);		
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(244.41,163.98,0);
		glVertex3f(232.78,112.48,0);
		glVertex3f(696.32,117.46,0);
		glVertex3f(696.32,165.64,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(244.41,163.98,0);
		glVertex3f(696.32,165.64,0);		
		glVertex3f(709.61,217.15,0);
		glVertex3f(232.78,202.19,0);
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(653.12,300.22,0);
		glVertex3f(709.61,217.15,0);
		glVertex3f(754.47,242.07,0);
		glVertex3f(744.5,291.91,0);		
	glEnd();

	glBegin(GL_POLYGON);
		glVertex3f(744.5,291.91,0);
		glVertex3f(754.47,242.07,0);
		glVertex3f(786.04,283.61,0);				
	glEnd();


	glBegin(GL_POLYGON);		
		glVertex3f(754.47,242.07,0);
		glVertex3f(744.5,291.91,0);
		glVertex3f(794.35,248.71,0);
		glVertex3f(786.04,283.61,0);
	glEnd();

	glBegin(GL_POLYGON);		
		glVertex3f(794.35,248.71,0);
		glVertex3f(786.04,283.61,0);
		glVertex3f(829.24,271.97,0);
		glVertex3f(837.54,237.08,0);
	glEnd();

	glBegin(GL_POLYGON);		
		glVertex3f(829.24,271.97,0);
		glVertex3f(837.54,237.08,0);
		glVertex3f(860.8,212.16,0);
		glVertex3f(865.79,255.36,0);
	glEnd();

	glBegin(GL_POLYGON);		
		glVertex3f(860.8,212.16,0);
		glVertex3f(865.79,255.36,0);
		glColor3f(1.0,1.0,1.0);//headlight
		glVertex3f(908.99,232.1,0);		
		glVertex3f(923.94,188.9,0);
		glColor3f(0.753,0.753,0.753);
		glVertex3f(870.77,173.95,0);		
	glEnd();

	glColor3f(0.753,0.753,0.753);
	glBegin(GL_POLYGON);		
		glVertex3f(923.94,188.9,0);
		glVertex3f(870.77,173.95,0);
		glVertex3f(867.45,120.78,0);		
		glVertex3f(887.39,115.8,0);		
		glVertex3f(908.99,135.1,0);
	glEnd();



}

void frontHubCap()
{
	glLineWidth(10.0);
	glColor3f(0.753, 0.753, 0.753);
	
	//lines in front HubCap
	glBegin(GL_LINES);	
	glVertex3f(710.0,160.0,0.0);
	glVertex3f(857.0,160.0,0.0);
	glVertex3f(784.0,87.0,0.0);
	glVertex3f(784.0,233.0,0.0);
	glVertex3f(842.5,110.98,0.0);
	glVertex3f(722.2,205.04,0.0);
	glVertex3f(837.5,210.67,0.0);
	glVertex3f(730.5,105.85,0.0);	
	glEnd();

	

}

void backHubCap()
{
	glColor3f(0.753, 0.753, 0.753);
	glBegin(GL_LINES);
	//lines in back HubCap
	glVertex3f(92.0,160.0,0.0);
	glVertex3f(229.0,160.0,0.0);
	glVertex3f(161.0,90.5,0.0);
	glVertex3f(161.0,227.5,0.0);
	glVertex3f(210.5,110.98,0.0);
	glVertex3f(105.2,205.04,0.0);
	glVertex3f(207.5,210.67,0.0);
	glVertex3f(112.5,105.85,0.0);
	glEnd();

	
   

}

void BMW_Logo()
{
 //Logo 
	
	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 1.0);

	glVertex3f(161.0,160.0,0.0);
	glVertex3f(161.0,174.0,0.0);
	glVertex3f(170.0,170.69,0.0);
	glVertex3f(175.0,160.0,0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(175.0,160.0,0.0);//last point from previos sec for colour mixing
	glVertex3f(170.93,150.14,0.0);
	glVertex3f(160.86,145.97,0.0);
	

	glColor3f(1.0, 1.0, 1.0);
	glVertex3f(160.86,145.97,0.0);//last point from previos sec for colour mixing
	glVertex3f(151.98,149.32,0.0);
	glVertex3f(147,160,0.0);

	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(147,160,0.0);//last point from previos sec for colour mixing
	glVertex3f(150.86,169.85,0.0);
	glVertex3f(161.0,174.0,0.0);
	glEnd();


   drawCircle(161,160,15,0.0,0.0,0.0);

   	glColor3f (0.753, 0.753, 0.753);
 glBegin(GL_LINE_LOOP);//representation of leterrs BMW in logo
	glVertex3f(159.42,175.51,0);
	glVertex3f(159.8,175.79,0);
	glVertex3f(160.12,175.67,0);
	glVertex3f(160.2,175.29,0);
	glVertex3f(160.0,175.03,0);
	glVertex3f(160.24,174.81,0);
	glVertex3f(160.24,174.43,0);
	glVertex3f(159.82,174.36,0);
	glVertex3f(159.48,174.55,0);
	glEnd();	
}

void endLogo()
{
	glBegin(GL_TRIANGLE_FAN);
					glColor3f(1.0, 1.0, 1.0);

					glVertex3f(161.0,160.0,0.0);
					glVertex3f(161.0,174.0,0.0);
					glVertex3f(170.0,170.69,0.0);
					glVertex3f(175.0,160.0,0.0);

				    glColor3f(0.0, 0.0, 1.0);
					glVertex3f(175.0,160.0,0.0);//last point from previos sec for colour mixing
					glVertex3f(170.93,150.14,0.0);
					glVertex3f(160.86,145.97,0.0);
	
					
					glColor3f(1.0, 1.0, 1.0);
					glVertex3f(160.86,145.97,0.0);//last point from previos sec for colour mixing
					glVertex3f(151.98,149.32,0.0);
					glVertex3f(147,160,0.0);
					
					glColor3f(0.0, 0.0, 1.0);
					glVertex3f(147,160,0.0);//last point from previos sec for colour mixing
					glVertex3f(150.86,169.85,0.0);
					glVertex3f(161.0,174.0,0.0);
				glEnd();
}


void bigBen()
{
	//tower
	glColor3f(0.627,0.322,0.176);
	 glBegin(GL_POLYGON);//front face
		glVertex3f(396.0,362.0,0.0);
		glVertex3f(396.0,446.0,0.0);
		glVertex3f(445.0,446.0,0.0);
		glVertex3f(445.0,362.0,0.0);
	glEnd();	
	 glBegin(GL_POLYGON);//left face
		glVertex3f(396.0,362.0,0.0);
		glVertex3f(396.0,362.0,49.0);
		glVertex3f(396.0,446.0,49.0);
		glVertex3f(396.0,446.0,0.0);
	glEnd();	
	glBegin(GL_POLYGON);//back face
		glVertex3f(396.0,362.0,49.0);
		glVertex3f(396.0,446.0,49.0);
		glVertex3f(445.0,446.0,49.0);
		glVertex3f(445.0,362.0,49.0);
	glEnd();	
	 glBegin(GL_POLYGON);//right face
		glVertex3f(445.0,446.0,0.0);
		glVertex3f(445.0,446.0,49.0);
		glVertex3f(445.0,362.0,49.0);
		glVertex3f(445.0,362.0,0.0);
	glEnd();

	//roof
	glBegin(GL_POLYGON);//front face
		glVertex3f(396.0,446.0,0.0);
		glVertex3f(419.0,499.0,24.5);
		glVertex3f(445.0,446.0,0.0);
	glEnd();
	glBegin(GL_POLYGON);//left face
		glVertex3f(396.0,446.0,0.0);		
		glVertex3f(419.0,499.0,24.5);
		glVertex3f(396.0,446.0,49.5);
	glEnd();
	glBegin(GL_POLYGON);//back face
		glVertex3f(396.0,446.0,49.0);
		glVertex3f(419.0,499.0,24.5);
		glVertex3f(445.0,446.0,49.0);
	glEnd();
	glBegin(GL_POLYGON);//right face
		glVertex3f(445.0,446.0,0.0);		
		glVertex3f(419.0,499.0,24.5);
		glVertex3f(445.0,446.0,49.0);
	glEnd();

	glColor3f(1.0,1.0,1.0);//front face clock
	drawPCircle(419,422,25);

	glColor3f(0.0,0.0,0.0);
	glBegin(GL_LINES);
		glVertex3f(419,422,0);
		glVertex3f(431.5,422,0);
		glVertex3f(419,447,0);
		glVertex3f(419,422,0);
	glEnd();

	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	//right face clock
		glTranslatef(444, 422, 0 );
		glRotatef(90,0,1,0);
		glTranslatef(-444, -422, 0 );
		drawPCircle(419.0,422,25);
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex3f(419,422,0);
		glVertex3f(431.5,422,0);
		glVertex3f(419,447,0);
		glVertex3f(419,422,0);
	glEnd();
	glPopMatrix();

	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	//left face clock
		glTranslatef(394, 422, 0 );
		glRotatef(-90,0,1,0);
		glTranslatef(-394, -422, 0 );
		drawPCircle(419.0,422,25);
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex3f(419,422,0);
		glVertex3f(431.5,422,0);
		glVertex3f(419,447,0);
		glVertex3f(419,422,0);
	glEnd();
	glPopMatrix();		

	glColor3f(1.0,1.0,1.0);
	glPushMatrix();	//back face clock
		glTranslatef(0, 0, 49 );		
		drawPCircle(419.0,422,25);
		glColor3f(0.0,0.0,0.0);
		glBegin(GL_LINES);
		glVertex3f(419,422,0);
		glVertex3f(431.5,422,0);
		glVertex3f(419,447,0);
		glVertex3f(419,422,0);
	glEnd();
	glPopMatrix();		


}


void eiffleTower()
{
	glColor3f (0.753, 0.753, 0.753);
	
	
	glBegin(GL_POLYGON);//left front leg
		glVertex3f(486.07,364.67,0.0);
		glVertex3f(515.45,396.67,0.0);
		glVertex3f(519.19,385.06,0.0);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(519.19,385.06,0.0);
		glVertex3f(519.19,385.06,10.0);
		glVertex3f(486.07,364.67,0.0);		
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(515.45,396.67,0.0);
		glVertex3f(515.45,396.67,10.0);
		glVertex3f(486.07,364.67,0.0);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(486.07,364.67,0.0);
		glVertex3f(515.45,396.67,10.0);
		glVertex3f(519.19,385.06,10.0);
	glEnd();

	
	glBegin(GL_POLYGON);//left back leg
		glVertex3f(486.07,364.67,49.75);
		glVertex3f(515.45,396.67,39.75);
		glVertex3f(519.19,385.06,39.75);
	glEnd();	
	glBegin(GL_POLYGON);		
		glVertex3f(519.19,385.06,39.75);
		glVertex3f(519.19,385.06,29.75);
		glVertex3f(486.07,364.67,49.75);		
	glEnd();	
	glBegin(GL_POLYGON);		
		glVertex3f(515.45,396.67,39.75);
		glVertex3f(515.45,396.67,29.75);
		glVertex3f(486.07,364.67,49.75);		
	glEnd();	
	glBegin(GL_POLYGON);
		glVertex3f(486.07,364.67,49.75);
		glVertex3f(515.45,396.67,29.75);
		glVertex3f(519.19,385.06,29.75);
	glEnd();
	
	glBegin(GL_POLYGON);//Right front leg
		glVertex3f(555.2,396.1,0.0);
		glVertex3f(580.0,360.0,0.0);
		glVertex3f(548.13,385.06,0.0);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(580.0,360.0,0.0);
		glVertex3f(580.0,360.0,10.0);
		glVertex3f(548.13,385.06,0.0);		
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(555.2,396.1,0.0);
		glVertex3f(555.2,396.1,10.0);
		glVertex3f(548.13,385.06,0.0);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(555.2,396.1,10.0);
		glVertex3f(580.0,360.0,10.0);
		glVertex3f(548.13,385.06,0.0);
	glEnd();
	
	glBegin(GL_POLYGON);//Right back leg
	    glVertex3f(580.0,360.0,49.75);
		glVertex3f(555.2,396.1,39.75);		
		glVertex3f(548.13,385.06,39.75);
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(555.2,396.1,39.75);	
		glVertex3f(555.2,396.1,29.75);	
		 glVertex3f(580.0,360.0,49.75);		
	glEnd();
	glBegin(GL_POLYGON);		
		glVertex3f(548.13,385.06,39.75);
		glVertex3f(548.13,385.06,29.75);
		glVertex3f(580.0,360.0,49.75);		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3f(580.0,360.0,49.75);
		glVertex3f(555.2,396.1,29.75);		
		glVertex3f(548.13,385.06,29.75);
	glEnd();
	
	glBegin(GL_POLYGON);//mid front face
		glVertex3f(515.45,396.67,0.0);
		glVertex3f(528.74,436.51,19.875);
		glVertex3f(543.7,436.51,19.875);
		glVertex3f(555.2,396.1,0.0);
	glEnd();
	glBegin(GL_POLYGON);//mid left face
		glVertex3f(515.45,396.67,0.0);
		glVertex3f(515.45,396.67,39.75);
		glVertex3f(543.7,436.51,19.875);
		glVertex3f(543.7,436.51,0.0);
	glEnd();
	glBegin(GL_POLYGON);//mid back face
		glVertex3f(515.45,396.67,39.75);
		glVertex3f(528.74,436.51,19.875);
		glVertex3f(543.7,436.51,19.875);
		glVertex3f(555.2,396.1,39.75);
	glEnd();
	glBegin(GL_POLYGON);//mid right face
		glVertex3f(543.7,436.51,0.0);
		glVertex3f(543.7,436.51,19.875);
		glVertex3f(555.2,396.1,39.75);
		glVertex3f(555.2,396.1,0.0);
	glEnd();

	glBegin(GL_POLYGON);//top front face
		glVertex3f(528.74,436.51,19.875);
		glVertex3f(534.84,518.36,9.9375);
		glVertex3f(543.7,436.51,19.875);
	glEnd();
	glBegin(GL_POLYGON);//top left face
		glVertex3f(528.74,436.51,19.875);
		glVertex3f(534.84,518.36,9.9375);
		glVertex3f(528.74,436.51,19.875);
	glEnd();
	glBegin(GL_POLYGON);//top back face
		glVertex3f(528.74,436.51,19.875);
		glVertex3f(534.84,518.36,9.9375);
		glVertex3f(543.7,436.51,19.875);
	glEnd();
	glBegin(GL_POLYGON);//top right face
		glVertex3f(543.7,436.51,19.875);
		glVertex3f(534.84,518.36,9.9375);
		glVertex3f(543.7,436.51,0.0);
	glEnd();	

}



void Road()
{
	glColor3f(0.0,0.0,0.0);
	glBegin(GL_POLYGON);
	glVertex3f(0.0,0.0,0.0);
	glVertex3f(0.0,90.0,0.0);
	glVertex3f(1200.0,90.0,0.0);
	glVertex3f(1200.0,0.0,0.0);

	glEnd();
}

void sky()
{
	
	
glColor3f(1.0,1.0,1.0);


			drawPCircle(930.0,450,30);//moon
			
		      
		
		

}



void RoadLines()
{
glColor3f(1.0,1.0,1.0);

glBegin(GL_LINES);

glVertex3f(0.0,85.0,0.0);
glVertex3f(100.0,85.0,0.0);

glVertex3f(120.0,85,0.0);
glVertex3f(220.0,85,0.0);

glVertex3f(240.0,85,0.0);
glVertex3f(340.0,85,0.0);

glVertex3f(360.0,85,0.0);
glVertex3f(460.0,85,0.0);

glVertex3f(480.0,85,0.0);
glVertex3f(580.0,85,0.0);

glVertex3f(600.0,85,0.0);
glVertex3f(700.0,85,0.0);

glVertex3f(720.0,85,0.0);
glVertex3f(820.0,85,0.0);

glVertex3f(840.0,85,0.0);
glVertex3f(940.0,85,0.0);

glVertex3f(960.0,85,0.0);
glVertex3f(1060.0,85,0.0);

glVertex3f(1080.0,85,0.0);
glVertex3f(1180.0,85,0.0);

glVertex3f(1200.0,85,0.0);
glVertex3f(1300.0,85,0.0);

glVertex3f(1320.0,85,0.0);
glVertex3f(1420.0,85,0.0);

glEnd();
}

void RoadLines1()
{
glColor3f(1.0,1.0,1.0);

glBegin(GL_LINES);

glVertex3f(0.0,85.0,0.0);
glVertex3f(100.0,85.0,0.0);

glVertex3f(120.0,85,0.0);
glVertex3f(220.0,85,0.0);

glVertex3f(240.0,85,0.0);
glVertex3f(340.0,85,0.0);

glVertex3f(360.0,85,0.0);
glVertex3f(460.0,85,0.0);

glVertex3f(480.0,85,0.0);
glVertex3f(580.0,85,0.0);

glVertex3f(600.0,85,0.0);
glVertex3f(700.0,85,0.0);

glVertex3f(720.0,85,0.0);
glVertex3f(820.0,85,0.0);

glVertex3f(840.0,85,0.0);
glVertex3f(940.0,85,0.0);

glVertex3f(960.0,85,0.0);
glVertex3f(1060.0,85,0.0);

glVertex3f(1080.0,85,0.0);
glVertex3f(1180.0,85,0.0);

glVertex3f(1200.0,85,0.0);
glVertex3f(1300.0,85,0.0);

glVertex3f(1320.0,85,0.0);
glVertex3f(1420.0,85,0.0);

glEnd();
}



void scene_1()
{
	 
	int i;
	glColor3f (0.753, 0.753, 0.753);
		glBegin(GL_LINE_LOOP);
		  
			 for(i=0;i<no_points;i++)
				 {
					glVertex3f (bed[i].x, bed[i].y, bed[i].z);
				}			 
		glEnd();

		 bedColor();
	   sheet();
	   covers();
	   
	   pillow();
	   
	    glPushMatrix(); 		 
		 glTranslatef(-20, 5 , 0);
		 person();
		glPopMatrix();
		  
	   body();


}

void scene_1_1()
{
   scene_1();
		  glColor3f(1.0, 1.0, 1.0);
		  drawCircle(425,275,5,1.0,1.0,1.0);
		  drawCircle(410,295,10,1.0,1.0,1.0); 
		  drawCircle(390,320,15,1.0,1.0,1.0);			
			dreamBubble();
			
			glPushMatrix();					
				glTranslatef(451 * (1 - 0.2), 196 * (1 - 0.2), 0 );
				glScalef(0.2, 0.2, 1.0);
				glTranslatef(-800, 1050, 0 );
				  glPushMatrix(); // Rotate front Big ben around the centre (420, 400 , 15).
				glTranslatef(420, 400 , 15);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-420, -400 , -15);
				glTranslatef(-300, -10 , 100);
				 bigBen();				 
			glPopMatrix();
		
			glPushMatrix(); // Rotate front Eiffle Tower around the centre (535.44, 416.05 , 46.97).
				glTranslatef(535.44, 416.05 , 46.97);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-535.44, -416.05 , 46.97);
				glTranslatef(200, -10 , -100);
				 eiffleTower();				 
			glPopMatrix();	
		 
		 theta1=theta1-2.00;			 
			glPopMatrix();	

			glColor3f(1.0,0.0,0.0);
	   renderSpacedBitmapString(500,480,GLUT_BITMAP_TIMES_ROMAN_24,"DREAMING OF TRAVELING?");
}

void scene_1_2()
{
	 scene_1();
		  drawCircle(425,275,5,1.0,1.0,1.0);
		  drawCircle(410,295,10,1.0,1.0,1.0); 
		  drawCircle(390,320,15,1.0,1.0,1.0);			
			dreamBubble();
			
			glPushMatrix();					
				glTranslatef(451 * (1 - 0.2), 196 * (1 - 0.2), 0 );
				glScalef(0.2, 0.2, 1.0);
				glTranslatef(-800, 1050, 0 );
				scene_1();
				 glPushMatrix(); // Rotate front Big ben around the centre (420, 400 , 15).
				glTranslatef(420, 400 , 24.5);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-420, -400 , -24.5);
				glTranslatef(-300, -10 , 100);
				 bigBen();				 
			glPopMatrix();
		
			glPushMatrix(); // Rotate front Eiffle Tower around the centre (535.44, 416.05 , 46.97).
				glTranslatef(535.44, 416.05 , 46.97);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-535.44, -416.05 , 46.97);
				glTranslatef(200, -10 , -100);
				 eiffleTower();				 
			glPopMatrix();	
		 
		 theta1=theta1-2.00;		 
			glPopMatrix();	

			glColor3f(1.0,0.0,0.0);
	   renderSpacedBitmapString(500,480,GLUT_BITMAP_TIMES_ROMAN_24,"DREAMING OF TRAVELING?");
}
void scene_2()
{
	int i;
	glColor3f (0.753, 0.753, 0.753);
		tween(bed,i8,no_points,proportion,tweenShape);
			 glBegin(GL_LINE_LOOP);
		       
			for(i=0;i<no_points;i++)
			{
			 glVertex3f (tweenShape[i].x,tweenShape[i].y,tweenShape[i].z);
			} 
		glEnd();

			frontHubCap();
			glPushMatrix();		
				glTranslatef(623,0, 0 );//tranlate logo to front hub cap
					BMW_Logo();	
				glPopMatrix();
			 backHubCap();
			 BMW_Logo();//draw logo on back hub cap
			 drawCircle(784,160,76,0.0,0.0,0.0);
			 drawCircle(161,160,71,0.0,0.0,0.0);				
	
			sx+=0.04;
			sy+=0.04;
			proportion +=0.01;

			if(proportion >1.0)
			{ 		
				proportion =0.0;	
		
			}
		
}

void scene_3()
{
	 sky();//draw sky
		 Road();//draw road

	int i;
	glColor3f (0.753, 0.753, 0.753);
		glBegin(GL_LINE_LOOP);
		
			 for(i=0;i<no_points;i++)
				 {
					glVertex3f (i8[i].x, i8[i].y, i8[i].z);
				}			 
		glEnd();

		carColour();//colour car in 

		glPushMatrix(); // Rotate front Hub Cap around the centre (784,160).
				glTranslatef(784, 160 , 0);
				glRotatef(theta, 0, 0, 1);
				glTranslatef(-784, -160 , 0);
				frontHubCap();
					glPushMatrix();		
						glTranslatef(623,0, 0 );//translate logo to front hub cap
						BMW_Logo();	
					glPopMatrix();
				drawCircle(784,160,76,0.0,0.0,0.0);
			glPopMatrix();

			glPushMatrix(); // Rotate front Hub Cap around the centre (784,160).
				glTranslatef(161, 160 , 0);
				glRotatef(theta, 0, 0, 1);
				glTranslatef(-161, -160 , 0);
				backHubCap();
				BMW_Logo();
				drawCircle(161,160,71,0.0,0.0,0.0);
			glPopMatrix();

			
			 glPushMatrix(); // Rotate front Big ben around the centre (420, 400 , 15).
				glTranslatef(420, 400 , 15);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-420, -400 , -15);
				glTranslatef(-300, -10 , 100);
				 bigBen();				 
			glPopMatrix();
		
			glPushMatrix(); // Rotate front Eiffle Tower around the centre (535.44, 416.05 , 46.97).
				glTranslatef(535.44, 416.05 , 46.97);
				glRotatef(theta1, 0, 1, 0);
				glTranslatef(-535.44, -416.05 , 46.97);
				glTranslatef(200, -10 , -100);
				 eiffleTower();				 
			glPopMatrix();	
		 
		 theta1=theta1-2.00;
		 theta=theta-5.00;
		 		 
		
			glPushMatrix();//move road lines
				glTranslatef(translate -= 10.00,-15.0,0.0);
				RoadLines();
					if (translate < -1420.0)
					translate = 1460.0;	    
			glPopMatrix();
	   
			glPushMatrix();
				glTranslatef(translate1 -= 10.00,-15.0,0.0);
				RoadLines1();
					if (translate1 < -1420.0)
					translate1 = 1460.0;	    
			glPopMatrix();	
}

void scene_4()
{
	glPushMatrix();
	        	glTranslatef(161 * (1 - sx), 160 * (1 - sy), 0 );
				glScalef(sx, sy, 1.0);
				glTranslatef(30, 10, 0 );
			glPushMatrix();
	        	glTranslatef(161 * (1 - sx1), 160 * (1 - sy1), 0 );
				glScalef(sx1, sy1, 1.0);
				glTranslatef(161,160,0);
				glRotatef(theta,0,0,1);
				glTranslatef(-161,-160,0);
				endLogo();				
			glPopMatrix();
				glTranslatef(161,160,0);
				glRotatef(theta1,0,0,1);
				glTranslatef(-161,-160,0);
		glColor3f(0.0,0.0,0.0);
		drawPCircle(161,160,18);	
			glPushMatrix();
				glColor3f(0.753, 0.753, 0.753);
				glTranslatef(-3,-0.5,0);
				glBegin(GL_LINE_LOOP);//B
				glVertex3f(159.42,175.51,0);
				glVertex3f(159.8,175.79,0);
				glVertex3f(160.12,175.67,0);
				glVertex3f(160.2,175.29,0);
				glVertex3f(160.0,175.03,0);
				glVertex3f(160.24,174.81,0);
				glVertex3f(160.24,174.43,0);
				glVertex3f(159.82,174.36,0);
				glVertex3f(159.48,174.55,0);
				glEnd();

		
	
				glTranslatef(1,-0.2,0);
				glBegin(GL_LINE_STRIP);//M
				glVertex3f(161.00,174.43,0);
				glVertex3f(161.00,175.79,0);
				glVertex3f(162.00,174.53,0);
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);	
				glEnd();

				glTranslatef(2.5,-0.2,0);
				glBegin(GL_LINE_STRIP);//W
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);
				glVertex3f(164.00,175.53,0);
				glVertex3f(165.00,174.43,0);
				glVertex3f(165.00,175.79,0);
				glEnd();		
			glPopMatrix();

		endLogo();
		drawCircle(161,160,17,0.753, 0.753, 0.753);		
		glPopMatrix();		

		glColor3f(0.0,0.0,0.0);
		 renderSpacedBitmapString(250,480,GLUT_BITMAP_TIMES_ROMAN_24,"BMW THE ULTIMATE DRIVING MACHINE");
		 sx+=0.04;
		 sy+=0.04;
		  sx1+=0.05;
		 sy1+=0.05;
		 theta+=2.00;
		theta1-=2.00;

}

void scene_5()
{
	glPushMatrix();
	        	glTranslatef(161 * (1 - sx), 160 * (1 - sy), 0 );
				glScalef(sx, sy, 1.0);
				glTranslatef(30, 10, 0 );				
			glPushMatrix();
	        	glTranslatef(161 * (1 - sx1), 160 * (1 - sy1), 0 );
				glScalef(sx1, sy1, 1.0);
				glTranslatef(161,160,0);
				glRotatef(theta,0,0,1);
				glTranslatef(-161,-160,0);
				endLogo();				
			glPopMatrix();
				glTranslatef(161,160,0);
				glRotatef(theta1,0,0,1);
				glTranslatef(-161,-160,0);
		glColor3f(0.0,0.0,0.0);
		drawPCircle(161,160,18);	
			glPushMatrix();
				glColor3f(0.753, 0.753, 0.753);
				glTranslatef(-3,-0.5,0);
				glBegin(GL_LINE_LOOP);//B
				glVertex3f(159.42,175.51,0);
				glVertex3f(159.8,175.79,0);
				glVertex3f(160.12,175.67,0);
				glVertex3f(160.2,175.29,0);
				glVertex3f(160.0,175.03,0);
				glVertex3f(160.24,174.81,0);
				glVertex3f(160.24,174.43,0);
				glVertex3f(159.82,174.36,0);
				glVertex3f(159.48,174.55,0);
				glEnd();

		
	
				glTranslatef(1,-0.2,0);
				glBegin(GL_LINE_STRIP);//M
				glVertex3f(161.00,174.43,0);
				glVertex3f(161.00,175.79,0);
				glVertex3f(162.00,174.53,0);
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);	
				glEnd();

				glTranslatef(2.5,-0.2,0);
				glBegin(GL_LINE_STRIP);//W
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);
				glVertex3f(164.00,175.53,0);
				glVertex3f(165.00,174.43,0);
				glVertex3f(165.00,175.79,0);
				glEnd();		
			glPopMatrix();

		endLogo();
		drawCircle(161,160,17,0.753, 0.753, 0.753);		
		glPopMatrix();
		
		theta+=2.00;
		theta1-=2.00;

		glColor3f(0.0,0.0,0.0);
		 renderSpacedBitmapString(300,480,GLUT_BITMAP_TIMES_ROMAN_24,"EXPERIENCE YOUR DREAM");
}

void scene_6()
{
	glPushMatrix();
	        	glTranslatef(161 * (1 - sx), 160 * (1 - sy), 0 );
				glScalef(sx, sy, 1.0);
				glTranslatef(30, 10, 0 );
			glPushMatrix();
	        	glTranslatef(161 * (1 - sx1), 160 * (1 - sy1), 0 );
				glScalef(sx1, sy1, 1.0);			
				endLogo();				
			glPopMatrix();				
		glColor3f(0.0,0.0,0.0);
		drawPCircle(161,160,18);	
			glPushMatrix();
				glColor3f(0.753, 0.753, 0.753);
				glTranslatef(-3,-0.5,0);
				glBegin(GL_LINE_LOOP);//B
				glVertex3f(159.42,175.51,0);
				glVertex3f(159.8,175.79,0);
				glVertex3f(160.12,175.67,0);
				glVertex3f(160.2,175.29,0);
				glVertex3f(160.0,175.03,0);
				glVertex3f(160.24,174.81,0);
				glVertex3f(160.24,174.43,0);
				glVertex3f(159.82,174.36,0);
				glVertex3f(159.48,174.55,0);
				glEnd();

		
	
				glTranslatef(1,-0.2,0);
				glBegin(GL_LINE_STRIP);//M
				glVertex3f(161.00,174.43,0);
				glVertex3f(161.00,175.79,0);
				glVertex3f(162.00,174.53,0);
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);	
				glEnd();

				glTranslatef(2.5,-0.2,0);
				glBegin(GL_LINE_STRIP);//W
				glVertex3f(163.00,175.79,0);
				glVertex3f(163.00,174.43,0);
				glVertex3f(164.00,175.53,0);
				glVertex3f(165.00,174.43,0);
				glVertex3f(165.00,175.79,0);
				glEnd();		
			glPopMatrix();

		endLogo();
		drawCircle(161,160,17,0.753, 0.753, 0.753);		
		glPopMatrix();
		
		
		glColor3f(0.0,0.0,0.0);
		 renderSpacedBitmapString(450,480,GLUT_BITMAP_TIMES_ROMAN_24,"TODAY");
}

void Draw() {
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	frame++;
	glLineWidth(10.0);

	if((frame>=0) && (frame<100))
    {	 
	   scene_1();
	  
    }

	if((frame>99) && (frame<110))

	{
		  scene_1();
		  glColor3f(1.0, 1.0, 1.0);
		  drawCircle(425,275,5,1.0,1.0,1.0);		
	}
	if((frame>109) && (frame<120))
	{
		  scene_1();
		  glColor3f(1.0, 1.0, 1.0);
		  drawCircle(425,275,5,1.0,1.0,1.0);
		  drawCircle(410,295,10,1.0,1.0,1.0);		  
	}
	if((frame>119) && (frame<130)) 
	{
		  scene_1();
		  glColor3f(1.0, 1.0, 1.0);
		  drawCircle(425,275,5,1.0,1.0,1.0);
		  drawCircle(410,295,10,1.0,1.0,1.0); 
		  drawCircle(390,320,15,1.0,1.0,1.0);		  
	}
	if((frame>129) && (frame<230))
	{	
         scene_1_1();
	      
	}
	if((frame>229) && (frame<330))
	{	
         scene_1_2();		
	      
	}
	if((frame>329) && (frame<430)) 
	{
		  	
			glPushMatrix();					
				glTranslatef(300 * (1 - sx), 500 * (1 - sy), 0 );
				glScalef(sx, sy, 1.0);
				glTranslatef(40, 25, 0 );
					glPushMatrix();					
						glTranslatef(451 * (1 - 0.2), 196 * (1 - 0.2), 0 );
						glScalef(0.2, 0.2, 1.0);
						glTranslatef(-800, 1050, 0 );
						scene_2();										   
					glPopMatrix();		
				dreamBubble();
			glPopMatrix();		

		

	}		

   
	 if((frame>429) && (frame<600))
	 {	
		
		 scene_3();//draw car
		 	    
	 }

	 if((frame>599) && (frame<800))
	 {
		 scene_3();//draw car
		 glColor3f(1.0,0.0,0.0);
		 renderSpacedBitmapString(300,480,GLUT_BITMAP_TIMES_ROMAN_24,"MAKE YOUR DREAMS COME TRUE");
		 

	 }

	  if((frame>799) && (frame<1000))
	 {
		 scene_3();//draw car
		 glColor3f(1.0,0.0,0.0);
		 renderSpacedBitmapString(450,480,GLUT_BITMAP_TIMES_ROMAN_24,"IN STYLE");

	 }

	   if((frame>999) && (frame<1200))
	 {
		 scene_3();//draw car
		glColor3f(1.0,0.0,0.0);
		 renderSpacedBitmapString(250,480,GLUT_BITMAP_TIMES_ROMAN_24,"BMW THE ULTIMATE DRIVING MACHINE");

	 }
	    
	   if((frame>1199) && (frame<1345))
	 {
		 scene_4();				
	 }
	   if((frame>1344) && (frame<1490))
	 {		 
		scene_5();		
	 }
	   if((frame>1489) && (frame<1600))
	 {		
		 scene_6();		
	 }

	 fprintf(stdout,"Frame number= %i\n", frame);
	
	  if(frame>=1600)
	  {
		  frame=0;
		  proportion=0.0;
		  translate=0.0;
		  translate1=1440.0;
		  theta=0.0;
		  theta1=0.0;
		  sx=1.0;
		  sy=1.0;
		  sx1=1.0;
		  sy1=1.0;

	  }
	
	glutSwapBuffers();
	glFlush ();
}




void Timer( int value )
{
   if( value ) glutPostRedisplay();
   glutTimerFunc(40,Timer,value);
}

void visibility(int state)
{
 switch (state)
 {
   case GLUT_VISIBLE:
             Timer(1);
             break;
   case GLUT_NOT_VISIBLE:
             Timer(0);
             break;
   default:
             break;
 }
}

void Initialize() {
	glClearColor(0.098, 0.098, 0.439, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 1000, 0,500,-500,500);
}


int main(int iArgc, char** cppArgv) {
	glutInit(&iArgc, cppArgv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);	
	glutInitWindowSize(1200, 600);
	glutInitWindowPosition(110, 30);
	glutCreateWindow("BMW");
	PlaySound(TEXT("Yiruma - Dream"),NULL,SND_ASYNC|SND_FILENAME|SND_LOOP);
	Initialize();
	glutDisplayFunc(Draw);
	glutVisibilityFunc(visibility);
	glutMainLoop();
	return 0;
}

