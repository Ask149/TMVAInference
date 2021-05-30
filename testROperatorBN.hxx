#ifndef TEST_OPERATOR_BN
#define TEST_OPERATOR_BN

#include "TMVA/RTensor.hxx"
#include "testROperator.hxx"
#include "ROperatorBN.hxx"
#include <sstream>

template<typename T>
bool testROperatorBNex1(double tol);

template<typename T>
bool testROperatorBN(double tol) {
   bool failed = false;

   failed |= testROperatorBNex1<T>(tol);
   
   return failed;
}


template<typename T>
bool testROperatorBNex1(double tol) {
   using namespace TMVA::Experimental;
   using TMVA::Experimental::SOFIE::ROperatorBN;

   // X
   T inputX[120] = {-1.9095213 ,  1.218844  ,  0.76495355,  0.0670151 , -0.60213196,
        0.49392796,  0.8695749 , -1.2979872 , -0.07066666,  1.1525824 ,
        0.42271087,  1.0284234 , -0.04561191, -0.09435329, -0.3284512 ,
       -0.20522097,  0.8535981 ,  0.6344595 , -0.26672226, -0.61256474,
        1.5730557 ,  0.26282558,  0.12445311,  0.3122296 , -1.061498  ,
       -0.23107629,  2.438932  ,  1.3413396 , -1.5409098 ,  1.5042274 ,
        0.7123857 ,  1.4870552 , -1.3786836 , -0.27757463,  1.811563  ,
       -0.64555687, -1.8314615 , -1.3670927 ,  0.24657932, -0.7309602 ,
       -1.8661383 , -1.515088  , -2.84557   , -1.0931219 , -0.32343584,
        1.1685846 ,  1.5722687 , -0.13897152, -1.1331571 ,  0.06784432,
        1.5154865 , -0.97512263, -1.0982232 ,  0.41904816,  0.47287086,
        1.6728544 ,  0.77808875,  0.3379938 ,  0.13388789, -1.2740448 ,
        0.9981336 , -0.8570239 , -0.47260493, -3.2788076 , -1.1861603 ,
       -0.16691786,  2.0951362 , -0.6706624 , -1.272584  , -0.52135366,
       -0.16400833, -0.9978094 ,  0.903902  ,  1.0329    , -0.07216305,
        0.3998871 , -0.5678381 ,  1.0642787 , -1.0477749 , -1.3917968 ,
        0.29486302,  0.08689022, -0.480461  , -0.75460184, -0.6183389 ,
        1.0237648 ,  0.42198288, -0.08204564, -2.0546257 , -0.89793694,
       -0.5638696 , -1.2734355 , -0.32096225, -1.0584327 , -0.09224104,
        0.19585583, -0.5208075 , -0.7935987 ,  0.17612757, -1.007827  ,
        0.7021446 ,  0.6574189 ,  0.34972036,  0.51691073,  2.0944574 ,
       -0.6356676 ,  0.20871985,  1.4097384 ,  0.01641679,  0.8997131 ,
       -1.026779  , -0.0579365 ,  0.45875865, -0.36347952,  1.029116  ,
        1.011908  , -0.44097945, -0.32804155,  0.9223772 ,  1.2286249 };
	RTensor<T> X(inputX, {2, 3, 4, 5});	

   // s
   T inputS[3] = {-0.0423089 , -0.05582622, -0.18905385};
   RTensor<T> s(inputS, {3});

   // bias
   T inputBias[3] = { -0.38561198,  1.0222404 ,  2.0636225};
   RTensor<T> bias(inputBias, {3});

   // mean
   T inputMean[3] = { 0.05369235,  1.0270655 , -0.8864892};
   RTensor<T> mean(inputMean, {3});

   // var
   T inputVar[3] = { 0.02769668, 0.3069227 , 0.29375818};
   RTensor<T> var(inputVar, {3});
   
   // Y
   T inputY[120] = {0.11339554, -0.681769  , -0.5663996 , -0.38899833, -0.21891527,
       -0.4975106 , -0.5929921 , -0.04204354, -0.35400254, -0.66492665,
       -0.4794087 , -0.6333681 , -0.36037093, -0.3479819 , -0.28847915,
       -0.3198017 , -0.58893114, -0.5332308 , -0.30416936, -0.21626349,
        0.9672228 ,  1.0992502 ,  1.1131936 ,  1.094272  ,  1.2326978 ,
        1.149019  ,  0.8799714 ,  0.9905721 ,  1.2810066 ,  0.9741584 ,
        1.0539496 ,  0.9758888 ,  1.2646595 ,  1.1537045 ,  0.94318926,
        1.1907849 ,  1.3102844 ,  1.2634916 ,  1.1008873 ,  1.1993906 ,
        2.4053292 ,  2.282881  ,  2.7469604 ,  2.1356971 ,  1.8672265 ,
        1.3468018 ,  1.2059946 ,  1.8028843 ,  2.1496615 ,  1.7307458 ,
        1.2258005 ,  2.0945382 ,  2.1374764 ,  1.6082441 ,  1.5894704 ,
        1.1709098 ,  1.4830087 ,  1.6365163 ,  1.7077094 ,  2.198804  ,
       -0.62566906, -0.1541271 , -0.25183833,  0.46143928, -0.07046759,
       -0.3295375 , -0.90450394, -0.20149627, -0.04850051, -0.23944741,
       -0.33027706, -0.1183424 , -0.60171735, -0.6345059 , -0.3536222 ,
       -0.4736074 , -0.22763206, -0.64248174, -0.10564223, -0.01819912,
        1.096022  ,  1.1169786 ,  1.1741487 ,  1.2017729 ,  1.1880422 ,
        1.022573  ,  1.0832125 ,  1.1340017 ,  1.332772  ,  1.2162163 ,
        1.1825535 ,  1.2540541 ,  1.1580765 ,  1.232389  ,  1.1350291 ,
        1.1059985 ,  1.1782143 ,  1.2057025 ,  1.1079866 ,  1.2272896 ,
        1.5094986 ,  1.525099  ,  1.632426  ,  1.5741091 ,  1.0238523 ,
        1.9761345 ,  1.6816077 ,  1.262686  ,  1.748684  ,  1.4405856 ,
        2.1125562 ,  1.7746189 ,  1.5943928 ,  1.8811939 ,  1.3954492 ,
        1.4014513 ,  1.9082263 ,  1.868833  ,  1.4326801 ,  1.3258593 }; 
   
   RTensor<T> TrueY(inputY, {2, 3, 4, 5});
   RTensor<T> Y({2, 3, 4, 5});

   ROperatorBN<T> bn(  1e-2,      /* epsilon */
                       0.9,       /* momentum */
                       0);        /* training_mode */

   bn.Forward_blas(X, s, bias, mean, var, Y);

   bool failed = !IsApprox(Y, TrueY, tol);

   std::stringstream ss;
   ss << "   ";
   ss << "Batch Normalization ex1 : Test ";
   ss << (failed? "Failed" : "Passed" );
   std::cout << ss.str() << std::endl;
   return failed;
}

#endif
