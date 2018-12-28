//
//  main.cpp
//  assignment4
//
//  Created by Simon Åkesson on 2018-11-28.
//  Copyright © 2018 Simon Åkesson. All rights reserved.
//

#include <iostream>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include "DrawLine.h"
#include "point.h"
#include "bezier.hpp"
#include "bspline.h"
#include <fstream>
#include "polygon.h"

int height=600,width=600;
float *PixelBuffer;
polygon poly;
using namespace std;
string inputFile = "/Users/simonakesson/Document/ECS 175/assignment4/assignment4/test.txt";
string outputFile = "/Users/simonakesson/Document/ECS 175/assignment4/assignment4/test.txt";

vector<point> ps;
vector<point> castPoints;
vector<point> spline;
vector<vector<point> > curves;
vector<vector<point> > curvesCast;
vector<polygon> polygons;
class bezier* bz;
class bspline* bs;
class DrawLine* dl;

//reads the file of the original input.
void readFile(){
    
    std::ifstream file(inputFile);
    std::string str;
    int nbrPoly;
    if (!file) {
        cout << "Unable to open file";
        exit(1);
    }
    int counter = 0;
    polygon poly;
    std::string delimiter = " ";
    while(std::getline(file, str)){
        if(counter==0) {
            nbrPoly = stoi(str);
            counter++;
            
        }
        else if(str == ""){
            if(poly.points.size() !=0){
                polygons.push_back(poly);
            }
            poly = *new polygon();
            counter=1;
            
        }

        else if(str.length() >= 3){
            std::string xcord = str.substr(0, str.find(delimiter));
            std::string temps = str.substr(xcord.length()+1);
            std::string ycord = temps.substr(0, temps.find(delimiter));
            point p = *new point(stof(xcord),stof(ycord));
           // std::cout<<p.x << " " <<  p.y << "\n";
            poly.addPoint(p);
            
            
        }else{
            if(counter==1){
                poly.setDegree(stoi(str));
                counter++;
            }else{
                 poly.addKnot(stoi(str));
                
            }
           
        }
        
    }
}




void draw(){
    
    for(int j = 0; j<curvesCast.size();j++){
        for(int i = 0; i < curvesCast[j].size()-1; i++){
            dl->drawDDA(curvesCast[j][i],  curvesCast[j][i+1],1,1,0);
        }
    }
    for(int j = 0; j<curves.size();j++){
        for(int i = 0; i < curves[j].size()-1; i++){
           dl-> drawDDA(curves[j][i],  curves[j][i+1],0,1,1);
        }
    }
}
//allows user to change degree. Default is 100



//clears the window
void clearDrawingBoard(int nbr, int selection){
    switch (selection){
        case 1 :{
            for(int i = 0; i < curvesCast[nbr-1].size()-1; i++){
                dl->drawDDA(curvesCast[nbr-1][i],  curvesCast[nbr-1][i+1],0,0,0);
            }
            break;
        }
        case 2:{
            for(int i = 0; i < curves[nbr-1].size()-1; i++){
               dl-> drawDDA(curves[nbr-1][i],  curves[nbr-1][i+1],0,0,0);
            }
            break;
        }
    }

}
void redraw(int nbr,int selection){
    switch (selection){
        case 1 :{
            for(int i = 0; i < curvesCast[nbr-1].size()-1; i++){
                dl->drawDDA(curvesCast[nbr-1][i],  curvesCast[nbr-1][i+1],1,1,0);
            }
            break;
        }
        case 2:{
            for(int i = 0; i < curves[nbr-1].size()-1; i++){
               dl-> drawDDA(curves[nbr-1][i],  curves[nbr-1][i+1],0,1,1);
            }
            break;
        }
    }

}
void replacePolygon(int selection){
    curves[selection-1] = bs->dbhHelper(polygons[selection-1].degree, (int)polygons[selection-1].points.size()-1, polygons[selection-1].points, polygons[selection-1].resolution, polygons[selection-1].knots);
    curvesCast[selection-1] = bz->deCasteljauV(polygons[selection-1].points,polygons[selection-1].resolution);
}

void modifyPoint(int index, int pos,float x, float y){
    clearDrawingBoard(index, 1);
    clearDrawingBoard(index, 2);
    polygons[index-1].points.at(pos) = *new point(x,y);
    replacePolygon(index);
    redraw(index,1);
    redraw(index,2);
}
void newCurve(vector<point>pts, vector<int>knots, int degree, int resolution){
    polygon pol;
    pol.points = pts;
    pol.knots = knots;
    pol.degree = degree;
    pol.resolution = resolution;
    polygons.push_back(pol);
    curvesCast.push_back(bz->deCasteljauV(polygons.at(polygons.size()-1).points,polygons.at(polygons.size()-1).resolution));
    curves.push_back(bs->dbhHelper(polygons.at(polygons.size()-1).degree, (int)polygons.at(polygons.size()-1).points.size()-1, polygons.at(polygons.size()-1).points, polygons.at(polygons.size()-1).resolution, polygons.at(polygons.size()-1).knots));
    redraw((int)polygons.size(),1);
    redraw((int)polygons.size(),2);
}

