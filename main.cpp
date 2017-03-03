#include <igl/readOFF.h>
#include <igl/readTGF.h>
#include <igl/viewer/Viewer.h>
#include "shared_path.h"


#ifndef TETLIBRARY
#  define TETLIBRARY 
#endif
#include <igl/copyleft/tetgen/read_into_tetgenio.h>
#include <igl/copyleft/tetgen/tetgenio_to_tetmesh.h>
#include "igl/boundary_facets.h"




Eigen::MatrixXd V, C;

Eigen::MatrixXi F, BE, T;

const Eigen::RowVector3d sea_green(70. / 255., 252. / 255., 167. / 255.);


int main(int argc, char *argv[])
{
	// Load a mesh in OFF format
	igl::readOFF(SHARED_PATH "/bunny.off", V, F);
	std::string skel_filename = "../shared/roboptim-debug-graph-edge.tgf";
	igl::readTGF(skel_filename, C, BE);

	

	// Plot the mesh
	igl::viewer::Viewer viewer;
	//viewer.data.set_mesh(V, F);
	viewer.data.set_vertices(C);

	double HI = 1; // set HI and LO according to your problem.
	double LO = 0;
	double range = HI - LO;
	Eigen::MatrixX3d m = Eigen::MatrixX3d::Random(C.rows(), 3); // 3x3 Matrix filled with random numbers between (-1,1)
	int rows = m.rows();
	int cols = m.cols();
	m = (m + Eigen::MatrixX3d::Constant(rows, cols, 1.))*range / 2.; // add 1 to the matrix to have values between 0 and 2; multiply with range/2
	m = (m + Eigen::MatrixX3d::Constant(rows, cols, LO)); //set LO as the lower bound (offset)

	const Eigen::MatrixX3d color = m;
	//viewer.data.set_points(C, color);
	viewer.data.set_edges(C, BE, sea_green);
	
	

	viewer.core.point_size = 10;
	//viewer.core.show_faces = false;
	//viewer.core.line_width = 30;
	viewer.launch();
}
