#include <iostream>
#include "GRANSAC.hpp"
#include "PlaneModel.hpp"
#include <omp.h>
#include <opencv2/opencv.hpp>

bool PlaneFitting(const std::vector<Vector3VP> &points_input, double* center, double* normal)
{
	int Num = points_input.size();
	std::vector<std::shared_ptr<GRANSAC::AbstractParameter>> CandPoints;
	CandPoints.resize(Num);
#pragma omp parallel for num_threads(6)
	for (int i = 0; i <Num; ++i)
	{
		Vector3VP p=points_input[i];
		std::shared_ptr<GRANSAC::AbstractParameter> CandPt = std::make_shared<Point3D>(p[0], p[1],p[2]);
		CandPoints[i]=CandPt;
	}
	
	GRANSAC::RANSAC<PlaneModel, 3> Estimator;
    Estimator.Initialize(0.1, 100); // Threshold, iterations

    int64_t start = cv::getTickCount();
	Estimator.Estimate(CandPoints);
    int64_t end = cv::getTickCount();
    std::cout << "RANSAC took: " << GRANSAC::VPFloat(end - start) / GRANSAC::VPFloat(cv::getTickFrequency()) * 1000.0 << " ms." << std::endl;
	
	auto BestPlane = Estimator.GetBestModel();
	if (BestPlane == nullptr)
	{
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
        center[i] = BestPlane->m_PointCenter[i];
	}
    for (int i = 0; i < 4; i++)
    {
        normal[i] = BestPlane->m_PlaneCoefs[i];
    }

	return true;
}
int main()
{
    // data generation
    double a = -1/3.0, b = -2/3.0, d =3.0;
    cv::RNG rng;
    double w_sigma = 0.1;

    std::vector<Vector3VP> point_cloud;
    double *center = new double[3];
    double *coefs = new double[4];

    for(int i=0; i<300; i++)
    {
        for(int j=0; j<400; j++)
        {
            double x = double(i);
            double y = double(j);
            double z = a*x + b*y + d + rng.gaussian(w_sigma);

            Vector3VP Pt3d = {x, y, z};

            point_cloud.push_back(Pt3d);
        }
    }

    // perform Plane Fitting Algorithm
    PlaneFitting(point_cloud, center, coefs);

    for(int i=0; i<4; i++)
    {
        std::cout << coefs[i] << std::endl;
    }

    return 0;
}