void deletePoint(int index,int pos){
    clearDrawingBoard(index, 1);
    clearDrawingBoard(index, 2);
    polygons[index-1].points.erase(polygons[index-1].points.begin()+pos);
    replacePolygon(index);
    redraw(index,1);
    redraw(index,2);
    
}
void addFunc(int selection, float x,float y){
    clearDrawingBoard(selection, 1);
    clearDrawingBoard(selection, 2);
    polygons[selection-1].addPoint(*new point(x,y));
    polygons[selection-1].knots.push_back(polygons[selection-1].knots.back()+1);
    replacePolygon(selection);
    redraw(selection,1);
    redraw(selection,2);
}
void insertPoint(int index,int pos,float x, float y){
    clearDrawingBoard(index, 1);
    clearDrawingBoard(index, 2);
    polygons[index-1].points.insert(polygons[index-1].points.begin()+pos, *new point(x,y));
    polygons[index-1].knots.push_back(polygons[index-1].knots.back()+1);
    replacePolygon(index);
    redraw(index,1);
    redraw(index,2);
    
}

void setDegree(int selection, int degree){
    clearDrawingBoard(selection, 2);
    polygons[selection-1].setDegree(degree);
    replacePolygon(selection);
    redraw(selection,2);
}
void setResolution(int selection, int resolution){
    clearDrawingBoard(selection, 1);
    clearDrawingBoard(selection, 2);
    polygons[selection-1].setResolution(resolution);
    replacePolygon(selection);
    redraw(selection,1);
    redraw(selection,2);
}

void writeToFile(){
    ofstream file;
    file.open (outputFile);
    file << polygons.size() << "\n\n";
    for(polygon p : polygons){
        file << "\n";
        for(point points : p.points){
            file << (float)points.x << " "<< (float)points.y <<  "\n" ;
        }
        file << p.degree<< "\n";
        for(int kn : p.knots){
            file << kn << "\n" ;
        }
        file << "\n";
    }
    file.close();
}

