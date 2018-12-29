# Bezier-and-B-spline
Manual for Project 4

Setup

To compile I used the following:
	
	g++ main.cpp -o main.out -lGL -lglut -lGLU -lm
	./main.out

This program uses text files for input. Make sure that they are in the same working directory or provide the full path. Path can be changed at the top of the program. The string called “inputFile” is the input path.

The polygon in the text file will be drawn when starting the program.

It is important that there are at least two new lines(and empty) after the last point in the input file. Otherwise it will not read correctly. Use the same format as the input file provided. 

Polygons are numbered starting with index 1, and the order is displayed in the input file. 

2. Running the program
The program uses the keyboard to select what actions to be performed on the polyhedra. 

After starting the program you will get a list of action in the console. To select an action you need to click on the window with the polygons with your mouse and then press a number on your keyboard. 
Then the program will ask you to fill in e.g. “Which polygon” And your choice must be typed into the console. Pressing enter will submit the choice.

So in short, choose an action by selection the window by simply clicking on it and pressing the desired number, then the rest is done in the console. 

The program will use the same control points for both methods, meaning that for each set of control points there will be a Bezier curve (yellow) and a B-spline Curve (turquoise). 

P.S. THE PROGRAM IS RATHER SLOW, HAVE PATIENCE. please.

3.  Adding the outline of the polygon
Select the window and press “1” to change add the outline. Doing this action on a polygon with an outline will delete the outline. Then select which polygon.
Example:
Enter which polygon 
3

4. Add point to the curves
To change add you need to select the window and press “2”. First you select which polygon. Then you enter the coordinates for the new point, which all ought to be between 0 and 600 in both directions(600x600 is the window size). The point will be added to the end of the curve
Example:
Enter which polygon 
3
Selected polygon has the control points at: 
 60  400
130  350
230  350
290  400
150  400
Enter Coordinates for the new point? x y 
160 450
5. Inserting a point to the curve
To insert a point you need to select the window and press “3”. First you select the polygon. Then you enter the index to where you want to insert the point. Remember that this uses index starting from 0. Lastly enter the coordinates for the new point.
Example:
Enter which polygon 
4
Selected polygon has the control points at: 
 400  400
450  440
500  300
570  470
580  400
Enter the index for the new point?  
3
Enter Coordinates for the new point? x y 
540 290

6. Change the degree of selected polygon
To change the degree of the polygon, you need to select the window and press “4”.
Then you will be asked to choose which polygon and then what degree it should be using.
Example:
Enter which polygon 
1
 Selected polygon currently has the degree: 3
Enter what degree? 2,3,4.. 
4

7. Change the resolution of the polygon
To change the resolution of the polygon, you need to select the window and press “5”.
Then you will be asked to choose which polygon and then what resolution it should be using.
Example:
 Enter which polygon 
 2
 Selected polygon currently has the resolution: 100
 Enter what resolution? 50,100,1000.. 
 50
8. Deleting point from curve
To delete a point, select window and press “6”. Then enter which polygon. Then you will be asked to enter what point to be deleted. Note that index starts from 0. 
Example:
Enter which polygon 
4
Selected polygon has the control points at: 
400  400
450  440
500  300
540  290
570  470
580  400
Enter which point to delete? 0,1,2,.. 
3

9. Modifying a point
To modify a point, select window and press “7”. Then enter which polygon to be modified. Subsequently you enter the index of the point that will be modified. Lastly you enter the new coordinates for the point.  Index starts at 0.

Enter which polygon 
3
Selected polygon has the control points at: 
60  400
130  350
230  350
290  400
150  400
160  450
Enter the index for the point to modify?  
0
Enter Coordinates for the new point? x y 
100 400

10. Adding a new curve
To add a new curve, select window and press “8”. Then you enter the resolution in the console. Subsequently you enter the degree. Lastly you enter the coordinates for 4 new points which will be the control points for the new curve. You can later add more points to this curve. 

If you would want to delete a curve, you’d have to erase all the data the input file after closing. 

 Enter the resolution for the new curve. 50,100,1000,... 
100
Enter the degree for the new curve? 2,3,4..  
4
Enter Coordinates for the new point? x1 y1 x2 y2 x3 y3 x4 y4 
300 50 320 100 500 110 450 40



11. Save and exit
Select window and press “0” to exit the program. This will save the changes in an output file. 

12. Implementation



