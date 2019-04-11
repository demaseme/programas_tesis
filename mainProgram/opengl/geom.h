#include <stdint.h>

typedef struct punto{
	char etiqueta;
	uint16_t x;
	uint16_t y;
}Punto;

typedef struct {
  double x;
  double y;
} point_t;

typedef point_t* point_ptr_t;

typedef struct segmento{
	char etiqueta[3];
	struct punto a;
	struct punto b;
}Segmento;

int puntos_iguales(Punto a, Punto b){
	return a.x == b.x && a.y == b.y;
}

int comparten_punto(Segmento s1, Segmento s2){
	return puntos_iguales(s1.a, s2.a) || puntos_iguales(s1.a, s2.b) || puntos_iguales(s1.b, s2.a) || puntos_iguales(s1.b, s2.b);
}

int area(Punto a, Punto b, Punto c){
	long r = (long)(b.x - a.x) * (long)(c.y - a.y) - (long)(c.x - a.x) * (long)(b.y - a.y);

	return r > 0;
}

int izquierda(Punto a, Punto b, Punto c){
	return area(a, b, c) > 0;
}

int Xor(int x, int y){
	return !x ^ !y;
}

int interseccion(Segmento s1, Segmento s2){
	Punto a = s1.a, b = s1.b, c = s2.a, d = s2.b;

	return Xor(izquierda(a, b, c), izquierda(a, b, d)) && Xor(izquierda(c,d,a), izquierda(c,d,b));
}


/* Three points are a counter-clockwise turn if ccw > 0, clockwise if
 * ccw < 0, and collinear if ccw = 0 because ccw is a determinant that
 * gives the signed area of the triangle formed by p1, p2 and p3.
 */
static double
ccw(point_t* p1, point_t* p2, point_t* p3)
{
  return (p2->x - p1->x)*(p3->y - p1->y) - (p2->y - p1->y)*(p3->x - p1->x);
}

/* Returns a list of points on the convex hull in counter-clockwise order.
 * Note: the last point in the returned list is the same as the first one.
 */
void
convex_hull(point_t* points, ssize_t npoints, point_ptr_t** out_hull, ssize_t* out_hullsize)
{
  point_ptr_t* hull;
  ssize_t i, t, k = 0;

  hull = *out_hull;

  /* lower hull */
  for (i = 0; i < npoints; ++i) {
    while (k >= 2 && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }

  /* upper hull */
  for (i = npoints-2, t = k+1; i >= 0; --i) {
    while (k >= t && ccw(hull[k-2], hull[k-1], &points[i]) <= 0) --k;
    hull[k++] = &points[i];
  }

  *out_hull = hull;
  *out_hullsize = k;
}