#include <iostream>
#include <cstdlib>
#include "graphlib.h++"

using namespace std;

unsigned int errorCount = 0;

#define assert( cond, error ) if ( !(cond) ) { cout << "ERROR " << __FILE__ << ":" << __LINE__ << ": " << error << endl; errorCount++; }

int main( int argc, char *argv[] )
{
  Graph g;

  assert( g.edgeCount() == 0, "edge count fail" );
  assert( g.vertexCount() == 0, "vertex count fail" );
  assert( g.simple(), "simple fail" );
  assert( g.directed() == false, "directed fail" );
  assert( g.findVertex( 99 ) == NULL, "find vertex fail" );
  assert( g.findEdge( 12, 67 ) == NULL, "find edge fail" );

  g.addVertex( 3 );
  assert( g.edgeCount() == 0, "edge count fail" );
  assert( g.vertexCount() == 1, "vertex count fail" );
  assert( g.simple(), "simple fail" );
  assert( g.directed() == false, "directed fail" );
  assert( g.findVertex( 3 ) != NULL, "find vertex fail" );
  assert( g.findEdge( 3, 67 ) == NULL, "find edge fail" );

  g.addVertex( 3 );
  assert( g.edgeCount() == 0, "edge count fail" );
  assert( g.vertexCount() == 1, "vertex count fail" );
  assert( g.simple(), "simple fail" );
  assert( g.directed() == false, "directed fail" );
  assert( g.findVertex( 3 ) != NULL, "find vertex fail" );
  assert( g.findEdge( 3, 67 ) == NULL, "find edge fail" );

  g.addEdge( 3, 5 );
  assert( g.edgeCount() == 1, "edge count fail" );
  assert( g.vertexCount() == 2, "vertex count fail" );
  assert( g.simple(), "simple fail" );
  assert( g.directed() == false, "directed fail" );
  assert( g.findVertex( 3 ) != NULL, "find vertex fail" );
  assert( g.findVertex( 5 ) != NULL, "find vertex fail" );
  assert( g.findEdge( 3, 5 ) != NULL, "find edge fail" );

  g.addEdge( 3, 5 );
  assert( g.edgeCount() == 2, "edge count fail" );
  assert( g.vertexCount() == 2, "vertex count fail" );
  assert( !g.simple(), "simple fail" );
  assert( g.directed() == false, "directed fail" );
  assert( g.findVertex( 3 ) != NULL, "find vertex fail" );
  assert( g.findVertex( 5 ) != NULL, "find vertex fail" );
  assert( g.findEdge( 3, 5 ) != NULL, "find edge fail" );

  Graph g2;

  assert( g2.edgeCount() == 0, "edge count fail" );
  assert( g2.vertexCount() == 0, "vertex count fail" );
  assert( g2.simple(), "simple fail" );
  assert( g2.directed() == false, "directed fail" );
  assert( g2.findVertex( 14 ) == NULL, "find vertex fail" );
  assert( g2.findEdge( 14, 14 ) == NULL, "find edge fail" );
  assert( g2.findEdge( 9, 34 ) == NULL, "find edge fail" );

  g2.addEdge( 9, 9 );
  assert( g2.edgeCount() == 1, "edge count fail" );
  assert( g2.vertexCount() == 1, "vertex count fail" );
  assert( !g2.simple(), "simple fail" );
  assert( g2.directed() == false, "directed fail" );
  assert( g2.findVertex( 9 ) != NULL, "find vertex fail" );
  assert( g2.findEdge( 9, 9 ) != NULL, "find edge fail" );
  assert( g2.findEdge( 9, 12 ) == NULL, "find edge fail" );

  int w = 10;
  int h = 10;
  Graph grid( w, h );
  assert( grid.edgeCount() == w * (h + 1) + h * (w + 1), "edge count fail" );
  assert( grid.vertexCount() == (w + 1) * (h + 1), "vertex count fail" );
  assert( grid.simple(), "simple fail" );
  assert( grid.directed() == false, "directed fail" );
  assert( grid.findVertex( 0 ) != NULL, "find vertex fail" );
  assert( grid.findEdge( 0, w + 1 ) != NULL, "find edge fail" );
  assert( grid.findEdge( 0, 2 ) == NULL, "find edge fail" );

  w = 1;
  h = 1;
  Graph grid1( w, h );
  assert( grid1.edgeCount() == w * (h + 1) + h * (w + 1), "edge count fail" );
  assert( grid1.vertexCount() == (w + 1) * (h + 1), "vertex count fail" );
  assert( grid1.simple(), "simple fail" );
  assert( grid1.directed() == false, "directed fail" );
  assert( grid1.countRoutes( 0, ((w + 1) * (h + 1) - 1) ) == 2, "count routes fail" );
  assert( grid1.findVertex( 1 ) != NULL, "find vertex fail" );
  assert( grid1.findEdge( 1, w - 1 ) != NULL, "find edge fail" );
  assert( grid1.findEdge( 0, ((w + 1) * (h + 1) - 1) ) == NULL, "find edge fail" );

  w = 2;
  h = 2;
  Graph grid2( w, h );
  assert( grid2.edgeCount() == w * (h + 1) + h * (w + 1), "edge count fail" );
  assert( grid2.vertexCount() == (w + 1) * (h + 1), "vertex count fail" );
  assert( grid2.simple(), "simple fail" );
  assert( grid2.directed() == false, "directed fail" );
  assert( grid2.countRoutes( 0, ((w + 1) * (h + 1) - 1) ) == 12, "count routes fail" );
  assert( grid1.findVertex( w ) != NULL, "find vertex fail" );
  assert( grid1.findEdge( w, 0 ) != NULL, "find edge fail" );
  assert( grid1.findEdge( 0, ((w + 1) * (h + 1) - 1) ) == NULL, "find edge fail" );

  exit( errorCount );
}
