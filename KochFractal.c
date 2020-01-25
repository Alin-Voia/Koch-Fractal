#include <stdio.h>
#include <math.h>
#define pi M_PI

typedef struct
{
    int x,y;

}points;

/**For function 'koch' we need 6 parameters.4 of them are the coordinates of 2 points:
the first point and the last point.one parameter is the grade of the koch snowflake and
the last parameter is the svg file in which we print the coordinates of the points*/
void koch(int s_x, int s_y, int e_x, int e_y, int grade, FILE* pgmimg)
{
    float angle = M_PI/3;
    points px3, py3, px4, py4, px5, py5;

    if(grade > 0)
    {
        px3.x = (2*s_x + e_x)/3;
        py3.y = (2*s_y + e_y)/3;

        px5.x = (2*e_x + s_x)/3;
        py5.y = (2*e_y + s_y)/3;

        ///These 2 are the coordinates of the point that forms the triangle
        px4.x = px3.x + (px5.x-px3.x)*cos(angle)+(py5.y-py3.y)*sin(angle);
        py4.y = py3.y - (px5.x-px3.x)*sin(angle)+(py5.y-py3.y)*cos(angle);

        koch(s_x, s_y, px3.x, py3.y, grade-1, pgmimg);
        koch(px3.x, py3.y, px4.x, py4.y, grade-1, pgmimg);
        koch(px4.x, py4.y, px5.x, py5.y, grade-1, pgmimg);
        koch(px5.x, py5.y, e_x, e_y, grade-1, pgmimg);

    }

    else
    if(grade == 0)
    {
        fprintf(pgmimg, "<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" stroke=\"blue\" stroke-width=\"1\" />\n",s_x,s_y,e_x,e_y);
    }
}

int main()
{
    FILE* pgmimg;
	pgmimg = fopen("KochFractal.svg", "wb");

    fprintf(pgmimg, "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");

    /**int ax1 = 50, ay1 = 200, ax2 = 350, ay2 = 200;
    int bx1 = 350, by1 = 200, bx2 = 200, by2 = 450;
    int cx1 = 200, cy1 = 450, cx2 = 50, cy2 = 200;*/

    int ax1 = 200, ay1 = 200, ax2 = 500, ay2 = 200;
    int bx1 = 500, by1 = 200, bx2 = 500, by2 = 500;
    int cx1 = 500, cy1 = 500, cx2 = 200, cy2 = 500;
    int dx1 = 200, dy1 = 500, dx2 = 200, dy2 = 200;

    /**koch(ax1, ay1, ax2, ay2, 1, pgmimg);
    koch(bx1, by1, bx2, by2, 1, pgmimg);
    koch(cx1, cy1, cx2, cy2, 1, pgmimg);*/

    koch(ax1, ay1, ax2, ay2, 1, pgmimg);
    koch(bx1, by1, bx2, by2, 2, pgmimg);
    koch(cx1, cy1, cx2, cy2, 3, pgmimg);
    koch(dx1, dy1, dx2, dy2, 4, pgmimg);

	fprintf(pgmimg, "</svg>");

    fclose(pgmimg);
}