//function for the input of the keyboard while running
void keyboard(int key, int x, int y){
    int selection;
    string str;
    switch (key) {
        case '1' : {
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            if(!polygons[selection-1].active){
                for(int i = 0; i < polygons[selection-1].points.size()-1;i++){
                    dl->drawDDA(polygons[selection-1].points[i], polygons[selection-1].points[i+1], 0, 0, 1);
                }
                 polygons[selection-1].active = true;
            }else{
                for(int i = 0; i < polygons[selection-1].points.size()-1;i++){
                    dl->drawDDA(polygons[selection-1].points[i], polygons[selection-1].points[i+1], 0, 0, 0);
                }
                polygons[selection-1].active = false;
            }
            }
            break;
        }
        case '2' : {
            float x,y;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<"Selected polygon has the control points at: \n ";
            for(point p : polygons[selection-1].points){
                std::cout<<p.x<< "  " <<p.y<<"\n";
            }
            std::cout <<"Enter Coordinates for the new point? x y \n";
            cin>>x>>y;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x>>y;
            }
            
            addFunc(selection,x,y);
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '3' : {
            
            float x,y;
            int pos;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<"Selected polygon has the control points at: \n ";
            for(point p : polygons[selection-1].points){
                std::cout<<p.x<< "  " <<p.y<<"\n";
            }
            std::cout <<"Enter the index for the new point?  \n";
            cin>>pos;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>pos;
            }
                if(polygons[selection-1].points.size()>pos){
            std::cout <<"Enter Coordinates for the new point? x y \n";
            cin>>x>>y;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x>>y;
            }

            insertPoint(selection,pos, x, y);
                }else{
                    std::cout<<"out of bounds \n";
                }
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '4' :{
            
            float x;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<" Selected polygon currently has the degree: "<< polygons[selection-1].degree<<"\n";
            std::cout <<"Enter what degree? 2,3,4.. \n";
            cin>>x;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x;
            }
            
            setDegree(selection, x);
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '5' : {
            float x;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<" Selected polygon currently has the resolution: "<< polygons[selection-1].resolution<<"\n";
            std::cout <<"Enter what resolution? 50,100,1000.. \n";
            cin>>x;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x;
            }
            
            setResolution(selection, x);
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '6' : {
            float x;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<"Selected polygon has the control points at: \n ";
            for(point p : polygons[selection-1].points){
                std::cout<<p.x<< "  " <<p.y<<"\n";
            }
            std::cout <<"Enter which point to delete? 0,1,2,.. \n";
            cin>>x;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x;
            }
            
                if(polygons[selection-1].points.size()>x){
                    deletePoint(selection, x);
                }else{
                    std::cout<<"out of bounds \n";
                }
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '7' : {
            
            float x,y;
            int pos;
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
            std::cout<<"Selected polygon has the control points at: \n ";
            for(point p : polygons[selection-1].points){
                std::cout<<p.x<< "  " <<p.y<<"\n";
            }
            std::cout <<"Enter the index for the point to modify?  \n";
            cin>>pos;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>pos;
            }
            if(polygons[selection-1].points.size()>pos){
            std::cout <<"Enter Coordinates for the new point? x y \n";
            cin>>x>>y;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x>>y;
            }
         
            modifyPoint(selection, pos, x, y);
            }else{
                std::cout<<"out of bounds \n";
            }
            }else{
                std::cout<<"out of bounds \n";
            }
            break;
        }
        case '8' : {
            float x1,y1,x2,y2,x3,y3,x4,y4;
            int pos;
            vector<point> tempP;
            vector<int> knot;
            std::cout <<"Enter the resolution for the new curve. 50,100,1000,... \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            std::cout <<"Enter the degree for the new curve? 2,3,4..  \n";
            cin>>pos;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>pos;
            }
            std::cout <<"Enter Coordinates for the new point? x1 y1 x2 y2 x3 y3 x4 y4 \n";
            cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>x1>>y1>>x2>>y2>>x3>>y3>>x4>>y4;
            }
            for(int i = 0; i <= 4 + pos + 2; i++){
                knot.push_back(i);
            }
            tempP.push_back(*new point(x1,y1));
            tempP.push_back(*new point(x2,y2));
            tempP.push_back(*new point(x3,y3));
            tempP.push_back(*new point(x4,y4));
            newCurve(tempP, knot, pos, selection);
            break;
        }
        case '9' : {
            std::cout <<"Enter which polygon \n";
            cin>>selection;
            if(!cin){
                cout << "REENTER!  \n";
                cin.clear();
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                cin>>selection;
            }
            if(polygons.size()>=selection){
                std::cout<<"Selected polygon has the control points at: \n";
                for(point p : polygons[selection-1].points){
                    std::cout<<p.x<< "  " <<p.y<<"\n";
                }
                
            }
            break;
        }
        case '0' : {
            writeToFile();
            exit(0);
            break;
        }
    }
    
    glutPostRedisplay();
        std::cout<<"\n Select option 1-9 by clicking on window and pressing number. \n\n 1: Draw the outline  \n\n 2: Add point to the curve  \n\n 3: Insert a point in the curve \n\n 4: Change degree \n\n 5: Change resolution.  \n\n 6: Delete point from curve. \n\n 7: Modify point. \n\n 8: Adding a new curve \n\n 9: Print out control points\n\n 0: Exit program \n\n";
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    for(int i = 0; i < ps.size()-1;i++){
      // drawDDA(ps[i], ps[i+1], 1, 0, 0);
    }
    glDrawPixels(height, width, GL_RGB, GL_FLOAT, PixelBuffer);
    glFlush();
    glutSwapBuffers ();
}



int main(int argc, char *argv[]){
    readFile();
    for(int i = 0; i < polygons.size();i++){
        curvesCast.push_back(bz->deCasteljauV(polygons[i].points,polygons[i].resolution));
    }
    for(int i = 0; i < polygons.size();i++){
        curves.push_back(bs->dbhHelper(polygons[i].degree, (int)polygons[i].points.size()-1, polygons[i].points, polygons[i].resolution, polygons[i].knots));
    }
    glutInit(&argc, argv);
    PixelBuffer = new float[height * width * 3];
    draw();
    std::cout<<"\n Select option 1-9 by clicking on window and pressing number. \n\n 1: Draw the outline  \n\n 2: Add point to the curve  \n\n 3: Insert a point in the curve \n\n 4: Change degree \n\n 5: Change resolution.  \n\n 6: Delete point from curve. \n\n 7: Modify point. \n\n 8: Adding a new curve \n\n 9: Print out control points\n\n 0: Exit program \n\n";
    glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(100, 100); //set window position
    glutCreateWindow("Assignment 4"); //create and set main window title
    glClearColor (0,0,0,0); //clears the buffer of OpenGL
    glutDisplayFunc(display);  //callbacks display function
    glutSpecialFunc(keyboard);
    glutMainLoop();//main display loop, -will display until terminate
    return 0;
}


