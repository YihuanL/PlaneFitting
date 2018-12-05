#include<iostream>
#include"GRANSAC.hpp"
#include"PlaneModel.hpp"
#include <omp.h>

bool PlaneFitting(std::vector<Vector3VP> points_input,int Num double* center, double* normal)
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
	Estimator.Initialize(10, 300); // Threshold, iterations
	Estimator.Estimate(CandPoints);
	
	auto BestPlane = Estimator.GetBestModel();
	if (BestPlane == nullptr)
	{
		return false;
	}
	for (int i = 0; i < 3; i++)
	{
		normal[i] = BestPlane->m_PlaneCoefs[i];
		center[i] = BestPlane->m_PointCenter[i];
	}
	return true;
}
int main()
{
	
}







